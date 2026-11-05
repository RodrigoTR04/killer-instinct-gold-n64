"""For each asm function: frame size vs highest in-frame slot used (to spot inflated frames)."""
import re
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743')
pat_frame = re.compile(r'addiu\s+\$sp,\s*\$sp,\s*-(0x[0-9A-Fa-f]+)')
pat_off = re.compile(r'(0x[0-9A-Fa-f]+)\(\$sp\)')

rows = []
for s in sorted(ROOT.glob('asm/**/*.s')):
    text = s.read_text()
    name = s.stem
    for block in re.split(r'\n(?=glabel )', text):
        m = re.search(r'glabel (\w+)', block)
        if not m:
            continue
        f = pat_frame.search(block)
        if not f:
            continue
        frame = int(f.group(1), 16)
        offs = [int(o, 16) for o in pat_off.findall(block)]
        inside = [o for o in offs if o < frame]
        top = max(inside) if inside else -4
        rows.append((frame - (top + 4), frame, top, m.group(1), str(s.relative_to(ROOT))))
rows.sort(reverse=True)
for pad, frame, top, fn, path in rows[:25]:
    print(f'pad={pad:#x}\tframe={frame:#x}\ttop={top:#x}\t{fn}\t{path}')
print('total', len(rows), 'zero-pad', sum(1 for r in rows if r[0] == 0))
