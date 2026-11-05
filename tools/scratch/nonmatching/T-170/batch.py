#!/usr/bin/env python3
"""Batch: emit many variants of the else-arm store and report words/bytes/store count."""
import importlib.util, sys, tempfile, re, os
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)

fn = sys.argv[1]
base_path = Path(sys.argv[2])
base = base_path.read_text()
variants = eval(Path(sys.argv[3]).read_text())  # dict name -> (replace_from, replace_to)
pre = f'w_{fn[-6:].lower()}_'
outdir = base_path.parent
for name, (a, b) in variants.items():
    p = outdir / (pre + name + '.c')
    assert a in base, f'{name}: pattern not found'
    p.write_text(base.replace(a, b))
    try:
        r = screen.measure(fn, p)
        src, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(src, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        ins = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
        sw = sum(1 for x in ins if re.match(r'sw \w+,%lo\(0x801f3aa0\)', x))
        print(f'{name:24s} words={r["words"]:4d} bytes={r["compiled"]}/{r["original"]} stores={sw}')
    except Exception as e:
        print(f'{name:24s} ERROR {str(e)[-300:]}')
