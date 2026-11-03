BASE = 'tools/scratch/nonmatching/T-158/w/nat3.c'
V = [
 ('base', []),
 ('nonext', [('    f32 next;\n',''),('        next = 8.0f;\n',''),('rotation / next','rotation / 8')]),
 ('nonext_f', [('    f32 next;\n',''),('        next = 8.0f;\n',''),('rotation / next','rotation / 8.0f')]),
 ('nonext_decl', [('    f32 next;\n','    f32 next = 8.0f;\n'),('        next = 8.0f;\n','')]),
]
