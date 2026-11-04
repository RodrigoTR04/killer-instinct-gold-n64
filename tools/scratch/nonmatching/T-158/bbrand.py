import sys, itertools, random
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
seed = int(sys.argv[1]); N = int(sys.argv[2])
rnd = random.Random(seed)
RAMP = {'red': ('(i - 8) << 3', '0', '0'), 'green': ('248', '(i - 40) << 3', '0'), 'blue': ('248', '248', '(i - 72) << 2')}
HI = {'red': 40, 'green': 72, 'blue': 128}
def macro_pk(r, g, b, style):
    if style == 0: return f'((({r}) << 8) & 0xF800) | ((({g}) << 3) & 0x7C0) | ((({b}) >> 2) & 0x3E) | 1'
    if style == 1: return f'((({r}) << 8) & 0xF800) | ((({g}) << 3) & 0x7C0) | ((({b}) >> 2) & 0x3E) | (a)'
    if style == 2: return f'(((({r}) << 8) & 0xF800) | ((({g}) << 3) & 0x7C0)) | ((({b}) >> 2) & 0x3E) | 1'
    return f'1 | ((({b}) >> 2) & 0x3E) | ((({g}) << 3) & 0x7C0) | ((({r}) << 8) & 0xF800)'
def gen_loop(name, shared):
    r, g, b = RAMP[name]; hi = HI[name]
    mode = shared['mode']
    stm = []
    vars_ = []
    if mode == 'vars':
        # which components are variables
        parts = {}
        order = ['r', 'g', 'b']
        if rnd.random() < 0.5: rnd.shuffle(order)
        for k, v in zip('rgb', (r, g, b)):
            if rnd.random() < 0.8 or v not in ('0', '248'):
                stm.append(f'{k} = {v};'); parts[k] = k
            else: parts[k] = v
        if shared['colvar']: pk = f'color = {macro_pk(parts["r"], parts["g"], parts["b"], shared["style"])};'; stm.append(pk); stm.append('*palette++ = color;')
        else: stm.append(f'*palette++ = {macro_pk(parts["r"], parts["g"], parts["b"], shared["style"])};')
    else:
        stm.append(f'*palette++ = {macro_pk(r, g, b, shared["style"])};')
    inc = rnd.choice(['i++;', 'i += 1;', 'i = i + 1;', '++i;'])
    form = shared['form']
    if form == 'for':
        return f'    for (; i < {hi}; i++) {{ ' + ' '.join(stm) + ' }\n'
    pos = rnd.choice([len(stm), len(stm), len(stm), max(1, len(stm) - 1), 1]) if len(stm) > 1 else 1
    stm.insert(min(pos, len(stm)), inc)
    if form == 'dw': return f'    if (i < {hi}) do {{ ' + ' '.join(stm) + f' }} while (i < {hi});\n'
    return f'    while (i < {hi}) {{ ' + ' '.join(stm) + ' }\n'
def gen():
    shared = {'mode': rnd.choice(['vars', 'inline', 'vars']), 'colvar': rnd.random() < 0.3, 'style': rnd.choice([0, 0, 1, 2, 3]), 'form': rnd.choice(['for', 'dw', 'while'])}
    ty = rnd.choice(['s32', 'u32', 's32', 'int'])
    cty = rnd.choice(['s32', 'u16', 's16', 'u32'])
    body = ''.join(gen_loop(n, shared) for n in ['red', 'green', 'blue'])
    decl = f'    {ty} r, g, b, a = 1;\n' + (f'    {cty} color;\n' if shared['colvar'] else '')
    return decl, body, shared
cands = [gen() for _ in range(N)]
srcs = [bbl.HEAD + bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i;\n' + d) + b + bbl.TAIL for d, b, _ in cands]
res = bbl.run(srcs)
rows = sorted([(r[0], i) for i, r in enumerate(res) if r])
for sc, i in rows[:6]:
    print(sc, cands[i][2], cands[i][0].replace('\n', ' ')); print(cands[i][1])
print('hist', {s: sum(1 for x in rows if x[0] == s) for s in sorted({x[0] for x in rows})[:6]})
