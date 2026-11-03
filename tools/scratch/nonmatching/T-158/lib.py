"""Shared scoring library: score_src(fn, draft_text, prefix) -> (masked, exact, frame, ninstr) ."""
import os, re, difflib, tempfile, importlib.util, concurrent.futures as cf
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT / 'tools/scratch/nonmatching/T-158/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
os.environ.setdefault('RONORM', '1')
_targets = {}
def M(x): return re.sub(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-7]|k[01]|gp|sp|fp|ra|f\d+)\b', 'R', x)
def target(fn):
    if fn not in _targets:
        t = [cm.canon(x) for x in cm.target_raw(fn)]
        _targets[fn] = [x for x in t if not x.startswith(('dlabel', 'enddlabel'))]
    return _targets[fn]
def score_src(fn, src, prefix=True):
    theirs = target(fn)
    with tempfile.TemporaryDirectory(prefix='s155-') as d:
        p = Path(d) / 'draft.c'; p.write_text(src)
        try:
            source, tu = cm.build_source(fn, p, prefix)
            o = cm.compile_source(source, Path(d) / 'c.c')
        except SystemExit:
            return None
        pairs = cm.draft_raw(o, fn)
    mine = [cm.canon(cm.apply_relocs(i, r)) for _, i, r in pairs]
    sm = difflib.SequenceMatcher(None, [M(x) for x in theirs], [M(x) for x in mine], autojunk=False)
    rg = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    sm = difflib.SequenceMatcher(None, theirs, mine, autojunk=False)
    ex = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    frame = next((abs(int(re.search(r'-?\d+$', x).group())) for x in mine if x.startswith('addiu sp,sp,')), 0)
    return rg, ex, frame, len(mine)
def run(fn, srcs, prefix=True, workers=14):
    with cf.ThreadPoolExecutor(workers) as ex:
        return list(ex.map(lambda s: score_src(fn, s, prefix), srcs))
