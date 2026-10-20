from attempts import *
# Scale arithmetic and boolean local shape; preserve explicit half-scale narrowing.
n='1E0B4';s=paths[n].read_text()
for tag,t in [('signed_scales',s.replace('u32 var_t1;','s32 var_t1;').replace('u32 var_t2;','s32 var_t2;')),('boolean_mirror',s.replace('''if ((s32) (*(u8 *)((u8 *)(temp_t3) + 0x21)) >= 0x80) {
                            var_t4 = 1;
                        } else {
                            var_t4 = 0;
                        }''','var_t4 = (*(u8 *)(temp_t3 + 0x21) & 0x80) != 0;')),('wide_mode',s.replace('u8 var_v1;','s32 var_v1;'))]:test(n,tag,t)
# Typed stage records let IDO share bases for related stores.
n='18F20';s=paths[n].read_text();t=s
fields={0:'display',4:'flags',8:'transform'}
for off in [4,8,0x10,0x14,0x18,0x1c,0x24,0x28,0x2c]:
 pattern=r'\(\*\([^\n]+?\*\)\(\(u8 \*\)\(D_8004A4C0\) \+ '+('0x%X'%off if off>=10 else str(off))+r'\)\)'
 t=re.sub(pattern,'((Stage *)D_8004A4C0)[%d].%s'%(off//12,fields[off%12]),t)
t='typedef struct { void *display; s16 flags,pad; s32 transform; } Stage;\n'+t
test(n,'stage_records',t)
for tag,old,new in [('half_constant','D_8004AC84 / 2.0f','D_8004AC84 * 0.5f'),('byte_table','extern s8 D_8004A5E0;','extern s8 D_8004A5E0[4][7];')]:
 u=s.replace(old,new)
 if tag=='byte_table':
  for j in range(4):u=u.replace('(*(s8 *)((u8 *)(&D_8004A5E0) + '+('0x%X'%(j*7) if j*7>=10 else str(j*7))+'))','D_8004A5E0[%d][0]'%j)
 test(n,tag,u)
# Resource records actually consist of interleaved two-player address pairs.
for n,ty in [('24714','T032Resource714'),('241BC','T032Resource1BC')]:
 s=paths[n].read_text();t=s
 # Replace padded fake structure with indexed arrays at the real base.
 slots=re.findall(r'u8 \*slot([0-9A-F]+)',s.split('extern')[0])
 t=re.sub(r'typedef struct \{.*?\} '+ty+r';', 'typedef struct { u8 *address[2]; } ResourceSlot;',t)
 t=t.replace(ty+' *','ResourceSlot *')
 t=t.replace('('+ty+' *)(D_8004D278 + arg0 * 8)','((ResourceSlot *)D_8004D278) + arg0')
 for slot in slots:t=re.sub(r'(\w+)->slot'+slot+r'\b',lambda m:m[1]+'[%d].address[%d]'%(int(slot,16)//8,(int(slot,16)%8)//4),t)
 test(n,'slot_arrays',t)
 test(n,'direct_dispatch',s.replace('temp_v0 = D_8004EA9C[arg0];\n    switch (temp_v0)','switch (D_8004EA9C[arg0])'))
# Explicit pointer loop with fixed source/destination strides.
n='170C4';s=paths[n].read_text()
test(n,'pointer_vertices',s.replace('for (i = 0; i < 8; i++) *var_v0[i] = var_a0[i];','do { **var_v0++ = *var_a0++; } while (var_a0 != &D_8004AEB8);'))
test(n,'equal_vertices',s.replace('i < 8','i != 8'))
test(n,'indexed_objects',s.replace('var_v0_2 = &D_801D3430;\n    do {','for (i = 0; i < 40; i++) {\n        var_v0_2 = &D_801D3430 + i;').replace('        var_v0_2++;\n    } while ((u8 *)var_v0_2 != (u8 *)&D_801D5C30);','    }'))
# Color loop induction, local channel type and switch lowering.
n='1BB64';s=paths[n].read_text()
test(n,'indexed_colors',s.replace('s16 *dst;','s16 *dst; s32 i;').replace('''src = &D_8004AC92; dst = colors;
    do {
        *dst = *src++ + brightness;
        if (*dst >= 128) *dst = 127;
        dst++;
    } while (src != &D_8004AC92 + 3);''','''for (i = 0; i < 3; i++) {
        colors[i] = (&D_8004AC92)[i] + brightness;
        if (colors[i] >= 128) colors[i] = 127;
    }'''))
test(n,'wide_channels',s.replace('s16 colors[3];','s32 colors[3];').replace('s16 *dst;','s32 *dst;'))
test(n,'wide_mode',s.replace('u8 amount,mode;','s32 amount,mode;'))
# Palette destination cursor reproduces original null-based hardware output.
n='1D47C';s=paths[n].read_text()
for tag,end in [('pointer_bound','dst != (u16 *)32'),('counted_pointer','i != 16')]:
 t=s.replace('    s32 temp_lo;','    u16 *dst;\n    s32 temp_lo;')
 t=t.replace('for (i = 0; i < 16; i++)','for (i = 0, dst = (u16 *)0; '+end+'; i++, dst++)').replace('((u16 *)0)[i]','*dst')
 test(n,tag,t)
test(n,'byte_selector',s.replace('void func_8001D47C(s32 arg0)','void func_8001D47C(u8 arg0)'))
# Command blocks: cursor update after stores versus macro-style postincrement.
for n in ['131A4','253D0']:
 s=paths[n].read_text()
 t=re.sub(r'(\w+) = \(\*arg0\)\+\+;',r'\1 = *arg0;\n    *arg0 += 1;',s)
 test(n,'separate_cursor',t)
 # Reverse only independent word stores inside each command.
 t=re.sub(r'(\w+)->(command|w0) = ([^;]+);\s*\1->(value|w1) = ([^;]+);',r'\1->\4 = \5; \1->\2 = \3;',s)
 test(n,'value_first',t)
# RLE row cursor avoids repeated row multiplication and uses a countdown.
n='30440';s=paths[n].read_text()
t=s.replace('out[y*stride + ((x+j)^swap)]','out[((x+j)^swap)]').replace('out[y*stride + (x^swap)]','out[(x^swap)]').replace('out[y*stride+x]','out[x]').replace('        while (x < stride) { out[(x^swap)] = 0; x++; }','        while (x < stride) { out[(x^swap)] = 0; x++; }\n        out += stride;')
test(n,'row_cursor',t)
test(n,'run_countdown',s.replace('for (j = 0; j < n; j++) out[y*stride + ((x+j)^swap)] = run & 0xF0;\n            x += n;','do { out[y*stride + (x^swap)] = run & 0xF0; x++; } while (--n);'))
test(n,'equal_run',s.replace('j < n','j != n'))
# Audio config: aligned record copying and sequence entry pointer traversal.
n='2A4F0';s=paths[n].read_text()
test(n,'shared_config',s.replace('secondary.voices=44; secondary.events=50; secondary.channels=16; secondary.heap=D_80066C30; secondary.init=0; secondary.osc=0; secondary.oscUpdate=0;','secondary = music;'))
test(n,'sequence_cursor',s.replace('s32 settings[3],size,i,length;','T024SeqEntry *entry; s32 settings[3],size,i,length;').replace('for(i=0;i<48;i++) { length=D_80066C28->entries[i].length&0xFFFF;','for(i=0,entry=D_80066C28->entries;i<48;i++,entry++) { length=entry->length&0xFFFF;'))
test(n,'signed_rom_size',s.replace('size=D_907580-D_8F9FA0','size=(s32)D_907580-(s32)D_8F9FA0').replace('size=D_9B9AD0-D_9AF4B0','size=(s32)D_9B9AD0-(s32)D_9AF4B0'))
# Float state: use direct indexed lvalues instead of saved pointer locals.
n='1AD04';s=paths[n].read_text()
t=s.replace('    temp_v0 = &D_8004A800[temp_t8];','').replace('*temp_v0','D_8004A800[sp2C]')
# repair substitutions of temp_v0_2/3 declarations: only exact token lvalues above.
t=s.replace('f32 D_8004A800[sp2C]_2;','f32 *temp_v0_2;').replace('f32 D_8004A800[sp2C]_3;','f32 *temp_v0_3;').replace('f32 D_8004A800[sp2C];','f32 *temp_v0;').replace('D_8004A800[sp2C]_2','*temp_v0_2').replace('D_8004A800[sp2C]_3','*temp_v0_3')
test(n,'direct_depth',t)
test(n,'wide_indices',s.replace('s32 sp2C;','u32 sp2C;').replace('s32 sp28;','u32 sp28;'))
(ROOT/'results.json').write_text(json.dumps(rows,indent=2))
