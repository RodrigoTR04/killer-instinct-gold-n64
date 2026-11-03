#!/usr/bin/env python3
"""Compare saved-register sets and frame sizes of drafts against the originals.

A different saved set means the draft keeps different values live across calls,
i.e. a structural difference (not scheduling), which is what makes matches.
"""
import re
import subprocess
import sys
import tempfile
from pathlib import Path
import importlib.util

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmp', ROOT / 'tools/scratch/nonmatching/T-153/cmp.py')
cmp_mod = importlib.util.module_from_spec(spec)
spec.loader.exec_module(cmp_mod)

SAVED = re.compile(r'(?:sdc1|sw)\s+\$?([fs]\d+),\s*(?:0x([0-9A-Fa-f]+)|(\d+))\((?:\$)?sp\)')
FRAME = re.compile(r'addiu\s+\$?sp,\s*\$?sp,\s*-(?:0x([0-9A-Fa-f]+)|(\d+))')


def saved(text):
    regs = set()
    for m in SAVED.finditer(text):
        off = int(m.group(2), 16) if m.group(2) else int(m.group(3))
        # only the prologue save area is above the outgoing-argument space
        if off >= 0x10:
            regs.add(m.group(1))
    return regs


def function_block(text, function):
    out, inside = [], False
    for line in text.splitlines():
        if re.search(r'<' + re.escape(function) + r'>:$', line):
            inside = True
            continue
        if inside and re.match(r'^[0-9a-f]{8} <', line):
            break
        if inside:
            out.append(line)
    return '\n'.join(out)


def frame(text):
    m = FRAME.search(text)
    if not m:
        return None
    return int(m.group(1), 16) if m.group(1) else int(m.group(2))


def main():
    for arg in sys.argv[1:]:
        function, draft = arg.split(':')
        path = Path(draft)
        if not path.is_absolute():
            path = ROOT / path
        _, text, m = cmp_mod.owner(function)
        asm = (ROOT / m.group(1)).read_text()
        tgt_regs, tgt_frame = saved(asm), frame(asm)
        try:
            source, _ = cmp_mod.build_source(function, path)
            with tempfile.TemporaryDirectory(prefix='kig-s-') as d:
                o = cmp_mod.compile_source(source, Path(d) / 'c.c')
                obj = subprocess.run([str(cmp_mod.OBJDUMP), '-dr', '--no-show-raw-insn', str(o)],
                                     capture_output=True, text=True).stdout
            obj = function_block(obj, function)
            got_regs, got_frame = saved(obj), frame(obj)
        except SystemExit:
            print(f'{function}: COMPILE FAILED')
            continue
        extra = sorted(got_regs - tgt_regs)
        missing = sorted(tgt_regs - got_regs)
        print(f'{function}: frame target 0x{tgt_frame:x} draft 0x{got_frame:x} '
              f'({len(tgt_regs)} vs {len(got_regs)} saved)  '
              f'extra={extra} missing={missing}')


if __name__ == '__main__':
    main()
