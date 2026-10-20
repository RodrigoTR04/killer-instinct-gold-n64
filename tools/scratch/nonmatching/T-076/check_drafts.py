#!/usr/bin/env python3
"""Compile each retained draft through asm-processor in its complete production TU.
Scratch objects are never linked into the ROM. Also print the T-056 prefix score.
"""
import pathlib, re, subprocess, sys, struct
sys.path.insert(0, str(pathlib.Path(__file__).parent))
import probe, tu
names = ['func_801B0668', 'func_801BD640', 'func_801B132C',
         'func_801B0CDC', 'func_801BF190', 'func_801C1C34',
         'func_801C7310', 'func_801C4240', 'func_801BDA6C', 'func_801B3DB0']
for name in names:
    path = tu.draft(name)
    source, prefix = tu.ctx(name)
    text = source.read_text()
    pattern = r'#pragma GLOBAL_ASM\("[^"\n]*/' + name + r'\.s"\)'
    text = re.sub(pattern, lambda _: path.read_text(), text)
    # T-071 added the same render layout after the C1C34 pragma. Reuse
    # the candidate's identical layout in this scratch TU to avoid two
    # incompatible anonymous-struct declarations of the same symbol.
    if name == 'func_801C1C34':
        text = text.replace('extern T030Render2D34 D_802C9F70;', '')
    scratch = pathlib.Path('/tmp/t076-full-' + name + '.c')
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

    code, masks, _ = probe.cmp.elf_function(scratch.with_suffix('.o'), name)
    offset = int(name[5:], 16) - 0x801ABB20
    target = (probe.ROOT/'build/segments/ovl_7DF8.bin').read_bytes()[offset:offset + probe.rows[name]['bytes']]
    actual = struct.unpack('>' + str(len(code)//4) + 'I', code)
    expected = struct.unpack('>' + str(len(target)//4) + 'I', target)
    score = sum(x & masks[i] != y & masks[i] for i, (x, y) in enumerate(zip(actual, expected))) + abs(len(actual) - len(expected))
    print('  full TU words / compiled bytes / original bytes:', score, len(code), len(target), flush=True)
