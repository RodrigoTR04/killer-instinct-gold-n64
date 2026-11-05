"""Compile standalone snippets with IDO 5.3 and extract frame size + prologue."""
import re
import subprocess
import tempfile
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743')
OBJDUMP = ROOT / 'tools/ext/binutils/bin/mips64-elf-objdump'


def insns(source, name='t'):
    """Return list of (mnemonic, operands) for the compiled snippet."""
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
            raise SystemExit('COMPILE FAIL\n' + r.stderr[-1200:])
        text = subprocess.run([str(OBJDUMP), '-dr', '--no-show-raw-insn', str(o)],
                             capture_output=True, text=True).stdout
    out = []
    for line in text.splitlines():
        parts = [p.strip() for p in line.split('\t')]
        if len(parts) >= 3 and re.fullmatch(r'[0-9a-f]+:', parts[0]):
            out.append((parts[1], parts[2]))
    return out


def frame(source):
    for mnem, ops in insns(source):
        if mnem == 'addiu' and ops.replace(' ', '').startswith('sp,sp,-'):
            return int(ops.split(',')[-1])
    return 0


def slots(source):
    """All sp-relative accesses, in order."""
    res = []
    for mnem, ops in insns(source):
        for m in re.finditer(r'(-?\d+)\(sp\)', ops):
            res.append((mnem, int(m.group(1))))
        m = re.search(r'sp,sp,(-?\d+)', ops.replace(' ', ''))
        if m:
            res.append(('frame', int(m.group(1))))
    return res
