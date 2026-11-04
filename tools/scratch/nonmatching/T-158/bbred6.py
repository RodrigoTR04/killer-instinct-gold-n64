import sys, itertools, difflib
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
from bbred3 import GB, region, TR
from bbred5 import rdiff
C = ['', 's16', 'u16', 's8', 'u8', 's32', 'u32']
def cast(t, e): return f'({t})({e})' if t else e
names = []; srcs = []
for c0, c1, c2, c3 in itertools.product(C, C, C, C):
    e = cast(c3, '(' + cast(c2, '(' + cast(c1, '(' + cast(c0, 'i') + ' - 8)') + ' << 11)') + ' | 1)')
    names.append((c0, c1, c2, c3))
    srcs.append(bbl.HEAD + bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i, green;\n') + f'    if (i < 40) do {{ *palette++ = {e}; i++; }} while (i < 40);\n' + GB + bbl.TAIL)
print(len(srcs), flush=True)
res = bbl.run(srcs)
seen = {}
for n, r in zip(names, res):
    if r: seen.setdefault(tuple(region(r[1])), []).append(n)
rows = sorted(seen.items(), key=lambda kv: rdiff(list(kv[0])))
print(len(rows), 'regions')
for k, v in rows[:12]: print(rdiff(list(k)), v[:3], k[2:8])
