"""Score a7c drafts and report unroll factor."""
import importlib.util, re, subprocess, tempfile, os, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
specc = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(specc); specc.loader.exec_module(screen)

def info(fn, path):
    path = Path(path)
    r = dict(screen.measure(fn, path))
    source, tu = cm.build_source(fn, path, False)
    with tempfile.TemporaryDirectory() as d:
        o = cm.compile_source(source, Path(d)/'c.c')
        pairs = cm.draft_raw(o, fn)
    mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    masks = [m for m in mine if re.match(r'andi \w+,\w+,\d+$', m)]
    return r['words'], r['compiled'], len(mine), [m.split(',')[-1] for m in masks]
