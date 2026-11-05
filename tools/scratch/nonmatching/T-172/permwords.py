"""Score permuter output dirs by official word count (extract just the function)."""
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')))
import detail

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743')


def extract(function, path):
    text = Path(path).read_text()
    i = text.index(function + '(')
    # back up to the return type line
    start = text.rfind('\n', 0, i) + 1
    lines = text[start:].split('\n')
    out, depth = [], 0
    for ln in lines:
        out.append(ln)
        depth += ln.count('{') - ln.count('}')
        if depth == 0 and len(out) > 1:
            break
    return '\n'.join(out) + '\n'


def score_dir(function, draft_head, permdir):
    draft = (ROOT / draft_head).read_text()
    externs = draft[:draft.index(function + '(')]
    body = extract(function, Path(permdir) / 'source.c')
    return externs + body


if __name__ == '__main__':
    function = sys.argv[1]
    draft_head = sys.argv[2]
    v = {}
    for d in sorted(Path(sys.argv[3]).iterdir()):
        if not (d / 'score.txt').exists():
            continue
        try:
            v[d.name] = score_dir(function, draft_head, d)
        except Exception as e:
            print('skip', d.name, e)
    detail.run(function, v, jobs=8)
