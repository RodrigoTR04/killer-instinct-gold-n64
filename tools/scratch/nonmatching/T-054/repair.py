from attempts import *
rows=[]
for n in ['1AD04','1B134']:
 s=(ROOT/('func_800'+n+'-best.c')).read_text()
 s=re.sub(r'func_8001B620\([^;]+\);','func_8001B620(arg0, arg1);',s)
 # Remove compiler-managed save artifacts. C's ordinary locals carry the values.
 s=re.sub(r'^\s*(?:sp20|sp1C|sp24) = [^;]+;', '',s,flags=re.M)
 if n=='1AD04':
  s=s.replace('    f32 *sp20;                                      /* compiler-managed */','').replace('    s32 sp24;','').replace('    f32 *sp1C;','')
 else:
  s=s.replace('    f32 *sp20;','').replace('    f32 *sp1C;','')
 s=s.replace('temp_v0 + ((u8 *)D_8004A800)','&D_8004A800[temp_t8]').replace('temp_v0 + (u8 *)&D_8004A7A0','&(&D_8004A7A0)[temp_t8]').replace('temp_v0 + ((u8 *)D_8004A8C0)','&D_8004A8C0[temp_t8]').replace('(sp28 * 4) + (u8 *)&D_8004A7A0','&(&D_8004A7A0)[sp28]').replace('(sp28 * 4) + ((u8 *)D_8004A8C0)','&D_8004A8C0[sp28]')
 r=probe(s,'func_800'+n);rows.append({'function':'func_800'+n,**r});(ROOT/('func_800'+n+'-repaired.c')).write_text(s);print(n,r.get('words'),r.get('bytes'),r.get('error'))
(ROOT/'repair.json').write_text(json.dumps(rows,indent=2)+'\n')
