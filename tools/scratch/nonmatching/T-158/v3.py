BASE = 'tools/scratch/nonmatching/T-158/w/nat1.c'
E = '    D_802C8C64[arg1->index * 2] = rotation;\n'
V = [
 ('base', []),
 ('b', [(E, '    *(f32 *)((u8 *)D_802C8C64 + arg1->index * 8) = rotation;\n')]),
 ('c', [(E, '    index = arg1->index;\n    D_802C8C64[index * 2] = rotation;\n'), ('    f32 next;', '    s32 index;\n    f32 next;')]),
 ('d', [(E, '    D_802C8C64[arg1->index << 1] = rotation;\n')]),
 ('e', [(E, '    D_802C8C64[2 * arg1->index] = rotation;\n')]),
]
