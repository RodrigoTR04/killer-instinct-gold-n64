"""Report words + frame + the non-boilerplate sp slots (hi spill, z spill) for a draft."""
import re
import sys

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail, slotdump


def profile(function, text, name='cand'):
    words, size, frame, _ = detail.detail(function, text, name)
    if frame is None:
        return words, size, None, []
    lines = slotdump.dump(function, text, name)
    sl = slotdump.slots(lines)
    keep = [(m, o) for m, o in sl if o not in (frame, 0x14, 0x3C)]
    return words, size, frame, keep


if __name__ == '__main__':
    function, path = sys.argv[1], sys.argv[2]
    print(profile(function, open(path).read()))
