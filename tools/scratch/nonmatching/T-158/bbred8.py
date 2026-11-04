import sys, itertools, random
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
from bbred3 import GB, region, TR
from bbred5 import rdiff
rnd = random.Random(int(sys.argv[1]) if len(sys.argv) > 1 else 1)
N = int(sys.argv[2]) if len(sys.argv) > 2 else 1500
T = ['', 's16', 'u16', 's32', 'u8', 's8', 'u32']
def cast(t, e): return f'({t})({e})' if t else e
def gen():
    # variables
    tr, tc, td = rnd.choice(T), rnd.choice(T), rnd.choice(T)
    use_r, use_c = tr != '', tc != ''
    c1, c2, c3 = rnd.choice(T), rnd.choice(T), rnd.choice(T)
    stm = []
    a = cast(c1, 'i - 8')
    if use_r: stm.append(f'r = {a};'); a = 'r'
    b = cast(c2, f'({a}) << 11')
    if rnd.random() < 0.3: b = cast(c2, f'({a}) * 2048')
    if use_c: stm.append(f'c = {b};'); b = 'c'
    e = cast(c3, f'({b}) | 1')
    stm.append(f'*palette++ = {e};')
    pos = rnd.randrange(len(stm) + 1)
    inc = rnd.choice(['i++;', 'i += 1;', 'i = i + 1;'])
    stm.insert(pos, inc)
    form = rnd.choice(['dw', 'for', 'wh'])
    decl = (f'    {tr} r;\n' if use_r else '') + (f'    {tc} c;\n' if use_c else '')
    if form == 'dw': body = '    if (i < 40) do { ' + ' '.join(stm) + ' } while (i < 40);\n'
    elif form == 'wh': body = '    while (i < 40) { ' + ' '.join(stm) + ' }\n'
    else:
        stm.remove(inc)
        body = '    for (; i < 40; i++) { ' + ' '.join(stm) + ' }\n'
    return decl, body
cands = [gen() for _ in range(N)]
srcs = [bbl.HEAD + bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i, green;\n' + d) + b + GB + bbl.TAIL for d, b in cands]
res = bbl.run(srcs)
rows = sorted([(rdiff(region(r[1])), r[0], i) for i, r in enumerate(res) if r])
for sc, tot, i in rows[:8]:
    print(sc, tot, cands[i][0].replace('\n', ' '), cands[i][1].strip()); print('   ', region(res[i][1])[2:8])
hits = [i for i, r in enumerate(res) if r and (lambda reg: any(l.startswith('addiu v1,v1,1') for l in reg[:5]) and [k for k,l in enumerate(reg) if l.startswith('addiu v1,v1,1')][0] < [k for k,l in enumerate(reg) if l.startswith('sll')][0])(region(r[1]))]
print('v1++ before sll hits:', len(hits))
for i in hits[:5]: print(cands[i][0].replace('\n',' '), cands[i][1].strip(), region(res[i][1])[2:8])
