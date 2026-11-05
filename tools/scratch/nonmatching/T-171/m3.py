#!/usr/bin/env python3
"""measure + aligned instruction listing with optional TU substitutions.

usage: m3.py FUNCTION DRAFT [--listing] [FROM TO]...
"""
import importlib.util, json, re, struct, subprocess, sys, tempfile
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
OBJDUMP = ROOT / 'tools/ext/binutils/bin/mips64-elf-objdump'
BASES = {'main': 0x8000F960, 'ovl_7DF8': 0x801ABB20}


def main():
    fn = sys.argv[1]
    draft = Path(sys.argv[2])
    listing = '--listing' in sys.argv
    rest = [a for a in sys.argv[3:] if a != '--listing']
    subs = [(rest[i], rest[i + 1]) for i in range(0, len(rest) - 1, 2)]
    owners = []
    for tu in (ROOT / 'src').glob('*/*.c'):
        text = tu.read_text()
        m = re.search(r'#pragma GLOBAL_ASM\("[^"\n]*/' + re.escape(fn) + r'\.s"\)', text)
        if m:
            owners.append((tu, text, m))
    tu, text, m = owners[0]
    head, tail = text[:m.start()], text[m.end():]
    for a, b in subs:
        head = head.replace(a, b)
    source = head + draft.read_text() + tail
    originals = json.loads((ROOT / 'tools/progress/original-functions.json').read_text())
    row = next(r for r in originals.values() if r['function'] == fn)
    with tempfile.TemporaryDirectory(prefix='kig-m3-') as d:
        c = Path(d) / 'c.c'; o = c.with_suffix('.o')
        c.write_text(source)
        cmd = [ROOT / '.venv/bin/python', ROOT / 'tools/ext/asm-processor/build.py',
               ROOT / 'tools/ext/ido/5.3/cc', '--',
               ROOT / 'tools/ext/binutils/bin/mips64-elf-as', '-EB', '-mips3', '-32', '-G', '0',
               '-I', 'include', '--', '-c', '-G', '0', '-non_shared', '-Xcpluscomm',
               '-Wab,-r4300_mul', '-O2', '-mips2', '-32', '-Iinclude', '-o', str(o), str(c)]
        r = subprocess.run([str(x) for x in cmd], cwd=ROOT, capture_output=True, text=True)
        if r.returncode:
            print(r.stderr[-2000:]); return
        code, masks, _ = screen.elf.elf_function(o, fn)
        mine = []
        if listing:
            out = subprocess.run([str(OBJDUMP), '-dr', '--no-show-raw-insn', str(o)],
                                 capture_output=True, text=True).stdout
            lines = out.splitlines()
            s = [i for i, l in enumerate(lines) if re.match(r'^[0-9a-f]{8} <' + re.escape(fn) + r'>:$', l)][0]
            for l in lines[s + 1:]:
                if re.match(r'^[0-9a-f]{8} <', l):
                    break
                mm = re.match(r'\s*[0-9a-f]+:\t(.*?)(?:\s*#.*)?$', l)
                if mm:
                    mine.append(mm.group(1).strip())
    base = BASES[row['area']]
    off = int(fn[5:], 16) - base
    target = (ROOT / 'build/segments' / (row['area'] + '.bin')).read_bytes()[off:off + row['bytes']]
    a = struct.unpack('>' + 'I' * (len(code) // 4), code)
    b = struct.unpack('>' + 'I' * (len(target) // 4), target)
    words = sum((x & masks[i]) != (y & masks[i]) for i, (x, y) in enumerate(zip(a, b))) + abs(len(a) - len(b))
    if listing:
        raw = (ROOT / ('asm/nonmatchings/' + row['area'] + '/' + tu.stem + '/' + fn + '.s')).read_text()
        raw = re.sub(r'/\*.*?\*/', ' ', raw).split('glabel', 1)[-1]
        tgt = []
        for line in raw.splitlines():
            line = line.split('#')[0].strip()
            if not line:
                continue
            mn = line.split()[0]
            if mn.startswith('.') or mn in ('glabel', 'endlabel', 'nonmatching', '}', '{', 'dlabel', 'enddlabel'):
                continue
            tgt.append(line)
        for i in range(max(len(mine), len(tgt))):
            mt = mine[i] if i < len(mine) else ''
            tt = tgt[i] if i < len(tgt) else ''
            print(f'{i:4d} T: {tt:44s} D: {mt}')
    print(f'# {words} words, {len(code)}/{len(target)} B, target {len(b)} / draft {len(a)} instrs')


main()
