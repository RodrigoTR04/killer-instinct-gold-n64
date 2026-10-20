from attempts import *
selected={
'170C4':'eight_indexed','1BB64':'clean','1E0B4':'best','131A4':'best',
'24714':'full_width_dispatch','1D47C':'best','253D0':'best','27E1C':'best',
'30440':'byte_source_cursor','3EF90':'best','327E8':'best','2A4F0':'best',
'18F20':'literal-all_literals','193DC':'literal-D_80048908','1AD04':'repaired','1B134':'repaired',
'241BC':'full_width_dispatch'}
# refine.py retained the shorter counter form; preserve the semantics of the original full-width counters instead.
p=ROOT/'func_80030440-byte_source_cursor.c'
s=(ROOT/'func_80030440-base.c').read_text().replace('s32 source = 8;','u8 *source = image + 8;').replace('image[source++]','*source++');p.write_text(s)
rows=[]
for path in paths:
 n=path.stem[8:];fn=path.stem
 if n in ['16910','1B620']:
  path.unlink();rows.append({'function':fn,'result':'MATCHED'});continue
 if n not in selected:continue
 s=(ROOT/(fn+'-'+selected[n]+'.c')).read_text();r=probe(s,fn)
 assert 'words' in r,(fn,r)
 # Do not retain historical stale claims in the selected draft header.
 s=re.sub(r'/\* (?:T-022 DRAFT|DRAFT\.)[^*]*\*/\s*','',s,count=1)
 s='/* T-054 DRAFT: %d relocation-masked positional words differ; %d emitted bytes. See T-054/REPORT.md. */\n'%(r['words'],r['bytes'])+s
 path.write_text(s);rows.append({'function':fn,'result':'IMPROVED',**r,'candidate':selected[n]})
(ROOT/'retained.json').write_text(json.dumps(rows,indent=2)+'\n')
