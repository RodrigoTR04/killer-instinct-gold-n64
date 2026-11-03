#!/usr/bin/env python3
"""Hill-climb cmd-pointer styles per site. usage: cmdsearch2.py fn draft out.c GfxType [--prefix env PREFIX]
Draft must use block-style sites:  '{ GfxType *cmd = (*dl)++; ... }' or inside if/else braces 'GfxType *cmd = (*dl)++;'"""
import sys, os, re, random, difflib, tempfile, importlib.util, concurrent.futures as cf
from pathlib import Path
os.environ['RONORM'] = '1'
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT / 'tools/scratch/nonmatching/T-154/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
fn, draft, out, GT = sys.argv[1:5]
src = Path(draft).read_text()
lines = src.split('\n')
# find sites: line matching '<ws>GT *cmd = (*dl)++;' ; site body = following lines starting with 'cmd->' or 'count++;'
sites = []
i = 0
decl_re = re.compile(r'^(\s*)' + re.escape(GT) + r' \*cmd = \(\*dl\)\+\+;$')
while i < len(lines):
    m = decl_re.match(lines[i])
    if m:
        j = i + 1
        while j < len(lines) and re.match(r'^\s*(cmd->|count\+\+;)', lines[j]): j += 1
        sites.append((i, j - 1, m.group(1))); i = j
    else: i += 1
print('sites', len(sites), file=sys.stderr)
theirs = [cm.canon(t) for t in cm.target_raw(fn)]
theirs = [t for t in theirs if not t.startswith(('dlabel', 'enddlabel'))]
fm = re.search(r'\b' + fn + r'\([^)]*\)\s*\{\n', src)
def build(assign):
    out_lines = list(lines)
    # each site rewrite
    for (a, b, ind), st in zip(sites, assign):
        if st == 'blk': continue  # keep as local decl in its scope
        var = {'shared': 'cmd', 'cmd2': 'cmd2', 'cmd3': 'cmd3'}[st]
        out_lines[a] = f'{ind}{var} = (*dl)++;'
        for x in range(a + 1, b + 1):
            out_lines[x] = out_lines[x].replace('cmd->', var + '->')
    t = '\n'.join(out_lines)
    need = set(assign)
    decl = ''
    if 'shared' in need: decl += f'    {GT} *cmd;\n'
    if 'cmd2' in need: decl += f'    {GT} *cmd2;\n'
    if 'cmd3' in need: decl += f'    {GT} *cmd3;\n'
    p = fm.end()
    # compute offset in rebuilt text: header lines unchanged before first site
    idx = t.index('{\n', t.index(fn + '(')) + 2
    return t[:idx] + decl + t[idx:]
def score(assign):
    with tempfile.TemporaryDirectory(prefix='cs2-') as d:
        pth = Path(d) / 'draft.c'; pth.write_text(build(assign))
        try:
            source, tu = cm.build_source(fn, pth)
            o = cm.compile_source(source, Path(d) / 'c.c')
        except SystemExit:
            return 10**6
        pairs = cm.draft_raw(o, fn)
    mine = [cm.canon(cm.apply_relocs(i, r)) for _, i, r in pairs]
    sm = difflib.SequenceMatcher(None, theirs, mine, autojunk=False)
    return sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
styles = ['blk', 'shared', 'cmd2', 'cmd3']
cur = ['blk'] * len(sites); best = score(cur); print('start', best, file=sys.stderr)
rnd = random.Random(1)
with cf.ThreadPoolExecutor(14) as ex:
    for rnd_i in range(4):
        improved = True
        while improved:
            improved = False
            cands = []
            for si in range(len(sites)):
                for st in styles:
                    if st != cur[si]:
                        c = list(cur); c[si] = st; cands.append(c)
            for _ in range(20):
                c = list(cur)
                for k in rnd.sample(range(len(sites)), 2): c[k] = rnd.choice(styles)
                cands.append(c)
            res = list(ex.map(score, cands))
            mn = min(res)
            if mn < best:
                best = mn; cur = cands[res.index(mn)]; improved = True
                print('best', best, cur, file=sys.stderr, flush=True)
                Path(out).write_text(build(cur))
print('final', best, cur)
Path(out).write_text(build(cur))
