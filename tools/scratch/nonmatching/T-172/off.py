"""Official word count for a draft file: off.py func_XXXX path.c"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
sys.path.insert(0, str(ROOT / 'tools/permuter'))
import screen  # noqa: E402

function = sys.argv[1]
for path in sys.argv[2:]:
    r = screen.measure(function, Path(path))
    err = r.get('error') or ''
    print(f'{r["words"]}\t{r["compiled"]}\t{path}\t{err.splitlines()[-1][:160] if err else ""}')
