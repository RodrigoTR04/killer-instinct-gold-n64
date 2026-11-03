#!/usr/bin/env python3
"""Print the compiled assembly of one draft function (owning TU context)."""
import importlib.util
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmp', ROOT / 'tools/scratch/nonmatching/T-153/cmp.py')
cmp_mod = importlib.util.module_from_spec(spec)
spec.loader.exec_module(cmp_mod)


def main():
    function, draft = sys.argv[1], Path(sys.argv[2])
    if not draft.is_absolute():
        draft = ROOT / draft
    source, tu = cmp_mod.build_source(function, draft)
    with tempfile.TemporaryDirectory(prefix='kig-asm-') as d:
        o = cmp_mod.compile_source(source, Path(d) / 'candidate.c')
        out = subprocess.run([str(cmp_mod.OBJDUMP), '-dr', '--no-show-raw-insn', str(o)],
                             capture_output=True, text=True).stdout
    started = False
    for line in out.splitlines():
        if f'<{function}>:' in line:
            started = True
        elif started and line and line[0].isdigit() and '<' in line:
            break
        if started:
            print(line)


if __name__ == '__main__':
    main()
