#!/usr/bin/env python3
"""Template generator for func_801BD640 variants."""
import sys, os, random, re, difflib, tempfile, importlib.util, json, concurrent.futures as cf
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT / 'tools/scratch/nonmatching/T-154/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
FN = 'func_801BD640'
os.environ['PREFIX'] = '1'; os.environ['RONORM'] = '1'
HEAD = """typedef struct { u32 w0, w1; } T154Gfx;
typedef union { u64 align; u8 bytes[64]; } T154Mtx;
typedef struct { u32 image; f32 width; } T154Glyph;
extern void guScale(void *, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
extern T154Glyph D_80282A70[];

"""
SITES = {
 'c1': ['cmd->w0 = 0xE7000000;', 'cmd->w1 = 0;'],
 'c2': ['cmd->w0 = 0xFA000000;', 'cmd->w1 = (r << 24) | (g << 16) | (b << 8) | A;'],
 'c3': ['cmd->w0 = 0xFCFFFFFF;', 'cmd->w1 = 0xFFFDF6FB;'],
 'c4': ['cmd->w0 = 0xB6000000;', 'cmd->w1 = 0x20000;'],
 'c5a': ['cmd->w0 = 0xB900031D;', 'cmd->w1 = 0x552048;'],
 'c5b': ['cmd->w0 = 0xB900031D;', 'cmd->w1 = 0x5041C8;'],
 'c6': ['cmd->w0 = 0x01020040;', 'cmd->w1 = (u32)matrices;'],
 'c7': ['cmd->w0 = 0x01040040;', 'cmd->w1 = (u32)&matrices[count];'],
 'c8': ['cmd->w0 = 0x06000000;', 'cmd->w1 = glyph->image;'],
 'c9': ['cmd->w0 = 0xBD000000;', 'cmd->w1 = 0;'],
}
def site(opt, name, indent):
    st = opt['style'].get(name, 'blk'); one = name in opt['one']; flip = name in opt['flip']
    lines = [l.replace('A', 'alpha' if opt['alpha'] != 'none' else 'a') if name == 'c2' else l for l in SITES[name]]
    if name == 'c2': lines = [l.replace('| alpha;', '| ' + ('alpha' if opt['alpha'] != 'none' else 'a') + ';').replace('| A;', '| ' + ('alpha' if opt['alpha'] != 'none' else 'a') + ';') for l in SITES[name]]
    if flip: lines = lines[::-1]
    if name == 'c9': lines = ['count++;'] + lines
    pad = ' ' * indent
    if st == 'blk':
        if one: return [pad + '{ T154Gfx *cmd = (*dl)++; ' + ' '.join(lines) + ' }']
        return [pad + '{', pad + '  T154Gfx *cmd = (*dl)++;'] + [pad + '  ' + l for l in lines] + [pad + '}']
    if one: return [pad + 'cmd = (*dl)++; ' + ' '.join(lines)]
    return [pad + 'cmd = (*dl)++;'] + [pad + l for l in lines]
def gen(opt):
    decl = ['T154Glyph *glyph;', 'f32 pos' + (' = x' if opt['pos'] == 'decl' else '') + ';', 's32 count;', 's32 mode' + (' = 0' if opt['mode'] == 'decl' else '') + ';', 'u8 *p;', 'u8 index;']
    if opt['alpha'] == 'u8': decl.append('u8 alpha = a;')
    elif opt['alpha'] == 'u32': decl.append('u32 alpha = a;')
    elif opt['alpha'] == 's32': decl.append('s32 alpha = a;')
    w = opt['width']
    if w == 'one': decl.append('f64 width;')
    elif w == 'three': decl += ['f64 width;', 'f64 width2;', 'f64 width3;']
    if 'shared' in opt['style'].values(): decl.append('T154Gfx *cmd;')
    if opt['order']:
        rnd = random.Random(opt['order']); rnd.shuffle(decl)
    L = ['  ' + d for d in decl]
    if opt['pos'] == 'stmt': L.append('  pos = x;')
    if opt['mode'] == 'stmt': L.append('  mode = 0;')
    for n in ['c1', 'c2', 'c3', 'c4']: L += site(opt, n, 2)
    L += ['  if (' + ('alpha' if opt['alpha'] != 'none' else 'a') + ' == 0xFF) {'] + site(opt, 'c5a', 4) + ['  } else {'] + site(opt, 'c5b', 4) + ['  }']
    L += ['  guScale(matrices, 0.75f, 0.75f, 1.0f);'] + site(opt, 'c6', 2) + ['  count = 1;']
    if opt['loop'] == 'for': L += ['  for (p = text; *p; p++) {']
    else: L += ['  p = text;', '  while (*p) {']
    L += ['    index = *p - 0x20;', '    if (index < 59 && index > 0 && (glyph = &D_80282A70[index])->image) {']
    def wsel(var, a, b): return [f'      if (mode) {var} = {a};', f'      else {var} = {b};']
    if w == 'inline':
        L += ['      pos = pos + (mode ? (f64)mode * 5.0 : (f64)(glyph->width * 10.0f));']
    else:
        L += wsel('width', 'mode * 5.0', 'glyph->width * 10.0f') + ['      pos = pos + width;']
    L += ['      guTranslate(&matrices[count], pos, y, z);'] + site(opt, 'c7', 6) + site(opt, 'c8', 6) + site(opt, 'c9', 6)
    if w == 'inline':
        L += ['      pos = pos + (mode ? 25.0 : (f64)(glyph->width * 10.0f));']
    else:
        v = 'width2' if w == 'three' else 'width'
        L += wsel(v, '25.0', 'glyph->width * 10.0f') + [f'      pos = pos + {v};']
    L += ['    } else if (*p == 9) {', '      pos = x + ((s32)(f32)((pos - x) / 400.0) * 20 + 20) * 2.5 * 8.0;', '    } else if (*p == 0x6A) {', '      mode = 5;', '    } else if (*p == 0x6B) {', '      mode = 2;', '    } else {']
    if w == 'inline':
        L += ['      pos = pos + (mode ? 50.0 : 30.0);']
    else:
        v = 'width3' if w == 'three' else 'width'
        L += wsel(v, '50.0', '30.0') + [f'      pos = pos + {v};']
    L += ['    }']
    if opt['loop'] == 'while': L += ['    p++;']
    L += ['  }', '  return count;', '}']
    sig = 's32 func_801BD640(T154Gfx **dl, T154Mtx *matrices, u8 *text, f32 x, f32 y, f32 z,\n                  u8 r, u8 g, u8 b, u8 a)\n{\n'
    return HEAD + sig + '\n'.join(L) + '\n'
theirs = [cm.canon(t) for t in cm.target_raw(FN)]
theirs = [t for t in theirs if not t.startswith(('dlabel', 'enddlabel'))]
def M(x): return re.sub(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-7]|k[01]|gp|sp|fp|ra|f\d+)\b', 'R', x)
def score_src(src):
    with tempfile.TemporaryDirectory(prefix='g640-') as d:
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
    sites = list(SITES)
    return dict(alpha=rnd.choice(['u8', 'u8', 'u32', 's32', 'none']), width=rnd.choice(['one', 'three', 'inline', 'one']), pos=rnd.choice(['decl', 'stmt']), mode=rnd.choice(['decl', 'decl', 'stmt']),
                loop=rnd.choice(['for', 'while']), style={s: rnd.choice(['blk', 'blk', 'blk', 'shared']) for s in sites}, one=[s for s in sites if rnd.random() < 0.5],
                flip=[s for s in sites if rnd.random() < 0.2], order=rnd.choice([0, 0] + list(range(1, 60))))
if __name__ == '__main__':
    rnd = random.Random(int(sys.argv[2])); n = int(sys.argv[1])
    opts = [rand_opt(rnd) for _ in range(n)]
    res = []
    with cf.ThreadPoolExecutor(14) as ex:
        for o, r in zip(opts, ex.map(score, opts)):
            if r: res.append((r, o))
    res.sort(key=lambda t: (t[0][0], t[0][1]))
    print(len(res), 'ok')
    for r, o in res[:6]: print(r, json.dumps(o)[:400])
    res.sort(key=lambda t: (t[0][1], t[0][0]))
    print('by exact')
    for r, o in res[:6]: print(r, json.dumps(o)[:400])
    Path('/tmp/g640_best.c').write_text(gen(res[0][1]))
