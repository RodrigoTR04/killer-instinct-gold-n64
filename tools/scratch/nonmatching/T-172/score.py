"""In-process draft scorer for T-172 (imports screen.measure directly)."""
import importlib.util
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)


def score(function, text, name='cand'):
    path = Path(ROOT) / 'tools/scratch/nonmatching/T-172' / f'.{name}.c'
    path.write_text(text)
    try:
        result = screen.measure(function, path)
        return result['words'], result['compiled'], result['error']
    except Exception as error:
        return None, None, str(error)[-300:]


def masked(function, text, name='cand'):
    """Register-masked / canonical sequence diff count via cmp.py's own logic."""
    import subprocess, tempfile, os
    path = Path(ROOT) / 'tools/scratch/nonmatching/T-172' / f'.{name}.c'
    path.write_text(text)
    env = dict(os.environ, REGMASK='1', COUNT='1')
    out = subprocess.run([str(ROOT / '.venv/bin/python'),
                          str(ROOT / 'tools/scratch/nonmatching/T-155/cmp.py'),
                          function, str(path)],
                         capture_output=True, text=True, env=env)
    if 'diffwords=' in out.stdout:
        return int(out.stdout.strip().split('diffwords=')[-1])
    return None


def compare(function, text, name='cand'):
    """Full canonical diff lines (unmasked)."""
    import subprocess, os
    path = Path(ROOT) / 'tools/scratch/nonmatching/T-172' / f'.{name}.c'
    path.write_text(text)
    out = subprocess.run([str(ROOT / '.venv/bin/python'),
                          str(ROOT / 'tools/scratch/nonmatching/T-155/cmp.py'),
                          function, str(path), '--context', '1'],
                         capture_output=True, text=True)
    return out.stdout
