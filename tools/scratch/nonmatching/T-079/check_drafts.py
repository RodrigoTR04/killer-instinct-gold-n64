#!/usr/bin/env python3
"""Compile each retained draft through asm-processor in its complete production TU.
Scratch objects are never linked into the ROM. Also print the T-056 prefix score.
"""
import pathlib, re, subprocess, sys, struct
sys.path.insert(0, str(pathlib.Path(__file__).parent))
import probe, tu
names = ['func_801BDF94','func_801BCB70','func_801C23C0','func_801C08F8']
for name in names:
    path = tu.draft(name)
    source, prefix = tu.ctx(name)
    text = source.read_text()
    pattern = r'#pragma GLOBAL_ASM\("[^"\n]*/' + name + r'\.s"\)'
    text = re.sub(pattern, lambda _: path.read_text(), text)
    if name == 'func_801C23C0':
        text = text.replace('extern T030Render2D34 D_802C9F70;', '')
        text = text.replace('typedef struct { u32 w0,w1; } T030Cmd23C0;',
                            'typedef union { struct { u32 w0, w1; } words; u64 full; } T030Cmd2D34;\ntypedef T030Cmd2D34 T030Cmd23C0;')
        declaration = 'typedef union { struct { u32 w0, w1; } words; u64 full; } T030Cmd2D34;'
        first = text.index(declaration)
        text = text[:first + len(declaration)] + text[first + len(declaration):].replace(declaration, '')
        # Use the owning TU's aligned command union throughout the candidate.
        start = text.index('u8 func_801C23C0(')
        end = text.index('typedef struct { u8 pad[0xF8]', start)
        text = text[:start] + text[start:end].replace('->w', '->words.w') + text[end:]
    scratch = pathlib.Path('/tmp/t079-full-' + name + '.c')
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
