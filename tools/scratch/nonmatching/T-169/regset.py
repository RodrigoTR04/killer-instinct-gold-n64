#!/usr/bin/env python3
"""Compare the callee-saved register set (integer + float) and frame size of a
draft against the target. The saved-set is what IDO's allocator decides, so it
is a much sharper layout probe than the word count."""
import importlib.util
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4f670e05')
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)
OBJDUMP = ROOT / 'tools/ext/binutils/bin/mips64-elf-objdump'
FS = [f'f{i}' for i in range(20, 32)]
GS = ['s0', 's1', 's2', 's3', 's4', 's5', 's6', 's7', 'fp', 'ra', 'gp']


def _summary(lines):
    frame = None
    saved = set()
    floats = set()
    for line in lines:
        body = line.split('#')[0]
        if frame is None:
            mm = re.search(r'addiu\s+\$?sp,\s*\$?sp,\s*-(0x[0-9A-Fa-f]+|\d+)', body)
            if mm:
                g = mm.group(1)
                frame = int(g, 16) if g.startswith('0x') else int(g)
        mm = re.search(r'\b(?:sw|sd)\s+\$?(s[0-7]|fp|ra|gp)\s*[,]', body)
        if mm:
            saved.add(mm.group(1))
        mm = re.search(r'\b(?:sdc1|sd|swc1|sw)\s+\$?(f2[0-9]|f3[01])\s*[,]', body)
        if mm:
            floats.add(mm.group(1))
    return frame, saved, floats


def target(fn):
    for tu in sorted((ROOT / 'src').glob('*/*.c')):
        text = tu.read_text()
        m = re.search(r'#pragma GLOBAL_ASM\("([^"]*/' + re.escape(fn) + r'\.s)"\)', text)
        if m:
            path = ROOT / m.group(1)
            break
    else:
        raise SystemExit('no owner')
    return _summary(path.read_text().splitlines())


def draft(fn, dpath):
    owners = []
    for tu in sorted((ROOT / 'src').glob('*/*.c')):
        text = tu.read_text()
        m = re.search(r'#pragma GLOBAL_ASM\("[^"\n]*/' + re.escape(fn) + r'\.s"\)', text)
        if m:
            owners.append((tu, text, m))
    if not owners:
        raise RuntimeError('already matched')
    tu, text, m = owners[0]
    source = text[:m.start()] + Path(dpath).read_text() + text[m.end():]
    d = tempfile.mkdtemp(prefix='regs-')
    c = Path(d) / 'c.c'
    c.write_text(source)
    o = c.with_suffix('.o')
    cmd = [ROOT / '.venv/bin/python', ROOT / 'tools/ext/asm-processor/build.py',
           ROOT / 'tools/ext/ido/5.3/cc', '--',
           ROOT / 'tools/ext/binutils/bin/mips64-elf-as', '-EB', '-mips3', '-32', '-G', '0',
           '-I', 'include', '--', '-c', '-G', '0', '-non_shared', '-Xcpluscomm',
           '-Wab,-r4300_mul', '-O2', '-mips2', '-32', '-Iinclude', '-o', o, c]
    r = subprocess.run([str(x) for x in cmd], cwd=ROOT, capture_output=True, text=True)
    if r.returncode:
        raise RuntimeError(r.stderr[-900:])
    asm = subprocess.run([str(OBJDUMP), '-dr', '--no-show-raw-insn', str(o)],
                         capture_output=True, text=True).stdout
    started = False
    lines = []
    for line in asm.splitlines():
        if re.match(r'^[0-9a-f]{8} <' + re.escape(fn) + r'>:$', line):
            started = True
            continue
        if started and re.match(r'^[0-9a-f]{8} <', line):
            break
        if started:
            lines.append(line)
    return _summary(lines)


def show(tag, res):
    frame, saved, floats = res
    fh = f'0x{frame:x}' if frame else '?'
    ints = ','.join(sorted(saved, key=lambda r: GS.index(r) if r in GS else 99))
    flts = ','.join(sorted(floats, key=lambda r: int(r[1:])))
    print(f'{tag:7s} frame {fh:>5}  int {{{ints}}}  float {{{flts}}}')


if __name__ == '__main__':
    fn = sys.argv[1]
    show('TARGET', target(fn))
    for p in sys.argv[2:]:
        try:
            show(Path(p).stem[:7], draft(fn, p))
        except Exception as e:
            print(f'{Path(p).name}: FAIL {str(e)[:120]}')
