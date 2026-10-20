from attempts import *
rows=[]
def test(n,tag,s):
 r=probe(s,'func_800'+n);rows.append({'function':'func_800'+n,'tag':tag,**r});(ROOT/('func_800'+n+'-'+tag+'.c')).write_text(s);print(n,tag,r.get('words',r.get('error','')[:80]),r.get('bytes'),flush=True)
s=(ROOT/'func_8001B620-literal-all_literals.c').read_text()
for tag,t in [('scoped switch local',s.replace('    s32 var_v0;','').replace('    var_v0 = D_8004ACF0;','    { s32 var_v0 = D_8004ACF0;').replace('    D_8004ACE0 =','    }\n    D_8004ACE0 =')),('direct state dispatch',s.replace('    var_v0 = D_8004ACF0;','').replace('(var_v0 == 1)','(D_8004ACF0 == 1)').replace('        var_v0 = 2;','').replace('switch (var_v0)','switch (D_8004ACF0)')),('typed stage pointer',s.replace('u8 *sp18;','struct T054NearPart {void *display; s16 flags,pad; s32 transform;} *sp18;').replace('sp18 = (u8 *)D_8004A4C0 + (arg0 * 0xC);','sp18 = (struct T054NearPart *)D_8004A4C0 + arg0;').replace('(*(s32 *)((u8 *)(sp18) + 8))','sp18->transform').replace('(*(s16 *)((u8 *)(sp18) + 4))','sp18->flags')),('index shorts',s.replace('s32 sp24;','s16 sp24;').replace('s32 sp20;','s16 sp20;'))]:test('1B620',tag.replace(' ','_'),t)
s=(ROOT/'func_80016910-literal-D_80048858.c').read_text()
for literal in ['256.0','(f32)256','(f64)256.0f']:
 test('16910','divide_'+literal.replace('.','_').replace('(','').replace(')',''),s.replace('/ 256.0f','/ '+literal))
# Force a float quotient before the subsequent multiply, as original scheduling suggests.
for tag,t in [('inline sine result',s.replace('    x = sinf','    D_80061CC8[0] = sinf').replace(' * D_8004A988;\n    D_80061CC8[1] = 0.0f;\n    D_80061CC8[0] = x / 256.0f;',' * D_8004A988 / 256.0f;\n    D_80061CC8[1] = 0.0f;')),('double divisor',s.replace('x / 256.0f','(f32)((f64)x / 256.0)').replace('D_8004A988 / 256.0f','D_8004A988 / 256.0'))]:test('16910',tag.replace(' ','_'),t)
(ROOT/'near.json').write_text(json.dumps(rows,indent=2)+'\n')
