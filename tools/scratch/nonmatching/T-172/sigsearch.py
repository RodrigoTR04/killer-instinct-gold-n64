"""Slot-signature sweep for func_8002E150 using standalone IDO compiles.

Compiles just the function body (with externs) and compares the exact sp-slot
signature against the target's, as slotsig.py does for the full TU but ~15x
cheaper. Hits are re-verified officially by the caller.
"""
import itertools
import re
import sys
from collections import Counter
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743')
sys.path.insert(0, str(ROOT / 'tools/scratch/nonmatching/T-172'))
import ido  # noqa: E402
import slotsig  # noqa: E402

TARGET_FRAME, TARGET_COUNTS = slotsig.target_sig('func_8002E150')

HEAD = '''typedef int s32;
typedef unsigned int u32;
extern double D_80048EE0[],D_80048F10[],D_80048F38[],D_80048F58[];
extern double D_80048F78,D_80048F80,D_80048F88,D_80048F90,D_80048F98,D_80048FA0,D_80048FA8;
extern float sqrtf(float);
'''

BODY = '''    s32 hi;
    s32 exponent;
    double w;
    double u;
    double r;
    double t;
    double a;
    double q;
    double p;
    double z;
    hi = *(s32 *)&x;
    exponent = (hi >> 20) & 0x7FF;
    if (exponent < 0x3FE) {
        if (exponent >= 0x3E3) {
            z = x * x;
            p = D_80048EE0[1]+((((D_80048EE0[5]*z+D_80048EE0[4])*z+D_80048EE0[3])*z+D_80048EE0[2])*z);
            q = D_80048F10[0]+(((z+D_80048F10[3])*z+D_80048F10[2])*z+D_80048F10[1])*z;
            return z * p * x / q + x;
        }
        return x;
    }
    if (exponent < 0x3FF) {
        a = x;
        if (x < 0.0) a = -x;
        if (a < D_80048FA8) {
            t = 2.0 * (x * x) - D_80048F78;
            do { z = t * t; } while (0);
            do { p = D_80048EE0[1]+((((D_80048EE0[5]*z+D_80048EE0[4])*z+D_80048EE0[3])*z+D_80048EE0[2])*z); } while (0);
            q = D_80048F10[0]+(((z+D_80048F10[3])*z+D_80048F10[2])*z+D_80048F10[1])*z;
            if (hi > 0) return 0.5 * (z * p * t / q + t) + D_80048F88;
            return D_80048F98 - 0.5 * (z * p * t / q + t);
        }
        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);
        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;
        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;
        r = z*u*t/w+t;
        if (hi > 0) return D_80048F90 - 2.0 * r;
        return 2.0 * r + D_80048FA0;
    }
    if (x != x) return 0.0;
    if (x == D_80048F78) return D_80048F90;
    if (x == D_80048F80) return D_80048FA0;
    return 0.0;
}
'''


def signature(source):
    try:
        stream = ido.insns(source)
    except SystemExit:
        return None, None
    c = Counter()
    frame = None
    for mnem, ops in stream:
        if frame is None:
            m = re.search(r'sp,sp,-(\d+)', ops.replace(' ', ''))
            if m:
                frame = -int(m.group(1))
        for off in re.findall(r'(\d+)\(sp\)', ops):
            c[int(off)] += 1
    return frame, c


def ok(frame, c):
    return frame == TARGET_FRAME and c == TARGET_COUNTS


if __name__ == '__main__':
    print('target', slotsig.fmt(TARGET_FRAME, TARGET_COUNTS))
    print('base  ', slotsig.fmt(*signature(HEAD + 'double func_8002E150(double x) {\n' + BODY)))
