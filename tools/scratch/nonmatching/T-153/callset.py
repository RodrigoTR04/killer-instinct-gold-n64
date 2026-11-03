#!/usr/bin/env python3
"""Compare the multiset of calls in a draft against the original splat assembly.

A missing or duplicated call is a structural (behavioural) difference, not a
scheduling one, so it is worth chasing before any register work.
"""
import re
import subprocess
import sys
import tempfile
from collections import Counter
from pathlib import Path
import importlib.util

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmp', ROOT / 'tools/scratch/nonmatching/T-153/cmp.py')
cmp_mod = importlib.util.module_from_spec(spec)
spec.loader.exec_module(cmp_mod)


def block(text, function):
    out, inside = [], False
    for line in text.splitlines():
        if re.search(r'<' + re.escape(function) + r'>:$', line):
            inside = True
            continue
        if inside and re.match(r'^[0-9a-f]{8} <', line):
            break
        if inside:
            out.append(line)
    return out


def calls_original(function):
    _, _, m = cmp_mod.owner(function)
    text = (ROOT / m.group(1)).read_text()
    names = re.findall(r'jal\s+(\w+)', text)
    # the splat asm also names indirect calls; ignore those
    return Counter(n for n in names if not n.startswith('$'))


def calls_draft(function, draft):
    source, _ = cmp_mod.build_source(function, draft)
    with tempfile.TemporaryDirectory(prefix='kig-c-') as d:
        o = cmp_mod.compile_source(source, Path(d) / 'c.c')
        text = subprocess.run([str(cmp_mod.OBJDUMP), '-dr', '--no-show-raw-insn', str(o)],
                              capture_output=True, text=True).stdout
    out = Counter()
    pending = None
    for line in block(text, function):
        if pending is not None:
            m = re.match(r'\s*[0-9a-f]+:\s+(R_MIPS_26)\s+(\S+)', line)
            if m:
                out[m.group(2)] += 1
                pending = None
                continue
        m = re.match(r'\s*[0-9a-f]+:\s+jal\s', line)
        if m:
            pending = True
    return out


def main():
    for arg in sys.argv[1:]:
        function, draft = arg.split(':')
        path = Path(draft)
        if not path.is_absolute():
            path = ROOT / path
        want = calls_original(function)
        try:
            got = calls_draft(function, path)
        except SystemExit:
            print(f'{function}: COMPILE FAILED')
            continue
        missing = {k: want[k] - got.get(k, 0) for k in want if want[k] > got.get(k, 0)}
        extra = {k: got[k] - want.get(k, 0) for k in got if got[k] > want.get(k, 0)}
        status = 'OK' if not missing and not extra else 'DIFF'
        print(f'{function}: {status}  missing={missing or "-"}  extra={extra or "-"}')


if __name__ == '__main__':
    main()
