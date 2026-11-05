"""List functions whose sdc1/sw of an incoming arg lands at offset >= frame size."""
import re
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743')
pat_frame = re.compile(r'addiu\s+\$sp,\s*\$sp,\s*-(0x[0-9A-Fa-f]+)')
pat_st = re.compile(r'(sdc1|sw|sd)\s+\$(\w+),\s*(0x[0-9A-Fa-f]+)\(\$sp\)')
ARGREGS = {'f12', 'f13', 'f14', 'f15', 'a0', 'a1', 'a2', 'a3'}

for s in sorted(ROOT.glob('asm/**/*.s')):
    text = s.read_text()
    frame = None
    out = []
    for line in text.splitlines():
        if frame is None:
            m = pat_frame.search(line)
            if m:
                frame = int(m.group(1), 16)
            continue
        for m in pat_st.finditer(line):
            reg = m.group(2)
            off = int(m.group(3), 16)
            if reg in ARGREGS and off >= frame:
                out.append((reg, off))
    if out:
        print(hex(frame), out[:4], s.relative_to(ROOT))
