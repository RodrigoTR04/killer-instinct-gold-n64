#!/usr/bin/env python3
"""Permutation search over coordinate statements + declarations for BADEC-like functions."""
import importlib.util, sys, tempfile, itertools, re
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)

HEAD = '''typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023StateBADEC;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F3AA0;
extern s32 D_801F3AA4;
extern u8 D_801F3AA8[];
'''

STMT = {
 'x': '    x = (arg1 * 4) + ((s32) ((0x1CD - (arg5 * 4)) * arg4->scale) >> 0xA);\n',
 'y0': '    y0 = (arg2 * 4) + ((s32) (arg4->scale * 0x198) >> 0xA) + (arg4->yOffset * 4);\n',
 'y1': '    y1 = (arg2 * 4) + ((s32) (arg4->scale * 0x1E3) >> 0xA) + (arg4->yOffset * 4);\n',
}

TAIL = '''    if (arg5 != 0) {
        x = 0x9B0 - x;
    }
    temp_v0_2 = *counter0 + 1;
    *counter0 = temp_v0_2;
    if (temp_v0_2 >= 0x15) {
        if (temp_v0_2 >= 0x27) {
            *counter0 = 0;
        } else {
            *counter0 = temp_v0_2;
            func_801BC1B0(arg0, *(s32 *)(D_801F3AA8 + (((s32) (temp_v0_2 - 0x15) >> 1) * 4)), 2, 0x2C, 0x12, 0x2C, 0x12, 0, 0, 0x2B, 0x11, (f32) x, (f32) y0, (s32) arg4->scale, arg5);
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
        func_801BC1B0(arg0, *(s32 *)(D_801F3AA8 + (((s32) (temp_v0_3 - 0x1C) >> 1) * 4)) + 0x318, 2, 0x2C, 0x1A, 0x2C, 0x1A, 0, 0, 0x2B, 0x19, (f32) x, (f32) y1, (s32) arg4->scale, arg5);
    }
}
'''

DECL = '    s32 x;\n    s32 y0;\n    s32 y1;\n    s32 *counter0;\n    s32 *counter1;\n    s32 temp_v0_2;\n    s32 temp_v0_3;\n\n    counter0 = &D_801F3AA0;\n    counter1 = &D_801F3AA4;\n'

outdir = ROOT / 'tools/scratch/nonmatching/T-170'
best = []
for order in itertools.permutations('xy0y1' if False else ['x', 'y0', 'y1']):
    name = ''.join(order)
    body = HEAD + '\nvoid func_801BADEC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023StateBADEC *arg4, s32 arg5) {\n' + DECL + ''.join(STMT[k] for k in order) + TAIL
    p = outdir / f'p_badec_{name}.c'
    p.write_text(body)
    try:
        r = screen.measure('func_801BADEC', p)
        src, tu = cm.build_source('func_801BADEC', p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(src, Path(d)/'c.c')
            pairs = cm.draft_raw(o, 'func_801BADEC')
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
        theirs = [cm.canon(t) for t in cm.target_raw('func_801BADEC')]
        theirs = [t for t in theirs if not t.startswith(('dlabel', 'enddlabel'))]
        import difflib
        sm = difflib.SequenceMatcher(None, theirs, mine, autojunk=False)
        bad = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
        REG = re.compile(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f\d+)\b')
        sm2 = difflib.SequenceMatcher(None, [REG.sub('R', t) for t in theirs], [REG.sub('R', x) for x in mine], autojunk=False)
        bad2 = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm2.get_opcodes() if t != 'equal')
        print(f'{name:6s} words={r["words"]:4d} bytes={r["compiled"]}/{r["original"]} diff={bad:3d} masked={bad2:3d}')
    except Exception as e:
        print(f'{name:6s} ERROR {str(e)[-200:]}')
