#!/usr/bin/env python3
"""Score a candidate definition in its complete owning TU; temporary outputs only."""
import importlib.util
import json
from pathlib import Path
import re
import struct
import subprocess
import sys
import tempfile
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('compare', ROOT / 'tools/scratch/flagprobe/compare.py')
cmp = importlib.util.module_from_spec(spec)
spec.loader.exec_module(cmp)
rows = {r['function']: r for r in json.loads((ROOT / 'tools/progress/original-functions.json').read_text()).values()}

def check(fn, candidate, full_tu=True):
    for tu in (ROOT / 'src').glob('*/*.c'):
        text = tu.read_text()
        match = re.search(r'#pragma GLOBAL_ASM\("[^"\n]*/' + fn + r'\.s"\)', text)
        if match:
            break
    else:
        raise ValueError('no owner: ' + fn)
    with tempfile.TemporaryDirectory(prefix='t082-check-') as tmp:
        c = Path(tmp) / 'candidate.c'
        o = c.with_suffix('.o')
        source = text[:match.start()] + candidate + (text[match.end():] if full_tu else '')
        if not full_tu:
            source = re.sub(r'#pragma GLOBAL_ASM\([^\n]*\)', '', source)
        c.write_text(source)
        cmd = [str(ROOT / '.venv/bin/python'), str(ROOT / 'tools/ext/asm-processor/build.py'), str(ROOT / 'tools/ext/ido/5.3/cc'), '--', str(ROOT / 'tools/ext/binutils/bin/mips64-elf-as'), '-EB', '-mips3', '-32', '-G', '0', '-I', 'include', '--', '-c', '-G', '0', '-non_shared', '-Xcpluscomm', '-Wab,-r4300_mul', '-O2', '-mips2', '-32', '-Iinclude', '-o', str(o), str(c)]
        r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
        if r.returncode:
            raise RuntimeError(r.stderr[-5000:])
        code, masks, _ = cmp.elf_function(o, fn)
    row = rows[fn]
    base = 0x8000F960 if row['area'] == 'main' else 0x801ABB20
    offset = int(fn[5:], 16) - base
    target = (ROOT / 'build/segments' / (row['area'] + '.bin')).read_bytes()[offset:offset + row['bytes']]
    a = struct.unpack('>' + 'I' * (len(code)//4), code)
    b = struct.unpack('>' + 'I' * (len(target)//4), target)
    diffs = [i*4 for i,(x,y) in enumerate(zip(a,b)) if x & masks[i] != y & masks[i]]
    return {'words': len(diffs) + abs(len(a)-len(b)), 'bytes': len(code), 'target_bytes': len(target), 'offsets': diffs}

if __name__ == '__main__':
    print(json.dumps(check(sys.argv[1], Path(sys.argv[2]).read_text())))
