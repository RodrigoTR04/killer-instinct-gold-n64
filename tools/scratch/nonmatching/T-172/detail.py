"""Score variants: official words + byte size + draft frame size + prologue."""
import importlib.util
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmp155', ROOT / 'tools/scratch/nonmatching/T-155/cmp.py')
cmp = importlib.util.module_from_spec(spec)
spec.loader.exec_module(cmp)
spec2 = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec2)
spec2.loader.exec_module(screen)


def detail(function, text, name='cand', show=0):
    with tempfile.TemporaryDirectory(prefix='t172-') as d:
        draft = Path(d) / f'{name.replace("/", "_")}.c'
        draft.write_text(text)
        r = screen.measure(function, draft)
        words, size, ok = r['words'], r['compiled'], r['error']
        if ok:
            return words, size, None, []
        source, tu = cmp.build_source(function, draft)
        o = cmp.compile_source(source, Path(d) / 'c.c')
        pairs = cmp.draft_raw(o, function)
    lines = [cmp.canon(cmp.apply_relocs(i, rr)) for _, i, rr in pairs]
    frame = None
    for ln in lines:
        m = re.search(r'addiu\s+sp\s*,\s*sp\s*,\s*-(\d+)', ln)
        if m:
            frame = int(m.group(1))
            break
    return words, size, frame, lines[:show] if show else []


def run(function, variants, jobs=1, show=0):
    import concurrent.futures
    def one(kv):
        name, text = kv
        try:
            return (name, *detail(function, text, name, show))
        except SystemExit:
            return (name, None, None, 'compile fail', [])
        except Exception as e:
            return (name, None, None, str(e)[-120:], [])
    with concurrent.futures.ThreadPoolExecutor(max_workers=jobs) as pool:
        out = list(pool.map(one, variants.items()))
    out.sort(key=lambda r: (r[1] is None, r[1] if r[1] is not None else 10**9))
    for name, words, size, frame, lines in out:
        fr = hex(frame) if isinstance(frame, int) else frame
        print(f'{words}\t{size}\t{fr}\t{name}')
        for ln in lines:
            print('     ', ln)
    return out
