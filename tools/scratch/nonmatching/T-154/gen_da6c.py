#!/usr/bin/env python3
"""Template generator for func_801BDA6C variants (random structural search)."""
import sys, os, random, re, difflib, tempfile, importlib.util, json, concurrent.futures as cf
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT / 'tools/scratch/nonmatching/T-154/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
FN = 'func_801BDA6C'
os.environ['PREFIX'] = '1'; os.environ['RONORM'] = '1'
HEAD = """typedef struct { u32 w0, w1; } T154Gfx;
typedef union { u64 align; u8 bytes[64]; } T154Mtx;
typedef struct { u32 image; f32 width; } T154Glyph;
extern void guScale(void *, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
extern T154Glyph D_80282A70[];
extern f32 D_80282D20;
f32 sinf(f32);
s32 strlen(u8 *);

"""
SITES = ['s1', 's2', 's3', 's4', 's5a', 's5b', 's6', 's7', 's8', 's9', 's10', 's11', 's12']
def body(name, opt):
    A = 'alpha' if opt['alpha'] != 'none' else 'a'
    C = 'color' if opt['color'] != 'none' else f'(r << 24) | (g << 16) | (b << 8) | {A}'
    B = {
     's1': ['cmd->w1 = 0;', 'cmd->w0 = 0xE7000000;'],
     's2': ['cmd->w0 = 0xFA000000;', f'cmd->w1 = {C};'],
     's3': ['cmd->w1 = 0xFFFDF6FB;', 'cmd->w0 = 0xFCFFFFFF;'],
     's4': ['cmd->w0 = 0xB6000000;', 'cmd->w1 = 0x22000;'],
     's5a': ['cmd->w0 = 0xB900031D;', 'cmd->w1 = 0x0F0A4000;'],
     's5b': ['cmd->w0 = 0xB900031D;', 'cmd->w1 = 0x5041C8;'],
     's6': ['cmd->w0 = 0x01020040;', 'cmd->w1 = (u32)&matrices[count++];'],
     's7': ['cmd->w0 = 0x01000040;', 'cmd->w1 = (u32)matrices;'],
     's8': ['cmd->w1 = 0;', 'cmd->w0 = 0xE7000000;'],
     's9': ['cmd->w0 = 0xFA000000;', f'cmd->w1 = ((u32)(sinf(D_80282D20) * 63.0f + 192.0f) << 24) | {A};'],
     's10': ['cmd->w0 = 0x06000000;', 'cmd->w1 = glyph->image;'],
     's11': ['cmd->w1 = 0;', 'cmd->w0 = 0xE7000000;'],
     's12': ['cmd->w0 = 0xFA000000;', f'cmd->w1 = {"color" if opt["color"] != "none" else "(r << 24) | (g << 16) | (b << 8) | " + A};'],
    }[name]
    return B
def site(opt, name, indent):
    lines = list(body(name, opt))
    if name in opt['flip']: lines = lines[::-1]
    pre = []
    if name == 's2':
        if opt['alpha'] != 'none': pre.append('alpha = a;')
        if opt['color'] != 'none': pre.append(f'color = (r << 24) | (g << 16) | (b << 8) | {"alpha" if opt["alpha"] != "none" else "a"};')
    pad = ' ' * indent
    st = opt['style'].get(name, 'blk'); one = name in opt['one']
    if st == 'blk':
        if one: return [pad + '{ T154Gfx *cmd = (*dl)++; ' + ' '.join(pre + lines) + ' }']
        return [pad + '{', pad + '  T154Gfx *cmd = (*dl)++;'] + [pad + '  ' + l for l in pre + lines] + [pad + '}']
    if one: return [pad + 'cmd = (*dl)++; ' + ' '.join(pre + lines)]
    return [pad + 'cmd = (*dl)++;'] + [pad + l for l in pre + lines]
def gen(opt):
    decl = ['T154Glyph *glyph;', 'u8 *p;', 's32 pulse' + (' = 2000' if opt['pinit'] == 'decl' else '') + ';', 's32 mode' + (' = 0' if opt['minit'] == 'decl' else '') + ';', 's32 count' + (' = 0' if opt['cinit'] == 'decl' else '') + ';', 's32 len;', 's32 i;']
    if opt['alpha'] != 'none': decl.append(f'{opt["alpha"]} alpha;')
    if opt['color'] != 'none': decl.append(f'{opt["color"]} color;')
    if opt['idx'] == 'func': decl.append('s8 index;')
    if opt['adv']: decl.append('f64 advance;')
    if opt['width'] == 'one': decl.append('f64 width;')
    if opt['width'] == 'three': decl += ['f64 width;', 'f64 width2;', 'f64 width3;']
    if 'shared' in opt['style'].values(): decl.append('T154Gfx *cmd;')
    if opt['order']:
        rnd = random.Random(opt['order']); rnd.shuffle(decl)
    L = ['  ' + d for d in decl]
    if opt['pinit'] == 'stmt': L.append('  pulse = 2000;')
    if opt['minit'] == 'stmt': L.append('  mode = 0;')
    if opt['cinit'] == 'stmt': L.append('  count = 0;')
    L += ['  len = strlen(text);', '  if (len == 0) {', '    return 0;', '  }', '  if (scale < 0.0f) {', '    pulse = (s32)(-scale - 1.0f);', '    scale = 1.0f;', '  }', '  if (scale != 1.0f) {', '    guScale(matrices, scale, scale, 1.0f);', '    count = 1;', '  }']
    for n in ['s1', 's2', 's3', 's4']: L += site(opt, n, 2)
    L += ['  if (a == 0xFF) {'] + site(opt, 's5a', 4) + ['  } else {'] + site(opt, 's5b', 4) + ['  }']
    L += ['  i = 0;', '  if (len > 0) {', '    p = text;', '    do {']
    idx = 'index' if opt['idx'] == 'func' else 'idx'
    if opt['idx'] == 'block': L += ['      s8 idx = *p - 0x20;']
    else: L += ['      index = *p - 0x20;']
    L += [f'      if ({idx} < 59 && {idx} >= 0 && (glyph = &D_80282A70[{idx}])->image) {{']
    w = opt['width']
    adv = 'advance' if opt['adv'] else 'scale'
    def wsel(v, a, b): return [f'        if (mode) {v} = {a};', f'        else {v} = {b};']
    if opt['adv']: L += ['        advance = scale;']
    if w == 'inline': L += [f'        x = x + {adv} * (mode ? 25.0 : glyph->width * 10.0f);']
    else: L += wsel('width', '25.0', 'glyph->width * 10.0f') + [f'        x = x + {adv} * width;']
    L += ['        guTranslate(&matrices[count], x, y, z);'] + site(opt, 's6', 8)
    L += ['        if (scale != 1.0f) {'] + site(opt, 's7', 10) + ['        }']
    L += ['        if (i == pulse) {'] + site(opt, 's8', 10) + ['          D_80282D20 = D_80282D20 + 0.4;'] + site(opt, 's9', 10) + ['        }']
    L += site(opt, 's10', 8)
    L += ['        if (i == pulse) {'] + site(opt, 's11', 10) + site(opt, 's12', 10) + ['        }']
    if w == 'inline': L += [f'        x = x + {adv} * (mode ? 25.0 : glyph->width * 10.0f);']
    else:
        v = 'width2' if w == 'three' else 'width'
        L += wsel(v, '25.0', 'glyph->width * 10.0f') + [f'        x = x + {adv} * {v};']
    L += [f'      }} else if ({idx} == 0x4A) {{', '        mode = 1;', '      } else {']
    if opt['adv']: L += ['        advance = scale;']
    if w == 'inline': L += [f'        x = x + {adv} * (mode ? 50.0 : 30.0);']
    else:
        v = 'width3' if w == 'three' else 'width'
        L += wsel(v, '50.0', '30.0') + [f'        x = x + {adv} * {v};']
    L += ['      }', '      i++;', '      p++;', '    } while (i != len);', '  }', '  return count;', '}']
    sig = 's32 func_801BDA6C(T154Gfx **dl, T154Mtx *matrices, u8 *text, f32 x, f32 y, f32 z,\n                  u8 r, u8 g, u8 b, u8 a, f32 scale)\n{\n'
    return HEAD + sig + '\n'.join(L) + '\n'
theirs = [cm.canon(t) for t in cm.target_raw(FN)]
theirs = [t for t in theirs if not t.startswith(('dlabel', 'enddlabel'))]
def M(x): return re.sub(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-7]|k[01]|gp|sp|fp|ra|f\d+)\b', 'R', x)
def score_src(src):
    with tempfile.TemporaryDirectory(prefix='g6c-') as d:
        p = Path(d) / 'draft.c'; p.write_text(src)
        try:
            source, tu = cm.build_source(FN, p, True)
            o = cm.compile_source(source, Path(d) / 'c.c')
        except SystemExit:
            return None
        pairs = cm.draft_raw(o, FN)
    mine = [cm.canon(cm.apply_relocs(i, r)) for _, i, r in pairs]
    sm = difflib.SequenceMatcher(None, [M(x) for x in theirs], [M(x) for x in mine], autojunk=False)
    rg = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    sm = difflib.SequenceMatcher(None, theirs, mine, autojunk=False)
    ex = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    frame = next((abs(int(re.search(r'-?\d+$', x).group())) for x in mine if x.startswith('addiu sp,sp,')), 0)
    return rg, ex, frame
def score(opt): return score_src(gen(opt))
def rand_opt(rnd):
    return dict(alpha=rnd.choice(['s32', 'u32', 'u8', 'none']), color=rnd.choice(['u32', 's32', 'none']), idx=rnd.choice(['block', 'func']), adv=rnd.choice([True, False]),
                width=rnd.choice(['one', 'three', 'inline', 'one']), pinit=rnd.choice(['decl', 'stmt']), minit=rnd.choice(['decl', 'stmt']), cinit=rnd.choice(['decl', 'stmt']),
                style={s: rnd.choice(['blk', 'blk', 'blk', 'shared']) for s in SITES}, one=[s for s in SITES if rnd.random() < 0.5], flip=[s for s in SITES if rnd.random() < 0.15],
                order=rnd.choice([0, 0] + list(range(1, 60))))
if __name__ == '__main__':
    rnd = random.Random(int(sys.argv[2])); n = int(sys.argv[1])
    opts = [rand_opt(rnd) for _ in range(n)]
    res = []
    with cf.ThreadPoolExecutor(14) as ex:
        for o, r in zip(opts, ex.map(score, opts)):
            if r: res.append((r, o))
    from collections import Counter
    print(len(res), 'ok', Counter(r[2] for r, o in res).most_common(6))
    res.sort(key=lambda t: (t[0][0], t[0][1]))
    for r, o in res[:6]: print(r, json.dumps(o)[:400])
    Path('/tmp/g6c_best.c').write_text(gen(res[0][1]))
