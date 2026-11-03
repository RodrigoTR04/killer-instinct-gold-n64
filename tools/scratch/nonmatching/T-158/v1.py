BASE = 'tools/scratch/nonmatching/T-158/w/5dcc_base.c'
V = [
 ('base', []),
 ('z_first', [('    record += index;\n    height = record->right;\n    z = -10.0f;\n', '    z = -10.0f;\n    record += index;\n    height = record->right;\n')]),
 ('z_mid', [('    record += index;\n    height = record->right;\n    z = -10.0f;\n', '    record += index;\n    z = -10.0f;\n    height = record->right;\n')]),
 ('z_before_rot', [('    z = -10.0f;\n    rotation = *(f32', '    rotation = *(f32')  ,('    record += index;\n', '    z = -10.0f;\n    record += index;\n')]),
 ('idx_first', [('    record->right = (s32)height;\n    index = arg1->index;\n', '    index = arg1->index;\n    record->right = (s32)height;\n')]),
 ('recidx', [('    record += index;\n    height = record->right;\n', '    height = record[index].right;\n')]),
]
