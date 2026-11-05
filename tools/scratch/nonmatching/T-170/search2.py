#!/usr/bin/env python3
"""Search BADEC with scale-local + store-form + tail-order knobs."""
import importlib.util, sys, tempfile, re, difflib, json, itertools
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)
REG = re.compile(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f\d+)\b')
fn = 'func_801BADEC'
THEIRS = None


def target():
    global THEIRS
    if THEIRS is None:
        t = [cm.canon(x) for x in cm.target_raw(fn)]
        THEIRS = [x for x in t if not x.startswith(('dlabel', 'enddlabel'))]
    return THEIRS


def score(src_text, tag):
    p = ROOT / 'tools/scratch/nonmatching/T-170' / f's_{tag}.c'
    p.write_text(src_text)
    try:
        r = screen.measure(fn, p)
        source, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(source, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    except Exception as e:
        return (9999, tag, f'{tag:34s} ERROR {str(e)[-140:]}')
    th = target()
    sm = difflib.SequenceMatcher(None, th, mine, autojunk=False)
    bad = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    sm2 = difflib.SequenceMatcher(None, [REG.sub('R', x) for x in th], [REG.sub('R', x) for x in mine], autojunk=False)
    bad2 = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm2.get_opcodes() if t != 'equal')
    return (r['words'], tag, f'{tag:34s} words={r["words"]:4d} bytes={r["compiled"]}/{r["original"]} diff={bad:3d} masked={bad2:3d}')


def build(o):
    L = ['typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023StateBADEC;\n',
         'extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);\n',
         'extern s32 D_801F3AA0;\nextern s32 D_801F3AA4;\nextern u8 D_801F3AA8[];\n\n',
         'void func_801BADEC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023StateBADEC *arg4, s32 arg5) {\n']
    if o['scale']:
        L.append('    s32 scale = arg4->scale;\n')
    for v in ['x', 'y0', 'y1']:
        L.append(f'    s32 {v};\n')
    L.append('    s32 *counter0;\n    s32 *counter1;\n    s32 temp_v0_2;\n    s32 temp_v0_3;\n\n')
    L.append('    counter0 = &D_801F3AA0;\n    counter1 = &D_801F3AA4;\n')
    sc = 'scale' if o['scale'] else 'arg4->scale'
    E = {
        'x': f'    x = (arg1 * 4) + ((s32) ((0x1CD - (arg5 * 4)) * {sc}) >> 0xA);\n',
        'y0': f'    y0 = (arg2 * 4) + ((s32) ({sc} * 0x198) >> 0xA) + (arg4->yOffset * 4);\n',
        'y1': f'    y1 = (arg2 * 4) + ((s32) ({sc} * 0x1E3) >> 0xA) + (arg4->yOffset * 4);\n',
    }
    if o.get('yorder') == 'y1y0':
        E['y0'], E['y1'] = E['y1'], E['y0']
    for k in o['order']:
        L.append(E[k])
    L.append('    if (arg5 != 0) {\n        x = 0x9B0 - x;\n    }\n')
    a3_1 = 'scale' if o['c1'] == 'local' else '(s32) arg4->scale'
    a3_2 = 'scale' if o['c2'] == 'local' else '(s32) arg4->scale'
    st = {'ptr': '*counter0 = temp_v0_2;', 'sym': 'D_801F3AA0 = temp_v0_2;', 'idx': 'counter0[0] = temp_v0_2;'}[o['store']]
    st2 = {'ptr': '*counter1 = temp_v0_3;', 'sym': 'D_801F3AA4 = temp_v0_3;'}[o['store2']]
    L.append('    temp_v0_2 = *counter0 + 1;\n    *counter0 = temp_v0_2;\n')
    L.append(f'''    if (temp_v0_2 >= 0x15) {{
        if (temp_v0_2 >= 0x27) {{
            *counter0 = 0;
        }} else {{
            {st}
            func_801BC1B0(arg0, *(s32 *)(D_801F3AA8 + (((s32) (temp_v0_2 - 0x15) >> 1) * 4)), 2, 0x2C, 0x12, 0x2C, 0x12, 0, 0, 0x2B, 0x11, (f32) x, (f32) y0, {a3_1}, arg5);
        }}
    }}
    temp_v0_3 = *counter1 + 1;
    *counter1 = temp_v0_3;
    if (temp_v0_3 >= 0x1C) {{
        if (temp_v0_3 >= 0x2E) {{
            *counter1 = 0;
            return;
        }}
        {st2}
        func_801BC1B0(arg0, *(s32 *)(D_801F3AA8 + (((s32) (temp_v0_3 - 0x1C) >> 1) * 4)) + 0x318, 2, 0x2C, 0x1A, 0x2C, 0x1A, 0, 0, 0x2B, 0x19, (f32) x, (f32) y1, {a3_2}, arg5);
    }}
}}
''')
    return ''.join(L)


def main():
    cfgs = []
    for order in itertools.permutations(['x', 'y0', 'y1']):
        for sc in (0, 1):
            for c1 in ('local', 'expr'):
                for c2 in ('local', 'expr'):
                    for store in ('ptr', 'sym', 'idx'):
                        for store2 in ('ptr', 'sym'):
                            tag = ''.join(o[0] if o[0] != 'y' else o for o in order) + f'_{sc}{c1[0]}{c2[0]}{store[0]}{store2[0]}'
                            cfgs.append(dict(tag=tag, order=list(order), scale=sc, c1=c1, c2=c2, store=store, store2=store2))
    res = []
    for c in cfgs:
        res.append(score(build(c), c['tag']))
    for w, t, line in sorted(res)[:10]:
        print(line)
    json.dump([l for _, _, l in res], open(ROOT/'tools/scratch/nonmatching/T-170/res_badec.json', 'w'), indent=1)


main()
