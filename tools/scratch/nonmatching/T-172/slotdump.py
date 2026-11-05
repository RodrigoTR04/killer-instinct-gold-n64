"""Score + full sp-slot list for one draft."""
import importlib.util
import re
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmp155', ROOT / 'tools/scratch/nonmatching/T-155/cmp.py')
cmp = importlib.util.module_from_spec(spec)
spec.loader.exec_module(cmp)


def dump(function, text, name='cand'):
    with tempfile.TemporaryDirectory(prefix='t172-') as d:
        draft = Path(d) / (name.replace('/', '_') + '.c')
        draft.write_text(text)
        source, tu = cmp.build_source(function, draft)
        o = cmp.compile_source(source, Path(d) / 'c.c')
        pairs = cmp.draft_raw(o, function)
    lines = [cmp.canon(cmp.apply_relocs(i, rr)) for _, i, rr in pairs]
    return lines


def slots(lines):
    out = []
    for ln in lines:
        m = re.search(r'sp,sp,-(\d+)', ln.replace(' ', ''))
        if m:
            out.append(('frame', int(m.group(1))))
        for m in re.finditer(r'(\d+)\(sp\)', ln):
            out.append((ln.split()[0], int(m.group(1))))
    return out


if __name__ == '__main__':
    fn, path = sys.argv[1], sys.argv[2]
    print(slots(dump(fn, Path(path).read_text())))
