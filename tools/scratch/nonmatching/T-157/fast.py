#!/usr/bin/env python3
"""Fast standalone evaluator: compile ONLY the draft (with common.h) and score vs the target.
usage: fast.py fn draft.c   -> prints regmasked and exact LCS diff counts + frame size
module: score(fn, text, theirs_cache) -> (regmasked, exact)"""
import difflib, importlib.util, os, re, sys, tempfile
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT / 'tools/scratch/nonmatching/T-157/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
os.environ.setdefault('RONORM', '1')
REG = re.compile(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f\d+)\b')
def M(x): return REG.sub('R', x)
_cache = {}
def target(fn):
    if fn not in _cache:
        raw = [cm.canon(t) for t in cm.target_raw(fn)]
        raw = [t for t in raw if not t.startswith(('dlabel', 'enddlabel'))]
        _cache[fn] = raw
    return _cache[fn]
def lcsdiff(a, b):
    sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
    return sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
import threading
_scorer = {}
_lock = threading.Lock()
_tls = threading.local()
def pscorer(fn):
    if fn not in _scorer:
        import sys
        sys.path.insert(0, str(ROOT / 'tools/ext/decomp-permuter'))
        from src.scorer import Scorer
        tgt = ROOT / f'tools/scratch/nonmatching/T-157/targets/{fn}.o'
        if not tgt.exists(): _scorer[fn] = None
        else:
            _scorer[fn] = Scorer(str(tgt), stack_differences=True, algorithm='levenshtein', debug_mode=False,
                                 ign_branch_targets=False,
                                 objdump_command=str(ROOT / 'tools/ext/binutils/bin/mips64-elf-objdump') + ' -drz -m mips:4300')
    return _scorer[fn]

def compile_raw(fn, text, header='#include "common.h"\n'):
    with tempfile.TemporaryDirectory(prefix='fast-') as d:
        try:
            o = cm.compile_source(header + text, Path(d) / 'c.c')
        except SystemExit:
            return None
        pairs = cm.draft_raw(o, fn)
        with _lock:
            sc = pscorer(fn)
            _tls.p = sc.score(str(o))[0] if sc else -1
    return [cm.canon(cm.apply_relocs(i, r)) for _, i, r in pairs]
def score(fn, text, header='#include "common.h"\n'):
    raw = compile_raw(fn, text, header)
    if raw is None: return None
    t = target(fn)
    fr = re.match(r'addiu sp,sp,-(\d+)', raw[0]) if raw else None
    return (lcsdiff([M(x) for x in t], [M(x) for x in raw]), lcsdiff(t, raw), len(raw), int(fr.group(1)) if fr else 0, getattr(_tls, 'p', -1))
if __name__ == '__main__':
    fn, draft = sys.argv[1], sys.argv[2]
    print(draft, score(fn, Path(draft).read_text()))
