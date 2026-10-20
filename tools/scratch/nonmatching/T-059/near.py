from attempts import *
n='1E0B4';s=paths[n].read_text().replace('extern u8 D_8004CEE8;','extern s16 D_8004CEE8;').replace('*(&D_8004CEE8 + (D_8004EA78 * 0x1C))','*(s16 *)((u8 *)&D_8004CEE8 + D_8004EA78 * 0x1C)')
test(n,'halfword_kind',s)
t=s.replace('var_t1 = (u16) ((s32) var_t1 / 2);','var_t1 = (s32) var_t1 / 2;')
test(n,'wide_half_scale',t)
# Order of first Gfx stores follows idiomatic macro argument evaluation.
test(n,'gfx_after_counter',t.replace('    var_s0 = 0;','').replace('    do {','    var_s0 = 0;\n    do {',1))
# Color expression OR associativity matches blue-red-green original order.
n='1BB64';s=paths[n].read_text()
t=s.replace('(colors[0] << 24) | ((colors[1] & 255) << 16) | ((colors[2] & 255) << 8)','((colors[2] & 255) << 8) | (colors[0] << 24) | ((colors[1] & 255) << 16)')
test(n,'blue_red_green',t)
test(n,'wide_dispatch',t.replace('u8 amount,mode;','s32 amount,mode;'))
test(n,'explicit_end',t.replace('extern u8 D_8004AA28','extern u8 D_8004AC95;\nextern u8 D_8004AA28').replace('&D_8004AC92 + 3','&D_8004AC95'))
# Initialization: unsigned byte stores are appropriate for values 0x80 and 0x40.
n='18F20';s=paths[n].read_text()
for region in ['order','tail','colors']:
 lines=[]
 for l in s.splitlines():
  if (region=='order' and 'D_8004A5E0)' in l) or (region=='tail' and ('D_80061520)' in l or 'D_80061CB8)' in l)) or (region=='colors' and 'D_80061CB8)' in l):l=l.replace('(*(s8 *)','(*(u8 *)')
  lines.append(l)
 test(n,region+'_unsigned','\n'.join(lines)+'\n')
# Audio configs: use standard SDK layout (pointer to params follows type padding).
n='2A4F0';s=(ROOT/(n+'-sequence_cursor.c')).read_text()
# Original sequence traversal starts at file header and advances by record size.
test(n,'header_cursor',s.replace('entry=D_80066C28->entries','entry=(T024SeqEntry *)D_80066C28').replace('length=entry->length','length=*(s32 *)((u8 *)entry+8)'))
# Destination pointer makes original two-byte cursor independent of source indexing.
test(n,'two_cursors',s.replace('T024SeqEntry *entry;','u16 *dest; T024SeqEntry *entry;').replace('i=0,entry=','i=0,dest=D_800669D0,entry=').replace('i++,entry++','i++,entry++,dest++').replace('D_800669D0[i]','*dest'))
(ROOT/'near-results.json').write_text(json.dumps(rows,indent=2))
