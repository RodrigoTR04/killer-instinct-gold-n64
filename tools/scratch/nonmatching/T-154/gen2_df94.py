#!/usr/bin/env python3
"""Template generator for func_801BDF94 variants; random search on structural options."""
import sys, os, random, re, difflib, tempfile, importlib.util, itertools, json, concurrent.futures as cf
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT / 'tools/scratch/nonmatching/T-154/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
FN = 'func_801BDF94'
HEAD = Path(ROOT / 'tools/scratch/nonmatching/T-154/wdf94/blk3.c').read_text().split('s32 func_801BDF94')[0]

def cmdsite(opt, name, body, indent):
    """emit one display-list command; opt['cmd'] in {'blk','shared','sepK'}"""
    style = opt['cmdstyle'].get(name, 'blk')
    if name in opt.get('flip', ()): body = list(reversed(body))
    pad = ' ' * indent
    lines = body
    one = name in opt.get('oneline', ())
    if style == 'blk':
        if one:
            return [pad + '{ T023801BDF94Gfx *g = (*dl)++; ' + ' '.join(lines) + ' }']
        return [pad + '{', pad + '    T023801BDF94Gfx *g = (*dl)++;'] + [pad + '    ' + l for l in lines] + [pad + '}']
    var = 'cmd' if style == 'shared' else style
    if one:
        return [pad + f'{var} = (*dl)++; ' + ' '.join(l.replace('g->', var + '->') for l in lines)]
    return [pad + f'{var} = (*dl)++;'] + [pad + l.replace('g->', var + '->') for l in lines]

def gen(opt):
    L = []
    I = '    '
    decl = []
    # declarations
    if opt['refl'] == 'func': decl.append('T079Matrix reflection;')
    decl += ['T023801BDF94Glyph *glyph;', 'T023801BDF94Gfx *cmd;', 'T023801BDF94Gfx *cmd2;', 'T023801BDF94Gfx *cmd3;']
    decl += ['s32 fixed = 0;', 's32 count = 0;', 's32 index;', 's32 length;']
    if opt.get('tick','ptr') == 'ptr': decl.append('s32 *tick;')
    if opt.get('len','idx') == 'ptr': decl.append('u8 *end;')
    if opt['char'] == 'func': decl.append('s8 character;')
    if opt['sine'] == 'func': decl.append('f32 sine;')
    if opt['rot'] == 'func': decl.append('f32 rotation;')
    for n in opt['f64']: decl.append(f'f64 {n};')
    # drop unused cmd vars
    used = set(opt['cmdstyle'].values())
    for v in ('cmd', 'cmd2', 'cmd3'):
        key = 'shared' if v == 'cmd' else v
        if key not in used: decl = [d for d in decl if not d.endswith(f' *{v};')]
    order = opt['order']
    if opt.get('explicit'):
        def key(d):
            nm = re.search(r'(\w+)(\[\d*\])?( = [^;]+)?;$', d).group(1)
            return opt['explicit'].index(nm) if nm in opt['explicit'] else 99
        decl.sort(key=key)
    elif order: 
        rnd = random.Random(order); rnd.shuffle(decl)
    for d in decl: L.append(I + d)
    L.append('')
    L += [I + 'if (scale != 1.0f && scale != -1.0f) {', I*2 + 'if (scale < 0.0f) {', I*3 + 'guScale(matrices, 1.0f, -scale, 1.0f);', I*3 + 'scale = 0.999f;', I*2 + '} else {', I*3 + 'guScale(matrices, scale, scale, 1.0f);', I*2 + '}', I*2 + 'count = 1;', I + '}']
    L += [I + 'if (mode == 2) {', I*2 + 'guRotate(&matrices[count], angle, 0.0f, 1.0f, 0.0f);']
    L += cmdsite(opt, 's1', ['g->w1 = (u32)&matrices[count++];', 'g->w0 = 0x01020040;'], 8)
    L += [I + '}']
    K = '0.017453292519943295'
    TK = '*tick' if opt.get('tick','ptr') == 'ptr' else 'D_80282DC0'
    if opt.get('tick','ptr') == 'ptr': L += [I + 'tick = &D_80282DC0;']
    refl_in = opt['refl'] == 'block'
    sinedecl = opt['sine']
    if refl_in:
        L += [I + '{', I*2 + 'T079Matrix reflection;']
        if sinedecl == 'block': L += [I*2 + 'f32 sine;']
        P = I*2
    else:
        P = I
    if sinedecl == 'inline':
        L += [P + f'guLookAtReflect(&reflection, D_802D36B0, sinf({TK} * {K}) * 60.0f,', P + f'                cosf({TK} * {K}) * 60.0f,', P + '                220.0f, 6.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);']
    else:
        L += [P + f'sine = sinf({TK} * {K});', P + 'guLookAtReflect(&reflection, D_802D36B0, sine * 60.0f,', P + f'                cosf({TK} * {K}) * 60.0f,', P + '                220.0f, 6.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);']
    if refl_in: L += [I + '}']
    L += cmdsite(opt, 's2', ['g->w1 = (u32)D_802D36B0;', 'g->w0 = 0x03840010;'], 4)
    L += cmdsite(opt, 's3', ['g->w0 = 0x03820010;', 'g->w1 = (u32)D_802D36C0;'], 4)
    L += cmdsite(opt, 's4', ['g->w0 = 0x06000000;', 'g->w1 = (u32)D_80282D28;'], 4)
    L += [I + ('(*tick)++;' if opt.get('tick','ptr') == 'ptr' else 'D_80282DC0++;')]
    if opt.get('len','idx') == 'ptr':
        L += [I + 'length = 0;', I + 'end = text;', I + 'while (*end) {', I*2 + 'length++;', I*2 + 'end++;', I + '}', I + 'angle -= length * 30;']
    else:
        L += [I + 'for (length = 0; text[length]; length++) {', I + '}', I + 'angle -= length * 30;']
    L += [I + 'for (index = 0; text[index]; index++) {']
    J = I * 2
    if opt['char'] == 'loop': L += [J + 's8 character;']
    if opt['rot'] == 'loop': L += [J + 'f32 rotation;']
    L += [J + "character = text[index] - 'A';", J + 'if (character == -19) character = 26;']
    L += [J + 'if (character < 27 && character >= 0 &&', J + '    (glyph = &D_80282C48[character])->image) {']
    K2 = J + I
    L += [K2 + 'rotation = 0.0f;']
    f = opt['f64']
    if opt['adv'] == 'var':
        L += [K2 + 'advance = scale;']; adv = 'advance'
    else: adv = 'scale'
    def wexpr(fx, gl): return f'(fixed ? {fx} : glyph->width * {gl})'
    if 'width' in f:
        L += [K2 + 'if (fixed) width = 32.22;', K2 + 'else width = glyph->width * 9.0f;', K2 + f'x = x + {adv} * width;']
    else:
        L += [K2 + (f'x = x + {wexpr("32.22","9.0f")} * {adv};' if opt.get('mulord') == 'wf' else f'x = x + {adv} * {wexpr("32.22","9.0f")};')]
    L += [K2 + 'if (mode == 1) {', K2 + '    rotation = index * 30 + angle;', K2 + '    if (rotation < 360.0f) {', K2 + '        z -= (rotation - 360.0f) / 8;', K2 + '        y += (rotation - 360.0f) / 32;', K2 + '    }', K2 + '}']
    L += [K2 + 'guTranslate(&matrices[count], x, y, z);']
    L += [K2 + 'if (mode == 2) {'] + cmdsite(opt, 's5', ['g->w1 = (u32)&matrices[count++];', 'g->w0 = 0x01040040;'], 16) + [K2 + '} else {'] + cmdsite(opt, 's6', ['g->w1 = (u32)&matrices[count++];', 'g->w0 = 0x01020040;'], 16) + [K2 + '}']
    L += [K2 + 'if (rotation < 360.0f && mode == 1) {', K2 + '    guRotate(&matrices[count], rotation, 1.0f, 0.0f, 0.0f);']
    L += cmdsite(opt, 's7', ['g->w1 = (u32)&matrices[count++];', 'g->w0 = 0x01000040;'], 16) + [K2 + '}']
    L += [K2 + 'if (scale != 1.0f) {'] + cmdsite(opt, 's8', ['g->w1 = (u32)matrices;', 'g->w0 = 0x01000040;'], 16) + [K2 + '}']
    L += cmdsite(opt, 's9', ['g->w0 = 0x06000000;', 'g->w1 = glyph->image;'], 12)
    if 'width2' in f or os.environ.get('W2SHARE') and 'width' in f:
        w2 = 'width2' if 'width2' in f else 'width'
        L += [K2 + f'if (fixed) {w2} = 35.8;', K2 + f'else {w2} = glyph->width * 10.0f;', K2 + f'x = x + {adv} * {w2};']
    else:
        L += [K2 + (f'x = x + {wexpr("35.8","10.0f")} * {adv};' if opt.get('mulord') == 'wf' else f'x = x + {adv} * {wexpr("35.8","10.0f")};')]
    L += [K2 + 'if (mode == 2) {'] + cmdsite(opt, 's10', ['g->w1 = 0;', 'g->w0 = 0xBD000000;'], 16) + [K2 + '}']
    L += [J + '} else if (character == 41) {', J + '    fixed = 1;', J + '} else {']
    if 'width3' in f or os.environ.get('W3SHARE') and 'width' in f:
        w3 = 'width3' if 'width3' in f else 'width'
        L += [J + f'    if (fixed) {w3} = 68.02;', J + f'    else {w3} = 28.5;', J + f'    x += scale * {w3};']
    else:
        L += [J + ('    x += (fixed ? 68.02 : 28.5) * scale;' if opt.get('mulord') == 'wf' else '    x += scale * (fixed ? 68.02 : 28.5);')]
    L += [J + '}', I + '}', I + 'return count;']
    src = HEAD + 's32 func_801BDF94(T023801BDF94Gfx **dl, T079Matrix *matrices, u8 *text,\n                    f32 x, f32 y, f32 z, s32 mode, f32 scale, f32 angle)\n{\n' + '\n'.join(L) + '\n}\n'
    return src

theirs = [cm.canon(t) for t in cm.target_raw(FN)]
theirs = [t for t in theirs if not t.startswith(('dlabel', 'enddlabel'))]
def M(x): return re.sub(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-7]|k[01]|gp|sp|fp|ra|f\d+)\b', 'R', x)
def score(opt):
    src = gen(opt)
    with tempfile.TemporaryDirectory(prefix='g94-') as d:
        p = Path(d) / 'draft.c'; p.write_text(src)
        try:
            source, tu = cm.build_source(FN, p)
            o = cm.compile_source(source, Path(d) / 'c.c')
        except SystemExit:
            return None
        pairs = cm.draft_raw(o, FN)
    mine = [cm.canon(cm.apply_relocs(i, r)) for _, i, r in pairs]
    a = [M(t) for t in theirs]; b = [M(t) for t in mine]
    sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
    reg = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    sm = difflib.SequenceMatcher(None, theirs, mine, autojunk=False)
    ex = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    shared = any(re.search(r'addiu \w+,\w+,%lo\(0x80282dc0\)', x) for x in mine)
    frame = next((abs(int(re.search(r'-?\d+$', x).group())) for x in mine if x.startswith('addiu sp,sp,')), 0)
    refl = next((int(re.search(r'(\d+)$', x).group()) for x in mine if x.startswith('addiu a0,sp,')), 0)
    rot = next((int(re.search(r'(\d+)\(sp\)$', x).group(1)) for x in mine if x.startswith('swc1 f12,')), 0)
    return reg, ex, shared, frame, refl, rot

def rand_opt(rnd):
    sites = ['s1','s2','s3','s4','s5','s6','s7','s8','s9','s10']
    cs = {}
    for s in sites:
        r = rnd.random()
        cs[s] = 'blk' if (r < 0.6 or os.environ.get('FORCE_BLK')) else ('shared' if r < 0.8 else rnd.choice(['cmd2','cmd3']))
    return dict(refl=rnd.choice(['func','block']), sine=rnd.choice(['func','inline','block']), char=rnd.choice(['func','loop']), rot=rnd.choice(['func','loop']),
                f64=rnd.sample(['advance','width','width2','width3'], rnd.randint(int(os.environ.get('F64MIN','0')),4)), adv=rnd.choice(['var','none']), cmdstyle=cs, order=rnd.choice([0,0,0]+list(range(1,40))))
def fix(opt):
    if os.environ.get('F64FIX') is not None:
        opt['f64'] = [x for x in os.environ['F64FIX'].split(',') if x]
    if opt['sine']=='block' and opt['refl']!='block': opt['sine']='func'
    if 'advance' in opt['f64'] and opt['adv']!='var': opt['adv']='var'
    if opt['adv']=='var' and 'advance' not in opt['f64']: opt['f64'].append('advance')
    return opt
if __name__ == '__main__':
    n = int(sys.argv[1]); seed = int(sys.argv[2]) if len(sys.argv) > 2 else 1
    rnd = random.Random(seed)
    opts = [fix(rand_opt(rnd)) for _ in range(n)]
    results = []
    with cf.ThreadPoolExecutor(12) as ex:
        for opt, r in zip(opts, ex.map(score, opts)):
            if r: results.append((r, opt))
    results.sort(key=lambda t: (t[0][0], t[0][1]))
    for r, opt in results[:8]:
        print(r, json.dumps(opt))
    best = results[0][1]
    Path('/tmp/df94_best.c').write_text(gen(best))
    print('frame320:'); [print(r, json.dumps(o)) for r, o in results if r[3] == 320 and r[4] == 232 and r[5] == 212][:5]


def flip_search(base_opt, n=1024, jobs=12):
    sites = ['s1','s2','s3','s4','s5','s6','s7','s8','s9','s10']
    opts = []
    for m in range(1 << len(sites)):
        o = dict(base_opt); o['flip'] = [s for i, s in enumerate(sites) if m >> i & 1]; opts.append(o)
    res = []
    with cf.ThreadPoolExecutor(jobs) as ex:
        for o, r in zip(opts, ex.map(score, opts)):
            if r: res.append((r, o))
    res.sort(key=lambda t: (t[0][0], t[0][1]))
    return res
