"""Recheck all seven assigned drafts in complete production TUs."""
from pathlib import Path
import sys,json
ROOT=Path(__file__).resolve().parents[4]
sys.path.insert(0,str(ROOT/'tools/permuter'))
import screen
sys.path.insert(0,str(ROOT/'tools/scratch/nonmatching/T-096'))
from probe import compile
names=['801B2EF4','801B310C','801B3324','801B353C','801B3754','801B396C','801B3B84']
rows=[]
for name in names:
    fn='func_'+name
    draft=ROOT/'tools/scratch/nonmatching/T-025'/(fn+'.c')
    if draft.exists():
        row=screen.measure(fn,draft)
    else:
        row=dict(function=fn,context='production full TU',**compile(fn,(ROOT/'src/ovl_7DF8/ovl_7DF8_5ED0.c').read_text(),'production',True))
    rows.append(row)
    print(row,flush=True)
(Path(__file__).parent/'final.json').write_text(json.dumps(rows,indent=2)+'\n')
