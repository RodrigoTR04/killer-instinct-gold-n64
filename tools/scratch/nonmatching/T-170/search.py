#!/usr/bin/env python3
"""General variant search: assemble BADEC source from parts, score each."""
import importlib.util, sys, tempfile, itertools, re, difflib, json
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)
REG = re.compile(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f\d+)\b')

fn = 'func_801BADEC'
HEAD = '''typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023StateBADEC;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F3AA0;
extern s32 D_801F3AA4;
extern u8 D_801F3AA8[];
'''
THEIRS = None


def target():
    global THEIRS
    if THEIRS is None:
        t = [cm.canon(x) for x in cm.target_raw(fn)]
        THEIRS = [x for x in t if not x.startswith(('dlabel', 'enddlabel'))]
    return THEIRS


def score(src_text, tag):
    p = ROOT / 'tools/scratch/nonmatching/T-170' / f'v_{tag}.c'
    p.write_text(src_text)
    try:
        r = screen.measure(fn, p)
        source, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(source, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    except Exception as e:
        return f'{tag:28s} ERROR {str(e)[-160:]}'
    th = target()
    sm = difflib.SequenceMatcher(None, th, mine, autojunk=False)
    bad = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    sm2 = difflib.SequenceMatcher(None, [REG.sub('R', x) for x in th], [REG.sub('R', x) for x in mine], autojunk=False)
    bad2 = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm2.get_opcodes() if t != 'equal')
    return f'{tag:28s} words={r["words"]:4d} bytes={r["compiled"]}/{r["original"]} diff={bad:3d} masked={bad2:3d}'


def build(opts):
    D = []
    if opts.get('scale_local'):
        D.append('    s32 scale = arg4->scale;\n')
    for v in opts['decls']:
        D.append(f'    s32 {v};\n')
    D.append('    s32 *counter0;\n    s32 *counter1;\n')
    for v in opts['decls2']:
        D.append(f'    s32 {v};\n')
    if opts.get('yoff_local'):
        D.append('    s32 yOffset = arg4->yOffset * 4;\n')
    if opts.get('temp_local'):
        D.append('    s32 xy = arg2 * 4;\n')
    L = list(D)
    L.append('\n    counter0 = &D_801F3AA0;\n    counter1 = &D_801F3AA4;\n')
    if opts.get('yoff_local'):
        L.append('    yOffset = arg4->yOffset * 4;\n')
    if opts.get('temp_local'):
        L.append('    xy = arg2 * 4;\n')
    sc = 'scale' if opts.get('scale_local') else 'arg4->scale'
    yo = 'yOffset' if opts.get('yoff_local') else '(arg4->yOffset * 4)'
    ay = 'xy' if opts.get('temp_local') else '(arg2 * 4)'
    EXPR = {
        'x': f'    x = (arg1 * 4) + ((s32) ((0x1CD - (arg5 * 4)) * {sc}) >> 0xA);\n',
        'y0': f'    y0 = {ay} + ((s32) ({sc} * 0x198) >> 0xA) + {yo};\n',
        'y1': f'    y1 = {ay} + ((s32) ({sc} * 0x1E3) >> 0xA) + {yo};\n',
    }
    for k in opts['order']:
        L.append(EXPR[k])
    L.append('''    if (arg5 != 0) {
        x = 0x9B0 - x;
    }
    temp_v0_2 = *counter0 + 1;
    *counter0 = temp_v0_2;
    if (temp_v0_2 >= 0x15) {
        if (temp_v0_2 >= 0x27) {
            *counter0 = 0;
        } else {
            *counter0 = temp_v0_2;
            func_801BC1B0(arg0, *(s32 *)(D_801F3AA8 + (((s32) (temp_v0_2 - 0x15) >> 1) * 4)), 2, 0x2C, 0x12, 0x2C, 0x12, 0, 0, 0x2B, 0x11, (f32) x, (f32) y0, (s32) %s, arg5);
        }
    }
    temp_v0_3 = *counter1 + 1;
    *counter1 = temp_v0_3;
    if (temp_v0_3 >= 0x1C) {
        if (temp_v0_3 >= 0x2E) {
            *counter1 = 0;
            return;
        }
        *counter1 = temp_v0_3;
        func_801BC1B0(arg0, *(s32 *)(D_801F3AA8 + (((s32) (temp_v0_3 - 0x1C) >> 1) * 4)) + 0x318, 2, 0x2C, 0x1A, 0x2C, 0x1A, 0, 0, 0x2B, 0x19, (f32) x, (f32) y1, (s32) %s, arg5);
    }
}
''' % (sc, sc))
    sig = 'void func_801BADEC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023StateBADEC *arg4, s32 arg5) {\n'
    return HEAD + '\n' + sig + ''.join(L)


def main():
    configs = json.loads(Path(sys.argv[1]).read_text())
    results = []
    for cfg in configs:
        txt = build(cfg)
        tag = cfg['tag']
        line = score(txt, tag)
        print(line, flush=True)
        results.append(line)
    print('\nBEST:')
    ok = [l for l in results if 'words=' in l]
    for line in sorted(ok, key=lambda s: int(re.search(r'words=\s*(\d+)', s).group(1)))[:6]:
        print(line)


if __name__ == '__main__':
    main()
