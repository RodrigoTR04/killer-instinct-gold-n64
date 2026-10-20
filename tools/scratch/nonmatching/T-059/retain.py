from pathlib import Path
import re,json
root=Path(__file__).parent
choices={'T-022/func_8001E0B4.c':('1E0B4-wide_half_scale',26,648),'T-022/func_80018F20.c':('18F20-colors_unsigned',90,696),'T-022/func_8001BB64.c':('1BB64-blue_red_green',143,592),'T-022/func_8001D47C.c':('1D47C-byte_offset',141,748),'T-024/func_8002A4F0.c':('2A4F0-entry_end',65,920)}
for p,(tag,count,size) in choices.items():
 s=(root/(tag+'.c')).read_text()
 s=re.sub(r'/\* T-054 DRAFT:.*?\*/',f'/* T-059 DRAFT: {count} relocation-masked positional words differ; {size} emitted bytes. See T-059/REPORT.md. */',s,count=1)
 (root.parent/p).write_text(s)
(root/'retained.json').write_text(json.dumps(choices,indent=2)+'\n')
