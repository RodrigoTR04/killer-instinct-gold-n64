import importlib.util, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
fn = sys.argv[1]
for d in sys.argv[2:]:
    print(d, dict(screen.measure(fn, Path(d))))
