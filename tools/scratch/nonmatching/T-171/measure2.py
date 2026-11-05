#!/usr/bin/env python3
"""Like screen.measure but with extra TU text substitutions.

Usage: measure2.py FUNCTION DRAFT [SUB_FROM SUB_TO]...
"""
import importlib.util, json, re, struct, subprocess, sys, tempfile
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)

def main():
    fn = sys.argv[1]
    draft = Path(sys.argv[2])
    subs = [(sys.argv[i], sys.argv[i + 1]) for i in range(3, len(sys.argv) - 1, 2)]
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
    with tempfile.TemporaryDirectory(prefix='kig-m2-') as d:
        c = Path(d) / 'c.c'; o = c.with_suffix('.o')
        c.write_text(source)
        cmd = [ROOT / '.venv/bin/python', ROOT / 'tools/ext/asm-processor/build.py',
               ROOT / 'tools/ext/ido/5.3/cc', '--',
               ROOT / 'tools/ext/binutils/bin/mips64-elf-as', '-EB', '-mips3', '-32', '-G', '0',
               '-I', 'include', '--', '-c', '-G', '0', '-non_shared', '-Xcpluscomm',
               '-Wab,-r4300_mul', '-O2', '-mips2', '-32', '-Iinclude', '-o', str(o), str(c)]
        r = subprocess.run([str(x) for x in cmd], cwd=ROOT, capture_output=True, text=True)
        if r.returncode:
            print(r.stderr[-2500:]); return
        code, masks, _ = screen.elf.elf_function(o, fn)
    originals = json.loads((ROOT / 'tools/progress/original-functions.json').read_text())
    row = next(r for r in originals.values() if r['function'] == fn)
    base = {'main': 0x8000F960, 'ovl_7DF8': 0x801ABB20}[row['area']]
    off = int(fn[5:], 16) - base
    target = (ROOT / 'build/segments' / (row['area'] + '.bin')).read_bytes()[off:off + row['bytes']]
    a = struct.unpack('>' + 'I' * (len(code) // 4), code)
    b = struct.unpack('>' + 'I' * (len(target) // 4), target)
    words = sum((x & masks[i]) != (y & masks[i]) for i, (x, y) in enumerate(zip(a, b))) + abs(len(a) - len(b))
    print(f'{words} words, {len(code)}/{len(target)} B  {draft}  subs={len(subs)}')

main()
