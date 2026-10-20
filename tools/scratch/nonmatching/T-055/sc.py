#!/usr/bin/env python3
"""sc.py file.c func [--mips1] [-v]: compile standalone (IDO 5.3 -O2), compare to built image.
Relocation fields masked. -v prints side-by-side disassembly."""
import importlib.util, json, struct, subprocess, sys, tempfile, difflib
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('c', ROOT / 'tools/scratch/flagprobe/compare.py')
cmp = importlib.util.module_from_spec(spec); spec.loader.exec_module(cmp)
OD = str(ROOT / 'tools/ext/binutils/bin/mips64-elf-objdump')
import os
EXTRA = os.environ.get('OPT', '-O2').split()
rows = json.loads((ROOT / 'tools/progress/original-functions.json').read_text())

def target(name):
    row = next(r for r in rows.values() if r['function'] == name)
    if row['area'] == 'boot':
        off = int(row['rom'], 16); return (ROOT / 'baserom.us.z64').read_bytes()[off:off + row['bytes']]
    base = {'main': 0x8000F960, 'ovl_7DF8': 0x801ABB20}[row['area']]
    a = int(row['vram'], 16) - base
    return Path(f"/tmp/t055ref/{row['area']}.bin").read_bytes()[a:a + row['bytes']]

def dis(words):
    with tempfile.NamedTemporaryFile(suffix='.bin') as f:
        f.write(struct.pack('>%dI' % len(words), *words)); f.flush()
        out = subprocess.run([OD, '-D', '-b', 'binary', '-m', 'mips:4300', '-EB', '-M', 'reg-names=32', f.name],
                             capture_output=True, text=True).stdout
    return [l.split('\t', 2)[-1].replace('\t', ' ') for l in out.splitlines() if ':\t' in l]

def run(path, name, mips='-mips2', verbose=False):
    with tempfile.TemporaryDirectory() as d:
        obj = Path(d) / 'p.o'
        r = subprocess.run([str(ROOT / 'tools/ext/ido/5.3/cc'), '-c', '-G', '0', '-non_shared', '-Xcpluscomm',
                            '-Wab,-r4300_mul', *EXTRA, mips, '-32', '-I' + str(ROOT / 'include'), str(Path(path).resolve()), '-o', str(obj)],
                           cwd=ROOT, capture_output=True, text=True)
        if r.returncode:
            print("\n".join(l for l in r.stderr.splitlines() if "Error" in l) or r.stderr[-3000:]); return None
        code, masks, _ = cmp.elf_function(obj, name)
    w = struct.unpack('>%dI' % (len(code) // 4), code)
    t = struct.unpack('>%dI' % (len(target(name)) // 4), target(name))
    diff = [i for i in range(max(len(w), len(t))) if i >= len(w) or i >= len(t) or (w[i] & masks[i]) != (t[i] & masks[i])]
    print(f'{name}: {len(diff)} words differ, size {len(code)}/{len(t)*4}')
    if verbose:
        mw = [x & m for x, m in zip(w, masks)]; mt = [x & m for x, m in zip(t, masks + [0xFFFFFFFF]*len(t))]
        a, b = dis(mw), dis(mt)
        for i in range(max(len(a), len(b))):
            x = a[i] if i < len(a) else ''; y = b[i] if i < len(b) else ''
            print(f"{i*4:4x} {'*' if x != y else ' '} {x:40s} | {y}")
    return len(diff)

if __name__ == '__main__':
    a = sys.argv[1:]
    run(Path(a[0]), a[1], '-mips1' if '--mips1' in a else '-mips2', '-v' in a)
