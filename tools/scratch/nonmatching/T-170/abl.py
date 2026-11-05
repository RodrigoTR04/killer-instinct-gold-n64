#!/usr/bin/env python3
"""Ablate named locals in a draft to find which ones inflate the frame."""
import importlib.util, sys, tempfile, re, difflib
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)

fn = sys.argv[1]
base = Path(sys.argv[2]).read_text()
decl_re = re.compile(sys.argv[3], re.M)


def frame_of(src):
    return re.search(r'addiu sp,sp,-(\d+)', src)


def score(txt, tag):
    p = ROOT / 'tools/scratch/nonmatching/T-170' / f'ab_{tag}.c'
    p.write_text(txt)
    try:
        r = screen.measure(fn, p)
        source, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(source, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
        fr = frame_of(' '.join(mine))
    except Exception as e:
        return (9999, f'{tag:16s} ERROR {str(e)[-70:]}')
    return (r['words'], f'{tag:16s} w={r["words"]:4d} {r["compiled"]}/{r["original"]} frame={fr.group(1) if fr else "?"}')


print(score(base, 'base')[1])
for m in decl_re.finditer(base):
    line = m.group(0)
    name = re.search(r'\*?\s*(\w+)\s*(\[|;|=)', line)
    v = base.replace(line, '', 1)
    print(score(v, (name.group(1) if name else line.strip()[:12]))[1], flush=True)
