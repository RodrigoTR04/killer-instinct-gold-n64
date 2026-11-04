BASE = 'tools/scratch/nonmatching/T-158/w/bb60_base.c'
L1 = '    for (i = 0; i < 0x1000; i++) D_802C8D20[i] = 128;\n    for (i = 0; i < 64; i++) D_802C9F20[i] = 124;\n'
V = [
 ('base', []),
 ('ptr_for', [(L1, '    for (fill = D_802C8D20; fill < (u8 *)D_802C9D20; fill++) *fill = 128;\n    for (fill = D_802C9F20; fill < D_802C9F60; fill++) *fill = 124;\n'), ('    s32 i, red, green;', '    s32 i, red, green;\n    u8 *fill;')]),
 ('ptr_do', [(L1, '    fill = D_802C8D20;\n    do { *fill++ = 128; } while (fill < (u8 *)D_802C9D20);\n    fill = D_802C9F20;\n    do { *fill++ = 124; } while (fill < D_802C9F60);\n'), ('    s32 i, red, green;', '    s32 i, red, green;\n    u8 *fill;')]),
 ('ptr_first_only', [('    for (i = 0; i < 0x1000; i++) D_802C8D20[i] = 128;\n', '    for (fill = D_802C8D20; fill < (u8 *)D_802C9D20; fill++) *fill = 128;\n'), ('    s32 i, red, green;', '    s32 i, red, green;\n    u8 *fill;')]),
 ('ptr_second_only', [('    for (i = 0; i < 64; i++) D_802C9F20[i] = 124;\n', '    for (fill = D_802C9F20; fill < D_802C9F60; fill++) *fill = 124;\n'), ('    s32 i, red, green;', '    s32 i, red, green;\n    u8 *fill;')]),
]
