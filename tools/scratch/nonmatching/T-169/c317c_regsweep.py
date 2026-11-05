#!/usr/bin/env python3
"""T-169 1C317C: the target keeps exactly f20/f22/f24 live (f24=D_802937B8,
f22=D_802937BC, f20=(f32)(arg2-0x5DC)) at frame 0x70 with s0-s7+ra. Sweep where
those three named locals are declared/assigned and filter on the register set
AND frame, not on score."""
import concurrent.futures as cf
import importlib.util
import itertools
import re
import sys
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4f670e05')
T = ROOT / 'tools/scratch/nonmatching/T-169'
sys.path.insert(0, str(T))
import regset  # noqa: E402

spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)
OUT = T / 'c317creg'
OUT.mkdir(exist_ok=True)
BASE = (T / 'c317c_best.c').read_text()

LOOP_HEAD = '''      slots = (u8 **) (entry + (first * 4));
      D_802D3834 = fade;
      while ((*slots) != 0)
      {'''
LOOP_OLD = '''        D_802956F4 = func_801BD640(arg0, (u8 *) ((D_802956F4 << 6) + ((s32) D_802C9F70.matrices)), *slots, D_802937BC, (f32) (y - 5), (f32) (arg2 - 0x5DC), 0, 0, 0, ((s32) (D_802D3834 & 0xFF)) >> 1);
        D_802956F4 += func_801BD640(arg0, (u8 *) ((D_802956F4 << 6) + ((s32) D_802C9F70.matrices)), *((u8 **) (((u8 *) ((u8 **) table)[D_80285578]) + (first * 4))), D_802937B8, (f32) y, (f32) (arg2 - 0x5DC), 0xFF, 0xFF, 0xFF, D_802D3834);'''

LOOP_NEW = '''        D_802956F4 = func_801BD640(arg0, (u8 *) ((D_802956F4 << 6) + ((s32) D_802C9F70.matrices)), *slots, tint, (f32) (y - 5), depth, 0, 0, 0, ((s32) (D_802D3834 & 0xFF)) >> 1);
        D_802956F4 += func_801BD640(arg0, (u8 *) ((D_802956F4 << 6) + ((s32) D_802C9F70.matrices)), *((u8 **) (((u8 *) ((u8 **) table)[D_80285578]) + (first * 4))), shade, (f32) y, depth, 0xFF, 0xFF, 0xFF, D_802D3834);'''

# where to place the three loads
PLACE = {
    'before_while': LOOP_HEAD + '\n' +
        '      shade = D_802937B8;\n      tint = D_802937BC;\n      depth = (f32) (arg2 - 0x5DC);',
    'before_while_rev': LOOP_HEAD + '\n' +
        '      depth = (f32) (arg2 - 0x5DC);\n      tint = D_802937BC;\n      shade = D_802937B8;',
    'before_if': None,      # handled specially: before `if ((*slots) != 0)`
    'before_arg3if': None,  # before `if (arg3 > 0)`
}

DECL = {
    'after_index': '  s32 index;\n  f32 tint, shade, depth;',
    'first': '  f32 tint, shade, depth;\n  u8 *table;',
    'sep_at_end': '  s32 index;\n  f32 tint;\n  f32 shade;\n  f32 depth;',
    'sep_first': '  f32 tint;\n  f32 shade;\n  f32 depth;\n  u8 *table;',
}


def build(place, decl, order):
    t = BASE.replace(LOOP_OLD, LOOP_NEW)
    t = t.replace('  s32 index;', DECL[decl], 1)
    loads = ['      shade = D_802937B8;', '      tint = D_802937BC;', '      depth = (f32) (arg2 - 0x5DC);']
    if order == 'rev':
        loads = loads[::-1]
    if place == 'before_while':
        t = t.replace(LOOP_HEAD, LOOP_HEAD + '\n' + '\n'.join(loads), 1)
    elif place == 'before_if':
        anchor = '  if ((*slots) != 0)'
        t = t.replace(anchor, '\n'.join(x[6:] for x in loads) + '\n' + anchor, 1)
    elif place == 'before_arg3if':
        anchor = '    if (arg3 > 0)'
        t = t.replace(anchor, '\n'.join(x[2:] for x in loads) + '\n' + anchor, 1)
    return t


def probe(args):
    place, decl, order = args
    p = OUT / f'{place}_{decl}_{order}.c'
    try:
        p.write_text(build(place, decl, order))
        frame, saved, floats = regset.draft('func_801C317C', p)
        words = dict(screen.measure('func_801C317C', p))['words']
        return (frame, sorted(saved), sorted(floats), words, p.name)
    except Exception as e:
        return (None, [], [], 10**6, p.name + ' ' + str(e)[:40])


tasks = [(pl, d, o) for pl in ('before_while', 'before_if', 'before_arg3if')
         for d in DECL for o in ('fwd', 'rev')]
rows = []
with cf.ThreadPoolExecutor(8) as pool:
    rows = list(pool.map(probe, tasks))

TF, TI, TFLOAT = 0x70, ['ra', 's0', 's1', 's2', 's3', 's4', 's5', 's6', 's7'], ['f20', 'f22', 'f24']
rows.sort(key=lambda r: (r[0] != TF, r[2] != TFLOAT, r[1] != TI, r[3]))
for frame, saved, floats, words, name in rows:
    fh = f'0x{frame:x}' if frame else 'fail'
    flags = ''.join(('F' if frame == TF else '.', 'R' if floats == TFLOAT else '.', 'I' if saved == TI else '.'))
    print(f'[{flags}] frame {fh:>5} float {{{",".join(floats)}}} words={words:4d} {name}')
