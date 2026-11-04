BASE = 'tools/scratch/nonmatching/T-158/w/bb60_base.c'
V = [('base', [])]
for ty in ['u8', 's8', 's16', 'u16', 'u32', 's32']:
    V.append(('red_'+ty, [('    s32 i, red, green;', '    s32 i, green;\n    %s red;' % ty)]))
    V.append(('green_'+ty, [('    s32 i, red, green;', '    s32 i, red;\n    %s green;' % ty)]))
    V.append(('both_'+ty, [('    s32 i, red, green;', '    s32 i;\n    %s red, green;' % ty)]))
for ty in ['u16', 's16', 'u32']:
    V.append(('i_'+ty, [('    s32 i, red, green;', '    %s i;\n    s32 red, green;' % ty)]))
