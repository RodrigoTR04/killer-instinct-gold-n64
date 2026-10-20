"""Reproduce CBCC's scheduling fix and the different relocation target.
Run from repo root after extraction. Only /tmp compiler outputs are written.
"""
from pathlib import Path
import sys, subprocess, struct, tempfile
sys.path.insert(0, 'tools/scratch/flagprobe')
from compare import elf_function
source = Path('tools/scratch/nonmatching/T-022/func_8001CBCC.c').read_text()
source = '#include "common.h"\nextern f32 sinf(f32), cosf(f32);\n' + source
original = Path('build/segments/main.bin').read_bytes()[0xD26C:0xD3AC]
variants = {
    'extern': source,
    'const extern': source.replace('extern f32 D_80045C00;', 'extern const f32 D_80045C00;'),
    'local factor': source.replace('    x *= D_80045C00;', '    f32 factor = D_80045C00;\n    x *= factor;').replace('y *= D_80045C00', 'y *= factor').replace('z *= D_80045C00', 'z *= factor'),
    'literal': source.replace('*= D_80045C00', '*= 0.017453292f'),
}
with tempfile.TemporaryDirectory(prefix='t046-rotation-') as tmp:
    src, obj = Path(tmp)/'probe.c', Path(tmp)/'probe.o'
    for name, code in variants.items():
        src.write_text(code)
        subprocess.run(['tools/ext/ido/5.3/cc', '-c', '-G', '0', '-non_shared', '-Xcpluscomm', '-Wab,-r4300_mul', '-O2', '-mips2', '-32', '-Iinclude', '-o', str(obj), str(src)], check=True)
        emitted, masks, rels = elf_function(obj, 'func_8001CBCC')
        different = [i*4 for i, (a,b,m) in enumerate(zip(struct.unpack('>'+str(len(emitted)//4)+'I', emitted), struct.unpack('>80I', original), masks)) if a&m != b&m]
        print(name, 'bytes:', len(emitted), 'masked differences:', [hex(x) for x in different])
        reloc = subprocess.run(['tools/ext/binutils/bin/mips64-elf-objdump', '-r', str(obj)], capture_output=True, text=True, check=True).stdout
        print('\n'.join(line for line in reloc.splitlines() if 'D_80045C00' in line or '.rodata' in line))
