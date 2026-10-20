from attempts import *
rows=[]
def test(n,tag,s):
 r=probe(s,'func_800'+n);rows.append({'function':'func_800'+n,'tag':tag,**r});(ROOT/('func_800'+n+'-'+tag+'.c')).write_text(s);print(n,tag,r.get('words',r.get('error','')[:80]),r.get('bytes'))
s=(ROOT/'func_80016910-inline_sine_result.c').read_text()
for lit in ['(f32)256','(f32)0x100','(f32)(s32)256']:
 test('16910','inline_divisor_'+str(len(rows)),s.replace('256.0f',lit))
s=(ROOT/'func_8001B620-direct_state_dispatch.c').read_text()
# Unused var_v0 and explicit address local allocation can affect IDO's fixed local area.
test('1B620','remove_dead_state',s.replace('    s32 var_v0;\n',''))
test('1B620','short_indices',s.replace('    s32 var_v0;\n','').replace('s32 sp24;','u16 sp24;').replace('s32 sp20;','u16 sp20;'))
# Keep the stage address as an expression; it remains live through calls naturally.
t=s.replace('    u8 *sp18;\n','').replace('    s32 var_v0;\n','').replace('    sp18 = (u8 *)D_8004A4C0 + (arg0 * 0xC);\n','').replace('sp18','((u8 *)D_8004A4C0 + arg0 * 12)')
test('1B620','stage_address_expression',t)
# A scoped declaration allows the compiler to reuse the state-dispatch local's slot.
test('1B620','scoped_stage_pointer',s.replace('    s32 var_v0;\n','').replace('    s32 sp24;\n    s32 sp20;\n','').replace('    sp24 =','    s32 sp24 =',1).replace('    sp20 =','    s32 sp20 =',1))
(ROOT/'finish_near.json').write_text(json.dumps(rows,indent=2)+'\n')
