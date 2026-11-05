#!/usr/bin/env python3
"""Ablation: for a draft, report words/bytes/frame and the positional diff length."""
import importlib.util, sys, tempfile, re, difflib
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)

fn = sys.argv[1]
for d in sys.argv[2:]:
    p = Path(d) if Path(d).is_absolute() else ROOT / d
    try:
        r = screen.measure(fn, p)
        source, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as dd:
            o = cm.compile_source(source, Path(dd)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
        fr = re.search(r'addiu sp,sp,-(\d+)', ' '.join(mine))
        print(f'{p.name:26s} w={r["words"]:4d} {r["compiled"]}/{r["original"]} frame={fr.group(1) if fr else "?"} n={len(mine)}')
    except Exception as e:
        print(f'{p.name:26s} ERROR {str(e)[-90:]}')
