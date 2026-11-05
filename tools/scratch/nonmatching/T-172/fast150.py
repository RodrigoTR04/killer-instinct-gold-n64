"""Fast standalone search for func_8002E150: rank decl orders by full instruction diff.

Compiles just the function (no TU) and diffs the instruction stream against the
splat asm. Only costs a standalone IDO run per variant, so ~15x faster than
screen.measure; top hits are re-verified officially by the caller.
"""
import difflib
import itertools
import re
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743')
sys.path.insert(0, str(ROOT / 'tools/scratch/nonmatching/T-172'))
import scan150  # noqa: E402

ASM = ROOT / 'asm/nonmatchings/main/main_1E7F0/func_8002E150.s'


def canon(insn):
    """Normalise an instruction for comparison: drop $, fold hex to int, mask regs."""
    parts = insn.split(None, 1)
    mnem = parts[0]
    rest = parts[1] if len(parts) > 1 else ''
    rest = rest.replace('$', '')

    def sub(m):
        tok = m.group(0)
        if re.fullmatch(r'0x[0-9A-Fa-f]+', tok):
            return str(int(tok, 16))
        return tok

    rest = re.sub(r'-?0x[0-9A-Fa-f]+', sub, rest)
    rest = re.sub(r'\s+', '', rest)
    regs = set(re.findall(r'\b(?:zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f\d+)\b', rest))
    return mnem + ' ' + rest


def target():
    out = []
    started = False
    for line in ASM.read_text().splitlines():
        if 'glabel func_8002E150' in line:
            started = True
            continue
        if not started or 'endlabel' in line:
            continue
        m = re.search(r'\*/\s+(\S+)\s+(.*)', line)
        if not m:
            continue
        out.append(canon(m.group(1) + ' ' + m.group(2)))
    return out


TARGET = target()


def slots_only(stream):
    res = []
    for insn in stream:
        for m in re.finditer(r'(-?\d+)\(sp\)', insn):
            res.append((insn.split()[0], int(m.group(1))))
        m = re.search(r'sp,sp,-(\d+)', insn)
        if m:
            res.append(('frame', int(m.group(1))))
    return res


TARGET_SLOTS = slots_only(TARGET)


def insns(source):
    return [canon(m + ' ' + o) for m, o in scan150_safe(source)]


def scan150_safe(source):
    try:
        return __import__('ido').insns(source)
    except SystemExit:
        return []


def score(source):
    got = insns(source)
    if not got:
        return None
    sm = difflib.SequenceMatcher(None, TARGET, got, autojunk=False)
    bad = 0
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag != 'equal':
            bad += max(i2 - i1, j2 - j1)
    bad += abs(len(got) - len(TARGET))
    return bad + 0.25 * abs(len(got) - len(TARGET))


if __name__ == '__main__':
    print('target insns', len(TARGET))
    print('target slots', TARGET_SLOTS)
