#!/usr/bin/env python3
"""BADEC v7: declaration-order permutations on the permuter 406 shape."""
import importlib.util, sys, tempfile, re, difflib, itertools
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)
fn = 'func_801BADEC'
T = None


def target():
    global T
    if T is None:
        t = [cm.canon(x) for x in cm.target_raw(fn)]
        T = [x for x in t if not x.startswith(('dlabel', 'enddlabel'))]
    return T


def score(txt, tag):
    p = ROOT / 'tools/scratch/nonmatching/T-170' / f'z_{tag[0]}.c'
    p.write_text(txt)
    try:
        r = screen.measure(fn, p)
        source, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(source, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    except Exception as e:
        return (9999, 999, tag[0], f'{tag[0]:14s} ERROR {str(e)[-90:]}')
    th = target()
    sm = difflib.SequenceMatcher(None, th, mine, autojunk=False)
    bad = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    return (r['words'], bad, tag[0], f'{tag[0]:14s} w={r["words"]:4d} {r["compiled"]}/{r["original"]} diff={bad:3d}')


HEAD = '''typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023StateBADEC;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F3AA0;
extern s32 D_801F3AA4;
extern u8 D_801F3AA8[];
'''

BODY = '''  counter0 = &D_801F3AA0;
  counter1 = &D_801F3AA4;
  x = (arg1 * 4) + (((s32) ((0x1CD - (arg5 * 4)) * scale)) >> 0xA);
  y0 = ((arg2 * 4) + (((s32) (scale * 0x198)) >> 0xA)) + (arg4->yOffset * 4);
  y1 = ((arg2 * 4) + (((s32) (scale * 0x1E3)) >> 0xA)) + (arg4->yOffset * 4);
  if (arg5 != 0)
  {
    x = 0x9B0 - x;
  }
  temp_v0_2 = (*counter0) + 1;
  *counter0 = temp_v0_2;
  if (temp_v0_2 >= 0x15)
  {
    if (temp_v0_2 >= 0x27)
    {
      D_801F3AA0 = temp_v0_2;
      *counter0 = 0;
    }
    else
    {
      func_801BC1B0(arg0, *((s32 *) (D_801F3AA8 + ((((s32) (temp_v0_2 - 0x15)) >> 1) * 4))), 2, 0x2C, 0x12, 0x2C, 0x12, 0, 0, 0x2B, 0x11, (f32) x, (f32) y0, scale, arg5);
    }
  }
  temp_v0_3 = (*counter1) + 1;
  *counter1 = temp_v0_3;
  if (temp_v0_3 >= 0x1C)
  {
    D_801F3AA4 = temp_v0_3;
    if (temp_v0_3 >= 0x2E)
    {
      *counter1 = 0;
      return;
    }
    D_801F3AA4 = temp_v0_3;
    func_801BC1B0(arg0, (*((s32 *) (D_801F3AA8 + ((((s32) (temp_v0_3 - 0x1C)) >> 1) * 4)))) + 0x318, 2, 0x2C, 0x1A, 0x2C, 0x1A, 0, 0, 0x2B, 0x19, (f32) x, (f32) y1, scale, arg5);
  }
}
'''


def build(order, scale_first):
    d = []
    if scale_first:
        d.append('  s32 scale = arg4->scale;\n')
    for v in order:
        if v == 'counter0':
            d.append('  s32 *counter0;\n')
        elif v == 'counter1':
            d.append('  s32 *counter1;\n')
        elif v == 'scale':
            if not scale_first:
                d.append('  s32 scale = arg4->scale;\n')
        else:
            d.append(f'  s32 {v};\n')
    sig = 'void func_801BADEC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023StateBADEC *arg4, s32 arg5)\n{\n'
    return HEAD + '\n' + sig + ''.join(d) + BODY


if __name__ == '__main__':
    names = ['x', 'y0', 'y1', 'counter0', 'counter1', 'temp_v0_2', 'temp_v0_3', 'scale']
    res = []
    for i, order in enumerate(itertools.permutations(names)):
        if i % 3:
            continue
        for sf in (0, 1):
            if sf and order[0] != 'scale':
                continue
            tag = (f'{i}_{sf}',)
            res.append(score(build(list(order), sf), tag))
    for w, b, t, line in sorted(res)[:12]:
        print(line, flush=True)
