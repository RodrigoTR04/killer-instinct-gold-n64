#!/usr/bin/env python3
"""Create disposable decomp-permuter inputs from a nonmatching draft and its TU."""
import argparse
import importlib.util
import json
from pathlib import Path
import re
import shlex
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[2]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('function')
    parser.add_argument('output', type=Path, help='new directory outside the tracked tree')
    parser.add_argument('--draft', type=Path)
    args = parser.parse_args()
    fn = args.function
    matches = []
    for tu in (ROOT / 'src').glob('*/*.c'):
        text = tu.read_text()
        match = re.search(r'#pragma GLOBAL_ASM\("([^"]*/' + re.escape(fn) + r'\.s)"\)', text)
        if match:
            matches.append((tu, text, match))
    if len(matches) != 1:
        parser.error(f'expected one GLOBAL_ASM owner, found {len(matches)}')
    tu, text, match = matches[0]
    drafts = [args.draft] if args.draft else list((ROOT / 'tools/scratch/nonmatching').glob('T-*/' + fn + '.c'))
    if len(drafts) != 1:
        parser.error('expected one draft; select it with --draft')
    draft = drafts[0].resolve()
    # Keep preceding declarations/definitions, as the prior TU-context probes do.
    context = re.sub(r'#pragma GLOBAL_ASM\([^\n]*\)', '', text[:match.start()])
    draft_text = draft.read_text()
    if fn == 'func_8002F45C':
        # Retain the owning TU's declaration; use a layout-compatible typed view.
        draft_text = draft_text.replace('extern T024AllocationLists D_80048270;', '')
        draft_text = draft_text.replace('D_80048270.', '((T024AllocationLists *)&D_80048270)->')
    source = context + '\n' + draft_text
    out = args.output.resolve()
    out.mkdir(parents=True, exist_ok=False)
    permuter = ROOT / 'tools/ext/decomp-permuter'
    spec = importlib.util.spec_from_file_location('strip_other_fns', permuter / 'strip_other_fns.py')
    strip = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(strip)
    with tempfile.TemporaryDirectory(prefix='kig-permuter-') as tmp:
        c = Path(tmp) / 'context.c'
        c.write_text(source)
        processed = subprocess.check_output(['gcc', '-E', '-P', '-I' + str(ROOT / 'include'), str(c)], text=True)
    (out / 'base.c').write_text(strip.strip_other_fns(processed, fn))
    # Original splat assembly includes its own late-rodata and jump tables.
    asm = re.sub(r'^\s*\.late_rodata_alignment[^\n]*', '', (ROOT / match[1]).read_text(), flags=re.M)
    (out / 'target.s').write_text((permuter / 'prelude.inc').read_text() + '\n' + asm)
    subprocess.run([str(ROOT / 'tools/ext/binutils/bin/mips64-elf-as'), '-EB', '-mips3', '-32', '-G', '0', '-I', str(ROOT / 'include'), '-o', str(out / 'target.o'), str(out / 'target.s')], check=True)
    # Same wrapper, assembler and game flags as Makefile's build/src/%.c.o rule.
    command = [ROOT / '.venv/bin/python', ROOT / 'tools/ext/asm-processor/build.py', ROOT / 'tools/ext/ido/5.3/cc', '--', ROOT / 'tools/ext/binutils/bin/mips64-elf-as', '-EB', '-mips3', '-32', '-G', '0', '-I', ROOT / 'include', '--', '-c', '-G', '0', '-non_shared', '-Xcpluscomm', '-Wab,-r4300_mul', '-O2', '-mips2', '-32', '-I' + str(ROOT / 'include')]
    (out / 'compile.sh').write_text('#!/bin/sh\nset -eu\nexec ' + shlex.join([str(x) for x in command]) + ' "$@"\n')
    (out / 'compile.sh').chmod(0o755)
    objdump = shlex.join([str(ROOT / 'tools/ext/binutils/bin/mips64-elf-objdump'), '-drz', '-m', 'mips:4300'])
    (out / 'settings.toml').write_text(
        f'func_name = {json.dumps(fn)}\ncompiler_type = "ido"\n'
        f'objdump_command = {json.dumps(objdump)}\n')
    (out / 'origin.json').write_text(json.dumps({'function': fn, 'tu': str(tu.relative_to(ROOT)), 'draft': str(draft.relative_to(ROOT) if draft.is_relative_to(ROOT) else draft), 'asm': match[1]}, indent=2) + '\n')
    subprocess.run([str(out / 'compile.sh'), str(out / 'base.c'), '-o', str(out / 'base.o')], check=True, cwd=ROOT)
    print(out)


if __name__ == '__main__':
    main()
