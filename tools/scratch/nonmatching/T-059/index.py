from attempts import *
n='1AD04';s=paths[n].read_text()
t=s.replace('s32 transform;','u32 transform;').replace('s32 sp2C;','u32 sp2C;').replace('s32 sp28;','u32 sp28;').replace('s32 temp_t8;','u32 temp_t8;')
test(n,'transform_index_type',t)
(ROOT/'index-results.json').write_text(json.dumps(rows,indent=2))
