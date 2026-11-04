"""helpers for func_801BBB60 loop search: canonical lines of a variant, per-loop region diff"""
import sys, re, difflib, tempfile, os
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import lib
cm = lib.cm
FN = 'func_801BBB60'
BASE = Path('tools/scratch/nonmatching/T-158/w/bb60_base.c').read_text()
HEAD = BASE[:BASE.index('    s16 *palette')]
PRE = BASE[BASE.index('    s16 *palette'):BASE.index('    if (i < 40) do')]
TAIL = BASE[BASE.index('    D_802C9F64 = 0;'):]
def lines(src):
    with tempfile.TemporaryDirectory(prefix='bb-') as d:
        p = Path(d) / 'draft.c'; p.write_text(src)
        try:
            source, tu = cm.build_source(FN, p, False)
            o = cm.compile_source(source, Path(d) / 'c.c')
        except SystemExit:
            return None
        pairs = cm.draft_raw(o, FN)
    return [cm.canon(cm.apply_relocs(i, r)) for _, i, r in pairs]
TGT = lib.target(FN)
def regions(ls):
    # split at loop-test constants
    idx = {}
    for k, l in enumerate(ls):
        for c in (40, 72, 128):
            if l.startswith('slti at,v1,%d' % c) and c not in idx: idx[c] = k
    return idx
def score(src):
    ls = lines(src)
    if ls is None: return None
    sm = difflib.SequenceMatcher(None, TGT, ls, autojunk=False)
    return sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal'), ls
def run(srcs, workers=16):
    import concurrent.futures as cf
    with cf.ThreadPoolExecutor(workers) as ex:
        return list(ex.map(score, srcs))
