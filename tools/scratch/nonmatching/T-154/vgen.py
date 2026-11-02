#!/usr/bin/env python3
"""Generate variants of a draft from (name, [(old,new),...]) edits, score each.
usage: vgen.py fn base.c edits.py   (edits.py defines EDITS = {name: [(old,new),...]})
prints reg-masked and exact diff counts + whether pattern PAT appears in disassembly."""
import sys, os, re, difflib, importlib.util, tempfile, concurrent.futures as cf
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT / 'tools/scratch/nonmatching/T-154/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
import subprocess
def M(x):
    return re.sub(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-7]|k[01]|gp|sp|fp|ra|f\d+)\b', 'R', x)
def run(function, text, theirs, pat):
    with tempfile.TemporaryDirectory(prefix='vg-') as d:
        p = Path(d)/'draft.c'; p.write_text(text)
        try:
            source, tu = cm.build_source(function, p)
            o = cm.compile_source(source, Path(d)/'c.c')
        except SystemExit:
            return None
        pairs = cm.draft_raw(o, function)
        dis = subprocess.run([str(cm.OBJDUMP), '-dr', '--no-show-raw-insn', str(o)], capture_output=True, text=True).stdout
    mine_raw = [cm.canon(cm.apply_relocs(i, r)) for _, i, r in pairs]
    out = []
    for conv in (lambda x: M(x), lambda x: x):
        a = [conv(t) for t in theirs]; b = [conv(t) for t in mine_raw]
        sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
        out.append(sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal'))
    shared = bool(re.search(pat, '\n'.join(str(x) for x in mine_raw))) if pat else None
    return out[0], out[1], shared
def main():
    function, base, edits = sys.argv[1:4]
    pat = sys.argv[4] if len(sys.argv) > 4 else None
    ns = {}; exec(Path(edits).read_text(), ns)
    src = Path(base).read_text()
    theirs = [cm.canon(t) for t in cm.target_raw(function)]
    theirs = [t for t in theirs if not t.startswith(('dlabel', 'enddlabel'))]
    jobs = {}
    for name, eds in ns['EDITS'].items():
        t = src; ok = True
        for ed in eds:
            old, new = ed[0], ed[1]
            if old not in t: ok = False; print('MISSING', name, old[:40]); break
            t = t.replace(old, new) if len(ed) > 2 else t.replace(old, new, 1)
        if ok: jobs[name] = t
    with cf.ThreadPoolExecutor(8) as ex:
        futs = {ex.submit(run, function, t, theirs, pat): n for n, t in jobs.items()}
        res = {}
        for f in cf.as_completed(futs):
            res[futs[f]] = f.result()
    for n in jobs:
        print(n, res[n])
    if ns.get('SAVE'):
        for n, t in jobs.items(): Path(ns['SAVE'], n + '.c').write_text(t)
main()
