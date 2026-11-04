import sys, itertools, difflib
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
from bbred3 import GB, region, TR
def rscore(ls, isregion=False):
    r = ls if isregion else region(ls)
    sm = difflib.SequenceMatcher(None, TR, r, autojunk=False)
    return sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
types = ['', 's32', 's16', 'u16', 's8', 'u8']
casts = ['{}', '(s16)({})', '(u16)({})', '(s8)({})', '(u8)({})']
cands = {}
for tr, tc, cr, cv in itertools.product(types, types, casts, casts):
    for ipos in range(1, 4):
        for ex in range(2):
            decl = ''
            if tr: decl += f'    {tr} r;\n'
            if tc: decl += f'    {tc} c;\n'
            rr = 'r' if tr else cr.format('(i - 8)')
            if not tr and cr != '{}': pass
            stm = []
            if tr: stm.append('r = %s;' % cr.format('i - 8'))
            sh = f'({rr} << 11)' if ex == 0 else f'({rr} * 0x800)'
            v = cv.format(f'{sh} | 1')
            if tc: stm.append(f'c = {v};'); stm.append('*palette++ = c;')
            else: stm.append(f'*palette++ = {v};')
            if ipos < len(stm): stm.insert(ipos, 'i++;')
            else: stm.append('i++;')
            body = '    if (i < 40) do { ' + ' '.join(stm) + ' } while (i < 40);\n'
            cands[(tr, tc, cr, cv, ipos, ex)] = bbl.HEAD + bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i, green;\n' + decl) + body + bbl.GB if False else bbl.HEAD + bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i, green;\n' + decl) + body + GB + bbl.TAIL
names = list(cands)
print(len(names), flush=True)
res = bbl.run([cands[n] for n in names])
out = sorted([(rscore(r[1]), r[0], n) for n, r in zip(names, res) if r])
for x in out[:25]: print(x)
seen = {}
for n, r in zip(names, res):
    if r: seen.setdefault(tuple(region(r[1])), []).append(n)
print(len(seen), 'distinct regions')
for k, v in sorted(seen.items(), key=lambda kv: rscore(list(kv[0]), True))[:12]:
    print(rscore(list(k), True), v[:3], k)
