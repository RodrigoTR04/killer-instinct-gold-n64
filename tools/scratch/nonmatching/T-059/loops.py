from attempts import *
n='30440';s=paths[n].read_text()
for name in ['width','height','stride','n','j','y','x']:
 for typ in ['u16','s16','u32']:
  test(n,name+'_'+typ,s.replace('s32 '+name,typ+' '+name))
# Pixel run index is intentionally a signed count despite byte input.
t=s.replace('    u8 *out = D_80069F70 + index * 0x120;','').replace('out[','(D_80069F70 + index * 0x120)[')
test(n,'output_expression',t)
u=t.replace('u8 *source = image + 8;','s32 source = 8;').replace('u8 run = *source++;','s32 run = image[source++];')
test(n,'offset_source',u)
# Palette original advances both byte cursors and has runtime divide by constant.
n='1D47C';s=paths[n].read_text()
t=s.replace('    s32 temp_lo;','    u16 *dst;\n    s32 temp_lo;').replace('for (i = 0; i < 16; i++)','for (dst = (u16 *)0; dst != (u16 *)32; dst++, var_v0++)').replace('((u16 *)0)[i]','*dst').replace('var_v0[i]','*var_v0')
test(n,'both_cursors',t)
for typ in ['u16','s16','u32']:
 test(n,'pixel_'+typ,t.replace('s32 pixel',typ+' pixel'))
# Match original 4-way color palette loop via byte index instead of element index.
u=s.replace('for (i = 0; i < 16; i++)','for (i = 0; i != 32; i += 2)').replace('((u16 *)0)[i]','*(u16 *)i').replace('var_v0[i]','*(u16 *)((u8 *)var_v0 + i)')
test(n,'byte_offset',u)
(ROOT/'loop-results.json').write_text(json.dumps(rows,indent=2))
