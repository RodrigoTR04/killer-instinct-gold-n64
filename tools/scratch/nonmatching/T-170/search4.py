#!/usr/bin/env python3
"""BADEC search v4: independent declaration order x assignment order x scale-local position."""
import importlib.util, sys, tempfile, re, difflib, json, itertools
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)
fn = 'func_801BADEC'
THEIRS = None


def target():
    global THEIRS
    if THEIRS is None:
        t = [cm.canon(x) for x in cm.target_raw(fn)]
        THEIRS = [x for x in t if not x.startswith(('dlabel', 'enddlabel'))]
    return THEIRS


def score(src_text, tag):
    p = ROOT / 'tools/scratch/nonmatching/T-170' / f'u_{tag}.c'
    p.write_text(src_text)
    try:
        r = screen.measure(fn, p)
        source, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(source, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    except Exception as e:
        return (9999, 999, tag, f'{tag:36s} ERROR {str(e)[-120:]}')
    th = target()
    sm = difflib.SequenceMatcher(None, th, mine, autojunk=False)
    bad = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    return (r['words'], bad, tag, f'{tag:36s} w={r["words"]:4d} {r["compiled"]}/{r["original"]} diff={bad:3d}')


def build(o):
    L = ['typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023StateBADEC;\n',
         'extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);\n',
         'extern s32 D_801F3AA0;\nextern s32 D_801F3AA4;\nextern u8 D_801F3AA8[];\n\n',
         'void func_801BADEC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023StateBADEC *arg4, s32 arg5) {\n']
    D = []
    if o['spos'] == 0:
        D.append('    s32 scale = arg4->scale;\n')
    for v in o['dorder']:
        D.append(f'    s32 {v};\n')
        if o['spos'] == 1 and v == 'x':
            D.append('    s32 scale = arg4->scale;\n')
    D.append('    s32 *counter0;\n    s32 *counter1;\n    s32 temp_v0_2;\n    s32 temp_v0_3;\n\n')
    I = ['    counter0 = &D_801F3AA0;\n    counter1 = &D_801F3AA4;\n']
    if o['spos'] == 2:
        I.append('    scale = arg4->scale;\n')
    E = {
        'x': '    x = (arg1 * 4) + ((s32) ((0x1CD - (arg5 * 4)) * scale) >> 0xA);\n',
        'y0': '    y0 = (arg2 * 4) + ((s32) (scale * 0x198) >> 0xA) + (arg4->yOffset * 4);\n',
        'y1': '    y1 = (arg2 * 4) + ((s32) (scale * 0x1E3) >> 0xA) + (arg4->yOffset * 4);\n',
    }
    for k in o['aorder']:
        I.append(E[k])
    I.append('    if (arg5 != 0) {\n        x = 0x9B0 - x;\n    }\n')
    a3 = 'scale'
    I.append(f'''    temp_v0_2 = *counter0 + 1;
    *counter0 = temp_v0_2;
    if (temp_v0_2 >= 0x15) {{
        if (temp_v0_2 >= 0x27) {{
            *counter0 = 0;
        }} else {{
            D_801F3AA0 = temp_v0_2;
            func_801BC1B0(arg0, *(s32 *)(D_801F3AA8 + (((s32) (temp_v0_2 - 0x15) >> 1) * 4)), 2, 0x2C, 0x12, 0x2C, 0x12, 0, 0, 0x2B, 0x11, (f32) x, (f32) y0, {a3}, arg5);
        }}
    }}
    temp_v0_3 = *counter1 + 1;
    *counter1 = temp_v0_3;
    if (temp_v0_3 >= 0x1C) {{
        if (temp_v0_3 >= 0x2E) {{
            *counter1 = 0;
            return;
        }}
        D_801F3AA4 = temp_v0_3;
        func_801BC1B0(arg0, *(s32 *)(D_801F3AA8 + (((s32) (temp_v0_3 - 0x1C) >> 1) * 4)) + 0x318, 2, 0x2C, 0x1A, 0x2C, 0x1A, 0, 0, 0x2B, 0x19, (f32) x, (f32) y1, {a3}, arg5);
    }}
}}
''')
    return ''.join(L) + ''.join(D) + ''.join(I)


def main():
    res = []
    for dorder in itertools.permutations(['x', 'y0', 'y1']):
        for aorder in itertools.permutations(['x', 'y0', 'y1']):
            for spos in (0, 1, 2):
                tag = ''.join(k[0] for k in dorder) + '|' + ''.join(k[0] for k in aorder) + f'|{spos}'
                res.append(score(build(dict(dorder=list(dorder), aorder=list(aorder), spos=spos)), tag.replace('|', '_')))
    for w, b, t, line in sorted(res)[:20]:
        print(line, flush=True)
    json.dump([l for _, _, _, l in res], open(ROOT/'tools/scratch/nonmatching/T-170/res4_badec.json', 'w'), indent=1)


main()
