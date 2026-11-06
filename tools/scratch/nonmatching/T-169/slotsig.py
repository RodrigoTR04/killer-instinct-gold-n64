#!/usr/bin/env python3
"""Extract the exact sp-slot signature (offset -> use count) of a function from
either the splat asm (target) or a compiled draft, so declaration-order sweeps
can be filtered on LAYOUT instead of score."""
import importlib.util
import re
import subprocess
import sys
import tempfile
from collections import Counter
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4f670e05')
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)
OBJDUMP = ROOT / 'tools/ext/binutils/bin/mips64-elf-objdump'


def target_sig(function):
    for tu in sorted((ROOT / 'src').glob('*/*.c')):
        text = tu.read_text()
        m = re.search(r'#pragma GLOBAL_ASM\("([^"]*/' + re.escape(function) + r'\.s)"\)', text)
        if m:
            path = ROOT / m.group(1)
            break
    else:
        raise SystemExit('no owner')
    c = Counter()
    frame = None
    for line in path.read_text().splitlines():
        body = re.sub(r'/\*[^*]*\*/', ' ', line).split('#')[0]
        if frame is None:
            mm = re.search(r'addiu\s+\$sp,\s*\$sp,\s*(-0x[0-9A-Fa-f]+)', body)
            if mm:
                frame = int(mm.group(1), 16)
        for off in re.findall(r'(-?(?:0x[0-9A-Fa-f]+|\d+))\(\$sp\)', body):
            c[int(off, 16) if 'x' in off else int(off)] += 1
    return frame, c


def draft_sig(function, draft, keep=None):
    owners = []
    for tu in sorted((ROOT / 'src').glob('*/*.c')):
        text = tu.read_text()
        m = re.search(r'#pragma GLOBAL_ASM\("[^"\n]*/' + re.escape(function) + r'\.s"\)', text)
        if m:
            owners.append((tu, text, m))
    if not owners:
        raise RuntimeError('no owner (already matched?)')
    tu, text, m = owners[0]
    source = text[:m.start()] + Path(draft).read_text() + text[m.end():]
    d = tempfile.mkdtemp(prefix='sig-')
    cfile = Path(d) / 'c.c'
    cfile.write_text(source)
    obj = cfile.with_suffix('.o')
    cmd = [ROOT / '.venv/bin/python', ROOT / 'tools/ext/asm-processor/build.py',
           ROOT / 'tools/ext/ido/5.3/cc', '--',
           ROOT / 'tools/ext/binutils/bin/mips64-elf-as', '-EB', '-mips3', '-32', '-G', '0',
           '-I', 'include', '--', '-c', '-G', '0', '-non_shared', '-Xcpluscomm',
           '-Wab,-r4300_mul', '-O2', '-mips2', '-32', '-Iinclude', '-o', obj, cfile]
    r = subprocess.run([str(x) for x in cmd], cwd=ROOT, capture_output=True, text=True)
    if r.returncode:
        raise RuntimeError(r.stderr[-1500:])
    asm = subprocess.run([str(OBJDUMP), '-dr', '--no-show-raw-insn', str(obj)],
                         capture_output=True, text=True).stdout
    started = False
    c = Counter()
    frame = None
    for line in asm.splitlines():
        if re.match(r'^[0-9a-f]{8} <' + re.escape(function) + r'>:$', line):
            started = True
            continue
        if started and re.match(r'^[0-9a-f]{8} <', line):
            break
        if not started:
            continue
        if frame is None:
            mm = re.search(r'addiu\s+sp,sp,-(0x[0-9a-f]+|\d+)', line)
            if mm:
                g = mm.group(1)
                frame = -int(g, 16) if g.startswith('0x') else -int(g)
        for off in re.findall(r'(-?(?:0x[0-9a-f]+|\d+))\(sp\)', line):
            c[int(off, 16) if 'x' in off else int(off)] += 1
    return frame, c


def fmt(frame, c):
    fh = f'0x{-frame:x} (sp,-{-frame})' if frame is not None else 'unknown'
    return f'frame {fh}: ' + ' '.join(f'{k:#04x}={v}' for k, v in sorted(c.items()))


if __name__ == '__main__':
    fn = sys.argv[1]
    print('TARGET ', fmt(*target_sig(fn)))
    print('DRAFT  ', fmt(*draft_sig(fn, sys.argv[2])))
