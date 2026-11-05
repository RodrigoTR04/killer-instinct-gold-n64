"""Find functions that home an incoming FP arg at exactly frame_size(sp)."""
import re
import sys
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743')
pat_frame = re.compile(r'addiu\s+\$sp,\s*\$sp,\s*-0x([0-9A-Fa-f]+)')
pat_sdc1 = re.compile(r'sdc1\s+\$(f\d+),\s*0x([0-9A-Fa-f]+)\(\$sp\)')

hits = []
for s in ROOT.glob('asm/**/*.s'):
    text = s.read_text()
    if 'func_' not in text:
        continue
    frame = None
    for line in text.splitlines():
        m = pat_frame.search(line)
        if m and frame is None:
            frame = int(m.group(1), 16)
            continue
        m = pat_sdc1.search(line)
        if m and frame is not None:
            off = int(m.group(2), 16)
            if off == frame:
                hits.append((s, frame, m.group(1)))
                break
for s, frame, reg in hits:
    print(hex(frame), reg, s.relative_to(ROOT))
