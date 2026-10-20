from attempts import *
n='1AD04';s=paths[n].read_text();t=s
for a in range(0x80048940,0x8004896c,4):
 name='D_%08X'%a; value=struct.unpack_from('>f',base,a-0x8000f960)[0];print(name,value)
 t=t.replace('extern f32 '+name+';','').replace(name,repr(value)+'f')
test(n,'literal_pool',t)
(ROOT/'float-results.json').write_text(json.dumps(rows,indent=2))
