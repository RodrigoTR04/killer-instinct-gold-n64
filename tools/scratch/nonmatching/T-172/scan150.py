"""Fast standalone signature scanner for func_8002E150 declaration orders.

Compiles just the function body (with its extern decls) and compares the
sp-relative access signature against the original's.
"""
import itertools
import re
import subprocess
import sys
import tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743')
OBJDUMP = ROOT / 'tools/ext/binutils/bin/mips64-elf-objdump'
ASM = ROOT / 'asm/nonmatchings/main/main_1E7F0/func_8002E150.s'

HEAD = '''typedef int s32;
typedef unsigned int u32;
extern double D_80048EE0[],D_80048F10[],D_80048F38[],D_80048F58[];
extern double D_80048F78,D_80048F80,D_80048F88,D_80048F90,D_80048F98,D_80048FA0,D_80048FA8;
extern float sqrtf(float);
'''

BODY = '''    s32 hi = *(s32 *)&x;
    s32 exponent = (hi >> 20) & 0x7FF;
    double DECLS;
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
        a = -x;
        if (x >= 0.0) a = x;
        if (a < D_80048FA8) {
            t = 2.0 * (x * x) - D_80048F78;
            do { z = t * t; } while (0);
            p = D_80048EE0[1]+((((D_80048EE0[5]*z+D_80048EE0[4])*z+D_80048EE0[3])*z+D_80048EE0[2])*z);
            q = D_80048F10[0]+(((z+D_80048F10[3])*z+D_80048F10[2])*z+D_80048F10[1])*z;
            if (hi > 0) return 0.5 * (z * p * t / q + t) + D_80048F88;
            return D_80048F98 - 0.5 * (z * p * t / q + t);
        }
        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);
        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;
        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;
        r = z*u*t/w + t;
        if (hi > 0) return D_80048F90 - 2.0 * r;
        return 2.0 * r + D_80048FA0;
    }
    if (x != x) return 0.0;
    if (x == D_80048F78) return D_80048F90;
    if (x == D_80048F80) return D_80048FA0;
    return 0.0;
}
'''


def target_slots():
    out = []
    for line in ASM.read_text().splitlines():
        m = re.search(r'\*/\s+(\S+)\s+(.*)', line)
        if not m:
            continue
        mnem, ops = m.group(1), m.group(2)
        ops = ops.replace('$', '')
        m2 = re.search(r'sp,\s*sp,\s*-(0x[0-9A-Fa-f]+)', ops)
        if m2:
            out.append(('frame', int(m2.group(1), 16)))
            continue
        for m3 in re.finditer(r'(0x[0-9A-Fa-f]+)\(sp\)', ops):
            out.append((mnem, int(m3.group(1), 16)))
    return out


def slots_of(source):
    with tempfile.TemporaryDirectory(prefix='t172-') as d:
        c = Path(d) / 't.c'
        o = Path(d) / 't.o'
        c.write_text(source)
        cmd = [ROOT / '.venv/bin/python', ROOT / 'tools/ext/asm-processor/build.py',
               ROOT / 'tools/ext/ido/5.3/cc', '--',
               ROOT / 'tools/ext/binutils/bin/mips64-elf-as', '-EB', '-mips3', '-32', '-G', '0',
               '-I', str(ROOT / 'include'), '--', '-c', '-G', '0', '-non_shared', '-Xcpluscomm',
               '-Wab,-r4300_mul', '-O2', '-mips2', '-32', '-Iinclude', '-o', str(o), str(c)]
        r = subprocess.run([str(x) for x in cmd], cwd=ROOT, capture_output=True, text=True)
        if r.returncode:
            return None
        text = subprocess.run([str(OBJDUMP), '-dr', '--no-show-raw-insn', str(o)],
                              capture_output=True, text=True).stdout
    out = []
    for line in text.splitlines():
        parts = [p.strip() for p in line.split('\t')]
        if len(parts) < 3 or not re.fullmatch(r'[0-9a-f]+:', parts[0]):
            continue
        mnem, ops = parts[1], parts[2].replace('$', '')
        m = re.search(r'sp,sp,-(\d+)', ops.replace(' ', ''))
        if m:
            out.append(('frame', int(m.group(1))))
            continue
        for m in re.finditer(r'(\d+)\(sp\)', ops):
            out.append((mnem, int(m.group(1))))
    return out


TARGET = target_slots()
NAMES = ['z', 'p', 'q', 'a', 't', 'r', 'u', 'w']


def score(order):
    decls = ', '.join(order)
    src = HEAD + 'double func_8002E150(double x) {\n' + BODY.replace('DECLS', decls)
    got = slots_of(src)
    if got != TARGET:
        return None
    return order


if __name__ == '__main__':
    print('target slots:', TARGET)
    orders = list(itertools.permutations(NAMES))
    print(len(orders), 'orders')
    hits = []
    with ThreadPoolExecutor(max_workers=24) as pool:
        for res in pool.map(score, orders):
            if res:
                hits.append(res)
                print('HIT', res)
    print('total hits', len(hits))
