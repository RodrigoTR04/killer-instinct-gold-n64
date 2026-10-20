#!/usr/bin/env python3
"""Compile each retained draft through asm-processor in its complete production TU.
Scratch objects are never linked into the ROM. Also print the T-056 prefix score.
"""
import pathlib, re, subprocess, sys
sys.path.insert(0, str(pathlib.Path(__file__).parent))
import probe, tu
names = ['func_801B0668', 'func_801BD640', 'func_801B132C',
         'func_801B0CDC', 'func_801BF190', 'func_801C1C34',
         'func_801C7310', 'func_801C4240', 'func_801BDA6C']
for name in names:
    path = tu.draft(name)
    source, prefix = tu.ctx(name)
    text = source.read_text()
    pattern = r'#pragma GLOBAL_ASM\("[^"\n]*/' + name + r'\.s"\)'
    text = re.sub(pattern, lambda _: path.read_text(), text)
    scratch = pathlib.Path('/tmp/t070-full-' + name + '.c')
    scratch.write_text(text)
    command = [str(probe.ROOT/'.venv/bin/python'),
               str(probe.ROOT/'tools/ext/asm-processor/build.py'),
               str(probe.ROOT/'tools/ext/ido/5.3/cc'), '--',
               str(probe.ROOT/'tools/ext/binutils/bin/mips64-elf-as'),
               '-EB', '-mips3', '-32', '-G', '0', '-I', 'include', '--',
               '-c', '-G', '0', '-non_shared', '-Xcpluscomm',
               '-Wab,-r4300_mul', '-O2', '-mips2', '-32', '-Iinclude',
               '-o', str(scratch.with_suffix('.o')), str(scratch)]
    result = subprocess.run(command, cwd=probe.ROOT, capture_output=True, text=True)
    print(name, 'full TU:', 'OK' if result.returncode == 0 else 'FAILED',
          'prefix score:', probe.probe(name, prefix + path.read_text()), flush=True)
    if result.returncode:
        print(result.stdout, result.stderr)
        sys.exit(result.returncode)
