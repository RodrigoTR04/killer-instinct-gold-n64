from attempts import *
n='1AD04';s=paths[n].read_text()
for name in ['sp2C','sp28']:
 test(n,name+'_unsigned',s.replace('s32 '+name+';','u32 '+name+';'))
t=s.replace('    temp_t0 = temp_t8 * 4;','').replace('    s32 temp_t0;','').replace('    f32 *sp18;','').replace('        sp18 = temp_a3;','').replace('sp18','temp_a3')
test(n,'single_rotation_pointer',t)
# Typed channel values preserve original 16-bit sum/reload, signed clamping.
n='1BB64';s=paths[n].read_text()
for typ in ['s16','u16','s32']:
 test(n,'channels_'+typ,s.replace('s32 brightness, r,g,b;','s32 brightness; '+typ+' r,g,b;'))
# Resource pointers can be expressed at the actual individual slot bases.
for n,ty in [('24714','T032Resource714'),('241BC','T032Resource1BC')]:
 s=paths[n].read_text();u=s
 for off in set(re.findall(r'->slot([0-9A-F]+)',s)):
  u=re.sub(r'\b\w+->slot'+off+r'\b', '((u8 **)(D_8004D278 + 0x'+off+'))[arg0 * 2]',u)
 test(n,'direct_slot_addresses',u)
# Match natural command sequence with one reusable cursor rather than many artificial temporaries.
n='253D0';s=paths[n].read_text();t=re.sub(r'    T032Gfx253 \*temp_v0_\d+;\n','',s);t=re.sub(r'\btemp_v0_\d+\b','temp_v0',t)
test(n,'single_command_cursor',t)
# Callback loop: use byte table pointer while preserving reload after each draw.
n='131A4';s=paths[n].read_text();t=s.replace('    s32 part, i;','    s32 part, i; s8 *parts;').replace('    i = 0;','    parts = &D_8004A688 + part;\n    i = 0;').replace('(&D_8004A688)[i * 7 + part]','parts[i * 7]')
test(n,'part_cursor',t)
(ROOT/'final-results.json').write_text(json.dumps(rows,indent=2))
