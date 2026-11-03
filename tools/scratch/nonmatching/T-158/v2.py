BASE = 'tools/scratch/nonmatching/T-158/w/5dcc_base.c'
E = '    index = arg1->index;\n    D_802C8C64[index * 2] = rotation;\n'
V = [
 ('base', []),
 ('a', [(E, '    D_802C8C64[arg1->index * 2] = rotation;\n')]),
 ('b', [(E, '    *(f32 *)((u8 *)D_802C8C64 + arg1->index * 8) = rotation;\n')]),
 ('c', [(E, '    D_802C8C64[arg1->index * 2] = rotation;\n'), ('    record->right = (s32)height;\n', '    record->right = height;\n')]),
 ('d', [('    record->right = (s32)height;\n', '    record->right = height;\n')]),
 ('e', [(E, '    index = arg1->index;\n    *(f32 *)((u8 *)D_802C8C64 + index * 8) = rotation;\n')]),
]
