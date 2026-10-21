"""Compare original cluster shapes and full-TU draft instruction differences."""
from pathlib import Path
import sys,json,difflib
ROOT=Path(__file__).resolve().parents[4]
sys.path.insert(0,str(ROOT/'tools/scratch/nonmatching/T-117'))
from compare_templates import instructions
sys.path.insert(0,str(ROOT/'tools/scratch/nonmatching/T-096'))
from probe import source,compile
out=Path(__file__).parent
names=['func_801B2EF4','func_801B3B84']
(out/'original-shapes.diff').write_text(''.join(difflib.unified_diff(instructions(names[0]),instructions(names[1]),fromfile=names[0],tofile=names[1],n=5)))
# baseline.json is the immutable incoming-draft measurement.
