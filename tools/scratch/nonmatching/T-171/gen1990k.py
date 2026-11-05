#!/usr/bin/env python3
"""func_801C1990 round 11: single-axis changes from the 91-word draft."""
from pathlib import Path
OUT = Path('/tmp/v1990k')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = """#include "frontend.h"
extern s32 func_801C17D0(u32 *, u8);
extern u8 D_8004A407, D_8004EA9B[], D_802D37FC, D_802D37FD;
extern s32 D_80127C30[];
extern u8 D_80128308[], D_8012830A[];
extern u64 D_802D3800[];
u8 func_801C1990(s32 *stats) {
    s32 result;
    s32 mask;
    s32 player;
    u32 value;
    s32 pending;
    u8 character;
 D_802D3800[0] = 0;
    D_802D3800[1] = 0;
    if (!stats[6]) stats[6] = 100;
    mask = D_8004A407 ^ 3;
    D_802D37FD = stats[0] & mask;
    value = (3 - stats[0]) & mask;
    pending = D_802D37FC = value;
    if (pending == 3) {
        result = func_801C17D0((u32 *)stats, 0);
        result |= func_801C17D0((u32 *)stats, 1) * 2;
        D_802D37FC = 0;
        return result & 255;
    }
    if (pending > 0) {
        func_801C17D0((u32 *)stats, (pending - 1) & 255);
        pending = D_802D37FC;
    }
    if (D_802D37FD > 0) {
        character = D_8004EA9B[D_802D37FD];
        D_802D37FD -= 1;
        player = D_802D37FD;
        value = stats[6];
        if (D_80127C30[player] > value) D_80127C30[player] = value;
        if (player == 0) {
            value = stats[3];
            if (D_80128328[player][character] < value) D_80128328[player][character] = value;
            value = stats[1];
            if (D_80128310[player][character] < value) D_80128310[player][character] = value;
        } else {
            value = stats[4];
            if (D_80128328[player][character] < value) D_80128328[player][character] = value;
            value = stats[2];
            if (D_80128310[player][character] < value) D_80128310[player][character] = value;
        }
        D_8012830A[player]++;
        if (stats[5]) D_80128308[player]++;
        D_802D37FD = player + 1;
    }
    if (pending > 0 && D_802D3800[pending - 1] != 0) return pending;
    return 0;
}
"""
(OUT / 'base.c').write_text(BASE)

# k1: D_80127C30 on the left (already in base) -- so instead make stats[6] the left operand
(OUT / 'k1.c').write_text(BASE.replace(
    'if (D_80127C30[player] > value) D_80127C30[player] = value;',
    'if (value < (u32) D_80127C30[player]) D_80127C30[player] = value;'))

# k2: stat rows read stats[] directly (row address computed first)
(OUT / 'k2.c').write_text(BASE.replace("""            value = stats[3];
            if (D_80128328[player][character] < value) D_80128328[player][character] = value;
            value = stats[1];
            if (D_80128310[player][character] < value) D_80128310[player][character] = value;""",
"""            if (D_80128328[player][character] < (u32) stats[3]) D_80128328[player][character] = stats[3];
            if (D_80128310[player][character] < (u32) stats[1]) D_80128310[player][character] = stats[1];""").replace(
"""            value = stats[4];
            if (D_80128328[player][character] < value) D_80128328[player][character] = value;
            value = stats[2];
            if (D_80128310[player][character] < value) D_80128310[player][character] = value;""",
"""            if (D_80128328[player][character] < (u32) stats[4]) D_80128328[player][character] = stats[4];
            if (D_80128310[player][character] < (u32) stats[2]) D_80128310[player][character] = stats[2];"""))

# k3: keep both: global left AND direct stats rows
b3 = (OUT / 'k2.c').read_text().replace(
    'if (value < (u32) D_80127C30[player])',
    'if (D_80127C30[player] > value)')
(OUT / 'k3.c').write_text(b3)

# k4: value as s32 with direct stats rows
(OUT / 'k4.c').write_text((OUT / 'k2.c').read_text().replace('u32 value;', 's32 value;'))

# k5: player from the decrement expression
(OUT / 'k5.c').write_text(BASE.replace(
    'D_802D37FD -= 1;\n        player = D_802D37FD;',
    'player = (D_802D37FD -= 1);'))

# k6: D_802D3800 write as two u32
(OUT / 'k6.c').write_text(BASE.replace(""" D_802D3800[0] = 0;
    D_802D3800[1] = 0;""",
"""    ((u32 *) D_802D3800)[0] = 0;
    ((u32 *) D_802D3800)[1] = 0;"""))

# k7: character loaded before the FD decrement stays, but store order changes
(OUT / 'k7.c').write_text(BASE.replace(
    'D_802D37FC = 0;\n        return result & 255;',
    'D_802D37FC = 0;\n        return (u8) result;'))

# k8: tail reads as two u32 words
(OUT / 'k8.c').write_text(BASE.replace(
    'if (pending > 0 && D_802D3800[pending - 1] != 0) return pending;',
    'if (pending > 0 && ((u32 *) D_802D3800)[pending * 2 - 2] != 0) return pending;'))

print(8)
