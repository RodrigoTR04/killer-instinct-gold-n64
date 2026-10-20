#!/usr/bin/env python3
"""Compile each independent T-041 draft and compare text at its original VRAM.

Run from the repository root after make extract. Outputs are temporary;
--write-evidence refreshes the human-readable comparison in this directory.
"""
from pathlib import Path
import argparse
import re
import subprocess
import tempfile

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--write-evidence', action='store_true')
args = parser.parse_args()
root = Path(__file__).resolve().parent
rom = Path('build/segments/ovl_7E00.bin').read_bytes()
prefix = 'tools/ext/binutils/bin/mips64-elf-'
sizes = {'801ADD20': 276, '801AF2E8': 64, '801B6858': 60,
         '801BABFC': 8, '801BAC04': 8, '801BB8AC': 8, '801C2508': 20}

def run(argv):
    return subprocess.check_output([str(x) for x in argv], text=True)

output = []
with tempfile.TemporaryDirectory(prefix='kig-T041-') as temp:
    temp = Path(temp)
    for address, size in sizes.items():
        name = 'func_' + address
        obj, elf, binary = (temp / (name + ext) for ext in ('.o', '.elf', '.bin'))
        run(['.venv/bin/python', 'tools/ext/asm-processor/build.py',
             'tools/ext/ido/5.3/cc', '--', prefix + 'as',
             '-EB', '-mips3', '-32', '-G', '0', '-I', 'include', '--',
             '-c', '-G', '0', '-non_shared', '-Xcpluscomm', '-Wab,-r4300_mul',
             '-O2', '-mips2', '-32', '-Iinclude', '-o', obj, root / (name + '.c')])
        symbols = run([prefix + 'nm', '-S', obj])
        body_size = int(re.search(r'^\S+ (\S+) T ' + name + '$', symbols, re.M)[1], 16)
        unresolved = re.findall(r'^\s+U (D_([0-9A-F]{8}))$', symbols, re.M)
        ldscript = temp / 'text.ld'
        ldscript.write_text('SECTIONS { .text 0x' + address +
                            ' : SUBALIGN(4) { *(.text) } /DISCARD/ : { *(.reginfo) *(.options) *(.mdebug) } }\n' +
                            ''.join(f'{name} = 0x{addr};\n' for name, addr in unresolved))
        run([prefix + 'ld', '-m', 'elf32ebmip', '-e', name, '-T', ldscript, '-o', elf, obj])
        run([prefix + 'objcopy', '-j', '.text', '-O', 'binary', elf, binary])
        draft = binary.read_bytes()
        start = int(address, 16) - 0x801AD900
        original = rom[start:start + size]
        mismatches = [i for i in range(0, min(size, len(draft)), 4)
                      if original[i:i+4] != draft[i:i+4]]
        heading = (f'{name}: original {size} B; draft body {body_size} B; '
                   f'draft TU .text {len(draft)} B; '
                   f'{len(mismatches)}/{min(size, len(draft)) // 4} overlapping words differ.\n'
                   'Mismatch offsets: ' + ', '.join(f'+0x{x:02X}' for x in mismatches) + '\n')
        print(heading)
        output.append(heading)
        original_dump = run([prefix + 'objdump', '-D', '-b', 'binary', '-m', 'mips:4300', '-EB',
                             '--adjust-vma=0x801AD900', '--start-address=0x' + address,
                             '--stop-address=' + hex(int(address, 16) + size + 16),
                             'build/segments/ovl_7E00.bin'])
        candidate_dump = run([prefix + 'objdump', '-d', '-z', elf])
        # Keep generated evidence independent of the temporary directory name.
        output.extend(['Original (includes 16 bytes after the slot):\n' + original_dump,
                       'Draft (linked at original address):\n' + candidate_dump.replace(str(elf), name + '.elf')])
if args.write_evidence:
    (root / 'comparison.txt').write_text('\n'.join(output))
