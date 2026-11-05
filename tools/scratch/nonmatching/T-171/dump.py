#!/usr/bin/env python3
"""Side-by-side full listing: index, target instr, draft instr, equality."""
import importlib.util, json, re, struct, subprocess, sys, tempfile
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
OBJDUMP = ROOT / 'tools/ext/binutils/bin/mips64-elf-objdump'
BASES = {'main': 0x8000F960, 'ovl_7DF8': 0x801ABB20}

def build(function, draft, prefix=False):
    owners = []
    for tu in sorted((ROOT / 'src').glob('*/*.c')):
        text = tu.read_text()
        m = re.search(r'#pragma GLOBAL_ASM\("[^"\n]*/' + re.escape(function) + r'\.s"\)', text)
        if m: owners.append((tu, text, m))
    tu, text, m = owners[0]
    source = text[:m.start()] + draft.read_text() + ('' if prefix else text[m.end():])
    if prefix: source = re.sub(r'#pragma GLOBAL_ASM\([^\n]*\)', '', source)
    return source, tu

def compile_source(source, path):
    path.write_text(source)
    o = path.with_suffix('.o')
    cmd = [ROOT / '.venv/bin/python', ROOT / 'tools/ext/asm-processor/build.py',
           ROOT / 'tools/ext/ido/5.3/cc', '--',
           ROOT / 'tools/ext/binutils/bin/mips64-elf-as', '-EB', '-mips3', '-32', '-G', '0',
           '-I', 'include', '--', '-c', '-G', '0', '-non_shared', '-Xcpluscomm',
           '-Wab,-r4300_mul', '-O2', '-mips2', '-32', '-Iinclude', '-o', str(o), str(path)]
    r = subprocess.run([str(x) for x in cmd], cwd=ROOT, capture_output=True, text=True)
    if r.returncode:
        print(r.stderr[-6000:], file=sys.stderr); raise SystemExit(1)
    return o

def instructions(o, function):
    text = subprocess.run([str(OBJDUMP), '-dr', '--no-show-raw-insn', str(o)], capture_output=True, text=True).stdout
    out, started = [], False
    for line in text.splitlines():
        if re.match(r'^[0-9a-f]{8} <' + re.escape(function) + r'>:$', line): started = True; continue
        if started and re.match(r'^[0-9a-f]{8} <', line): break
        if not started: continue
        m = re.match(r'\s*[0-9a-f]+:\t(.*?)(?:\s*#.*)?$', line)
        if m: out.append(m.group(1).strip())
    return out

def target_bytes(function):
    originals = json.loads((ROOT / 'tools/progress/original-functions.json').read_text())
    row = next(r for r in originals.values() if r['function'] == function)
    off = int(function[5:], 16) - BASES[row['area']]
    blob = (ROOT / 'build/segments' / (row['area'] + '.bin')).read_bytes()
    return blob[off:off + row['bytes']], row

def main():
    function, draft = sys.argv[1], Path(sys.argv[2])
    if not draft.is_absolute(): draft = ROOT / draft
    source, tu = build(function, draft, '--prefix' in sys.argv)
    with tempfile.TemporaryDirectory(prefix='kig-dump-') as d:
        o = compile_source(source, Path(d) / 'c.c')
        code, masks, _ = screen.elf.elf_function(o, function)
        mine = instructions(o, function)
    target, row = target_bytes(function)
    a = struct.unpack('>' + 'I' * (len(code) // 4), code)
    b = struct.unpack('>' + 'I' * (len(target) // 4), target)
    raw = (ROOT / ('asm/nonmatchings/' + row['area'] + '/' + tu.stem + '/' + function + '.s')).read_text()
    raw = re.sub(r'/\*.*?\*/', ' ', raw)
    raw = raw.split('.glabel' if '.glabel' in raw else 'glabel', 1)[-1]
    tgt = []
    for line in raw.splitlines():
        line = line.split('#')[0].strip()
        if not line: continue
        mnem = line.split()[0]
        if mnem.startswith('.') or mnem in ('glabel', 'endlabel', 'nonmatching', '}', '{', 'dlabel', 'enddlabel'): continue
        tgt.append(line)
    n = max(len(a), len(b))
    print(f'# {function} target {len(b)} draft {len(a)}')
    for i in range(n):
        eq = i < len(a) and i < len(b) and (a[i] & masks[i]) == (b[i] & masks[i])
        t = tgt[i] if i < len(tgt) else ''
        c = mine[i] if i < len(mine) else ''
        print(f'{i:4d} {"  " if eq else "**"} T: {t:46s} D: {c}')
main()
