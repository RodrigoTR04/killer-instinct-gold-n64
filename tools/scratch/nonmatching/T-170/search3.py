#!/usr/bin/env python3
"""BADEC search v3: locals set x decl order x if-shape x store form."""
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
    p = ROOT / 'tools/scratch/nonmatching/T-170' / f't_{tag}.c'
    p.write_text(src_text)
    try:
        r = screen.measure(fn, p)
        source, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(source, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    except Exception as e:
        return (9999, tag, f'{tag:40s} ERROR {str(e)[-120:]}')
    th = target()
    sm = difflib.SequenceMatcher(None, th, mine, autojunk=False)
    bad = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    sm2 = difflib.SequenceMatcher(None, [REG.sub('R', x) for x in th], [REG.sub('R', x) for x in mine], autojunk=False)
    bad2 = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm2.get_opcodes() if t != 'equal')
    return (r['words'], tag, f'{tag:40s} w={r["words"]:4d} {r["compiled"]}/{r["original"]} diff={bad:3d} msk={bad2:3d}')


def build(o):
    L = ['typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023StateBADEC;\n',
         'extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);\n',
         'extern s32 D_801F3AA0;\nextern s32 D_801F3AA4;\nextern u8 D_801F3AA8[];\n\n',
         'void func_801BADEC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023StateBADEC *arg4, s32 arg5) {\n']
    D, I = [], []
    if 'scale' in o['locals']:
        D.append('    s32 scale = arg4->scale;\n')
    if 'yBase' in o['locals']:
        D.append('    s32 yBase = arg2 * 4;\n')
    if 'xBase' in o['locals']:
        D.append('    s32 xBase = arg1 * 4;\n')
    for v in o['order']:
        D.append(f'    s32 {v};\n')
    D.append('    s32 *counter0;\n    s32 *counter1;\n    s32 temp_v0_2;\n    s32 temp_v0_3;\n\n')
    I.append('    counter0 = &D_801F3AA0;\n    counter1 = &D_801F3AA4;\n')
    sc = 'scale' if 'scale' in o['locals'] else 'arg4->scale'
    ay = 'yBase' if 'yBase' in o['locals'] else '(arg2 * 4)'
    ax = 'xBase' if 'xBase' in o['locals'] else '(arg1 * 4)'
    E = {
        'x': f'    x = {ax} + ((s32) ((0x1CD - (arg5 * 4)) * {sc}) >> 0xA);\n',
        'y0': f'    y0 = {ay} + ((s32) ({sc} * 0x198) >> 0xA) + (arg4->yOffset * 4);\n',
        'y1': f'    y1 = {ay} + ((s32) ({sc} * 0x1E3) >> 0xA) + (arg4->yOffset * 4);\n',
    }
    for k in o['order']:
        I.append(E[k])
    if o['ifshape'] == 'a':
        I.append('    if (arg5 != 0) {\n        x = 0x9B0 - x;\n    }\n')
    elif o['ifshape'] == 'b':
        I.append('    if (arg5) {\n        x = 0x9B0 - x;\n    }\n')
    elif o['ifshape'] == 'c':
        I.append('    if (arg5 != 0) x = 0x9B0 - x;\n')
    st1 = {'ptr': '*counter0 = temp_v0_2;', 'sym': 'D_801F3AA0 = temp_v0_2;'}[o['store']]
    a3_1 = 'scale' if 'scale' in o['locals'] else '(s32) arg4->scale'
    I.append(f'''    temp_v0_2 = *counter0 + 1;
    *counter0 = temp_v0_2;
    if (temp_v0_2 >= 0x15) {{
        if (temp_v0_2 >= 0x27) {{
            *counter0 = 0;
        }} else {{
            {st1}
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
        *counter1 = temp_v0_3;
        func_801BC1B0(arg0, *(s32 *)(D_801F3AA8 + (((s32) (temp_v0_3 - 0x1C) >> 1) * 4)) + 0x318, 2, 0x2C, 0x1A, 0x2C, 0x1A, 0, 0, 0x2B, 0x19, (f32) x, (f32) y1, {a3_1}, arg5);
    }}
}}
''')
    return ''.join(L) + ''.join(D) + ''.join(I)


def main():
    out = []
    for order in itertools.permutations(['x', 'y0', 'y1']):
        for locals_ in (['scale'], ['scale', 'yBase'], ['scale', 'xBase'], ['scale', 'xBase', 'yBase'], ['scale', 'yBase', 'xBase']):
            if locals_[:2] == ['scale', 'yBase'] and 'yBase' not in locals_:
                continue
            for ifs in ('a', 'b', 'c'):
                for st in ('ptr', 'sym'):
                    tag = ''.join(k[0] for k in order) + f'_{"".join(sorted(l[0] for l in locals_))}_{ifs}_{st[0]}'
                    out.append((tag, dict(order=list(order), locals=locals_, ifshape=ifs, store=st)))
    res = []
    for tag, cfg in out:
        res.append(score(build(cfg), tag))
    for w, t, line in sorted(res)[:16]:
        print(line, flush=True)
    json.dump([l for _, _, l in res], open(ROOT/'tools/scratch/nonmatching/T-170/res3_badec.json', 'w'), indent=1)


main()
