#!/usr/bin/env python3
"""func_801C1990 round 12: on the 89-word base, attack the stats copy to a2."""
from pathlib import Path
OUT = Path('/tmp/v1990l')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('/tmp/v1990k/k2.c').read_text()

def mk(name, text):
    (OUT / f'{name}.c').write_text(text)

# L1: u32* parameter matching the callee, no cast
t = BASE.replace('extern s32 func_801C17D0(u32 *, u8);', 'extern s32 func_801C17D0(u32 *, u8);')
t = t.replace('u8 func_801C1990(s32 *stats)', 'u8 func_801C1990(u32 *stats)')
t = t.replace('func_801C17D0((u32 *)stats,', 'func_801C17D0(stats,')
mk('l1', t)

# L2: callee takes void*, stats stays s32*, no cast
t = BASE.replace('extern s32 func_801C17D0(u32 *, u8);', 'extern s32 func_801C17D0(void *, u8);')
t = t.replace('func_801C17D0((u32 *)stats,', 'func_801C17D0(stats,')
mk('l2', t)

# L3: u32 stats param + void* callee
t = BASE.replace('extern s32 func_801C17D0(u32 *, u8);', 'extern s32 func_801C17D0(void *, u8);')
t = t.replace('u8 func_801C1990(s32 *stats)', 'u8 func_801C1990(u32 *stats)')
t = t.replace('func_801C17D0((u32 *)stats,', 'func_801C17D0(stats,')
mk('l3', t)

# L4: keep s32* but store through a real local address pointer taken once
t = BASE.replace("""    mask = D_8004A407 ^ 3;
    D_802D37FD = stats[0] & mask;""",
"""    mask = D_8004A407 ^ 3;
    D_802D37FD = stats[0] & mask;
""")
t = t.replace('u8 func_801C1990(s32 *stats) {', 'u8 func_801C1990(s32 *stats) {\n    u8 *pendingAddr = &D_802D37FC;')
t = t.replace('pending = D_802D37FC = value;', '*pendingAddr = pending = value;')
t = t.replace('pending = D_802D37FC;', 'pending = *pendingAddr;')
mk('l4', t)

# L5: 89 base but with the u8 pending local assigned from a second expression
t = BASE.replace('    s32 pending;', '    u8 pending;')
t = t.replace('    value = (3 - stats[0]) & mask;\n    pending = D_802D37FC = value;',
              '    D_802D37FC = (3 - stats[0]) & mask;\n    pending = (3 - stats[0]) & mask;')
mk('l5', t)

# L6: same but store before the value local is used again
t = BASE.replace('    s32 pending;', '    u8 pending;')
t = t.replace('    value = (3 - stats[0]) & mask;\n    pending = D_802D37FC = value;',
              '    D_802D37FC = (3 - stats[0]) & mask;\n    pending = D_802D37FC;')
mk('l6', t)

# L7: s32 pending, both from one expression, store last
t = BASE.replace('    value = (3 - stats[0]) & mask;\n    pending = D_802D37FC = value;',
              '    value = (3 - stats[0]) & mask;\n    pending = value;\n    D_802D37FC = pending;')
mk('l7', t)

# L8: 89 base without the value local in the header row at all
t = BASE.replace('    u32 value;\n', '')
t = t.replace('    value = (3 - stats[0]) & mask;\n    pending = D_802D37FC = value;',
              '    pending = D_802D37FC = (3 - stats[0]) & mask;')
mk('l8', t)

print(8)
