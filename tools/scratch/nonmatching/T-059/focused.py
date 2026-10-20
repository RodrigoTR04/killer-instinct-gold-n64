from attempts import *
# Initialization scalar signedness influences IDO's constant sharing across stores.
n='18F20';s=paths[n].read_text()
for typ in ['u16','u32','u8']:
 t=s.replace('(*(s16 *)','(*('+typ+' *)') if typ!='u8' else s
 if typ=='u8':t=t.replace('(*(s8 *)','(*(u8 *)')
 test(n,'store_'+typ,t)
t=s.replace('    f32 temp_f0;','    f32 temp_f0;\n    s8 *order = &D_8004A5E0;')
for j in range(4):t=t.replace('(*(s8 *)((u8 *)(&D_8004A5E0) + '+('0x%X'%(j*7) if j*7>=10 else str(j*7))+'))','order[%d]'%(j*7))
test(n,'order_cursor',t)
# Resource table models: each slot has two independent player entries.
for n,ty in [('24714','T032Resource714'),('241BC','T032Resource1BC')]:
 s=paths[n].read_text();slots=re.findall(r'->slot([0-9A-F]+)',s)
 t=re.sub(r'typedef struct \{.*?\} '+ty+r';','typedef struct { u8 *address[2]; } ResourceSlot;',s)
 t=t.replace(ty+' *','ResourceSlot *').replace('('+ty+' *)(D_8004D278 + arg0 * 8)','((ResourceSlot *)D_8004D278) + arg0')
 for slot in set(slots):t=re.sub(r'(\w+)->slot'+slot+r'\b',lambda m:m[1]+'[%d].address[%d]'%(int(slot,16)//8,(int(slot,16)%8)//4),t)
 test(n,'pair_slots',t)
 # Flat array makes actual byte offset explicit without pretending to be a giant record.
 u=t.replace('typedef struct { u8 *address[2]; } ResourceSlot;','').replace('ResourceSlot *','u8 **').replace('(ResourceSlot *)','(u8 **)')
 u=re.sub(r'(\w+)\[(\d+)\].address\[(\d+)\]',lambda m:m[1]+'[%d]'%(int(m[2])*2+int(m[3])),u)
 test(n,'flat_slots',u)
# Audio pointer loop: pointer bound versus counter; width supported by original lhu/store.
n='2A4F0';s=(ROOT/(n+'-sequence_cursor.c')).read_text()
for tag,t in [('entry_end',s.replace('i<48','entry != D_80066C28->entries + 48')),('length_u16',s.replace('size,i,length;','size,i; u16 length;')),('length_s16',s.replace('size,i,length;','size,i; s16 length;')),('equal_counter',s.replace('i<48','i!=48'))]:test(n,tag,t)
# Renderer callback ABI: existing cast forces all float inputs through integer conversions.
n='131A4';s=paths[n].read_text()
test(n,'short_counters',s.replace('s32 part, i;','s16 part, i;'))
test(n,'byte_counters',s.replace('s32 part, i;','u8 part, i;'))
test(n,'draw_count',s.replace('    s32 part, i;','    s32 part, i, count;').replace('    if ((&D_8004A738)[part] > 0)', '    count = (&D_8004A738)[part];\n    if (count > 0)').replace('i < (&D_8004A738)[part]','i < count'))
# Vertex loop is four-way unrolled in original; an array of word records retains alignment.
n='170C4';s=paths[n].read_text()
for count in [2,4]:
 lines=[]
 for j in range(count): lines.append('        *var_v0[%d] = var_a0[%d];'%(j,j))
 t=s.replace('for (i = 0; i < 8; i++) *var_v0[i] = var_a0[i];','do {\n'+'\n'.join(lines)+'\n        var_v0 += %d; var_a0 += %d;\n        } while (var_a0 != &D_8004AEB8);'%(count,count))
 test(n,'vertices_group'+str(count),t)
# Color local arrays and packed source view.
n='1BB64';s=paths[n].read_text()
for typ in ['u16','u8','s8']:
 test(n,'color_'+typ,s.replace('s16 colors','%s colors'%typ).replace('s16 *dst','%s *dst'%typ))
# HUD argument ABI widths: casts must agree with source loads.
n='253D0';s=paths[n].read_text()
test(n,'hud_wide_abi',s.replace('func_800257FC(u8,u16,u8,u8)','func_800257FC(s32,s32,s32,s32)').replace('(u8)D_8004EA78','D_8004EA78').replace('func_80025FC4(T032Gfx253 **,s32,s32,u8,u8)','func_80025FC4(T032Gfx253 **,s32,s32,s32,s32)'))
# Keep signed transform indices, varying scope avoids a dubious unsigned change.
n='1AD04';s=paths[n].read_text()
t=s.replace('    s32 sp2C;\n    s32 sp28;','').replace('    sp2C = temp_t8;','    s32 sp2C = temp_t8;').replace('    sp28 =','    s32 sp28 =',1)
test(n,'scoped_indices',t)
test(n,'short_indices',s.replace('s32 sp2C;','s16 sp2C;').replace('s32 sp28;','s16 sp28;'))
(ROOT/'focused-results.json').write_text(json.dumps(rows,indent=2))
