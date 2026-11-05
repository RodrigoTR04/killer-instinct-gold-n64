"""Compile a standalone C snippet with the project's IDO 5.3 and show prologue/offsets."""
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743')
OBJDUMP = ROOT / 'tools/ext/binutils/bin/mips64-elf-objdump'


def build(source, name='t'):
    with tempfile.TemporaryDirectory(prefix='t172-') as d:
        c = Path(d) / f'{name}.c'
        o = Path(d) / f'{name}.o'
        c.write_text(source)
        cmd = [ROOT / '.venv/bin/python', ROOT / 'tools/ext/asm-processor/build.py',
               ROOT / 'tools/ext/ido/5.3/cc', '--',
               ROOT / 'tools/ext/binutils/bin/mips64-elf-as', '-EB', '-mips3', '-32', '-G', '0',
               '-I', str(ROOT / 'include'), '--', '-c', '-G', '0', '-non_shared', '-Xcpluscomm',
               '-Wab,-r4300_mul', '-O2', '-mips2', '-32', '-Iinclude', '-o', str(o), str(c)]
        r = subprocess.run([str(x) for x in cmd], cwd=ROOT, capture_output=True, text=True)
        if r.returncode:
            print('COMPILE FAIL', r.stderr[-1500:])
            return []
        return subprocess.run([str(OBJDUMP), '-dr', '--no-show-raw-insn', str(o)],
                              capture_output=True, text=True).stdout.splitlines()


def show(source, label=''):
    lines = build(source)
    print(f'--- {label}')
    for ln in lines:
        s = ln.split('\t')[-1].strip()
        if any(k in s for k in ('addiu', 'sp)', 'jal', 'sw ', 'sdc1', 'ldc1', 'j', 'nop', 'mtc1')):
            if 'sp' in s or 'jal' in s or 'sd' in s or 'ldc1' in s or 'mtc1' in s:
                print('   ', s)
