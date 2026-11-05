#!/usr/bin/env python3
"""info.py FN DRAFT... : official count, bytes, instruction count, unroll mask."""
import sys, importlib.util, re, tempfile
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT / 'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec)
spec.loader.exec_module(cm)
specc = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(specc)
specc.loader.exec_module(screen)

fn = sys.argv[1]
for d in sys.argv[2:]:
    path = Path(d)
    if not path.is_absolute():
        path = ROOT / path
    try:
        r = dict(screen.measure(fn, path))
    except Exception as e:
        print(f'{d}: ERROR {str(e)[:200]}')
        continue
    source, tu = cm.build_source(fn, path, False)
    with tempfile.TemporaryDirectory() as td:
        o = cm.compile_source(source, Path(td) / 'c.c')
        pairs = cm.draft_raw(o, fn)
    mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    masks = [m for m in mine if re.match(r'andi \w+,\w+,\d+$', m)]
    nmul = sum(1 for m in mine if m.startswith('multu'))
    print(f'{path.name}: words={r["words"]} bytes={r["compiled"]}/{r["original"]} instr={len(mine)} masks={masks} multu={nmul}')
