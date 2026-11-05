#!/usr/bin/env python3
"""func_801C1990: attack the a2 copy with a different parameter type spelling."""
from pathlib import Path
OUT = Path('/tmp/v1990r')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-171/func_801C1990.c').read_text()

V = {}
V['base'] = BASE
# r1: callee declared as taking the same s32*
V['r1'] = BASE.replace('extern s32 func_801C17D0(u32 *, u8);', 'extern s32 func_801C17D0(s32 *, u8);').replace(
    'func_801C17D0((u32 *)stats,', 'func_801C17D0(stats,')
# r2: void*
V['r2'] = BASE.replace('extern s32 func_801C17D0(u32 *, u8);', 'extern s32 func_801C17D0(void *, u8);').replace(
    'func_801C17D0((u32 *)stats,', 'func_801C17D0(stats,')
# r3: keep u32* but declare stats as u32* too
V['r3'] = BASE.replace('u8 func_801C1990(s32 *stats)', 'u8 func_801C1990(u32 *stats)').replace(
    'func_801C17D0((u32 *)stats,', 'func_801C17D0(stats,')
# r4: two params, one per use? no. Use a copy of the pointer for the calls only.
V['r4'] = BASE.replace('    mask = D_8004A407 ^ 3;',
                       '    u32 *callStats = (u32 *) stats;\n    mask = D_8004A407 ^ 3;').replace(
    'func_801C17D0((u32 *)stats,', 'func_801C17D0(callStats,')
# r5: parameter named stats, u32*, no cast anywhere, D_8004A407 read first
V['r5'] = BASE.replace('u8 func_801C1990(s32 *stats)', 'u8 func_801C1990(u32 *stats)').replace(
    'func_801C17D0((u32 *)stats,', 'func_801C17D0(stats,').replace(
    '    mask = D_8004A407 ^ 3;', '    mask = D_8004A407 ^ 3;')

for k, v in V.items():
    (OUT / f'{k}.c').write_text(v)
print(len(V))
