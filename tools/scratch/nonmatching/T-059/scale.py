from attempts import *
n='1E0B4';s=(ROOT/(n+'-wide_half_scale.c')).read_text()
t=s.replace('                        if ((s32) (*(u8 *)((u8 *)(temp_t3) + 0x21)) >= 0x80)', '                        temp_v0 = *(u8 *)(temp_t3 + 0x21);\n                        if (temp_v0 >= 0x80)')
test(n,'mirror_local',t)
# An explicitly typed command record naturally separates command words from byte actor data.
u='typedef struct { u32 w0; void *w1; } RenderCommand;\n'+t
u=u.replace('u8 *temp_v1;','RenderCommand *temp_v1;').replace('temp_v1 = *arg0;','temp_v1 = (RenderCommand *)*arg0;').replace('*arg0 = temp_v1 + 8;','*arg0 = (u8 *)(temp_v1 + 1);').replace('(*(s32 *)((u8 *)(temp_v1) + 0))','temp_v1->w0').replace('(*(u8 **)((u8 *)(temp_v1) + 4))','temp_v1->w1')
test(n,'typed_command',u)
# Initialization as for loop places induction setup with its loop, rather than command setup.
v=t.replace('    var_s0 = 0;\n','').replace('    do {','    for (var_s0 = 0; var_s0 != 2; var_s0++) {',1).replace('        var_s0 += 1;\n    } while (var_s0 != 2);','    }')
test(n,'for_actors',v)
# Keep one actor index expression throughout; compiler can still reuse it after callback.
w=t.replace('    s32 temp_v1_2;\n','').replace('                    temp_v1_2 = var_s0 + 1;\n','').replace('temp_v1_2','(var_s0 + 1)')
test(n,'actor_expression',w)
(ROOT/'scale-results.json').write_text(json.dumps(rows,indent=2))
