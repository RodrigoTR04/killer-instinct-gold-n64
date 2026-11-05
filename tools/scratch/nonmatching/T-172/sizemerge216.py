"""Merge `loaded` into `size` for func_800216D4 (target has no `loaded = 0` store)."""
import sys

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_800216D4.c').read()
OLD = '''        size = T172_LE216(header + 4);
        if (wanted == id) {
            loaded = size + offset;
            loaded += loaded & 7;
            boot_dma((s32)start, (s32)destination, loaded);
            if (offset) memcpy(destination, header, loaded - offset);
        }'''
assert OLD in BASE

# The target keeps a per-iteration `size` in s5 and the loaded total in s1 (sp+0x5C),
# plus the rounded offset in s0 (sp+0x60). Express that without a zero-initialised var.
NEW = '''        size = T172_LE216(header + 4);
        if (wanted == id) {
            size += offset;
            size += size & 7;
            boot_dma((s32)start, (s32)destination, size);
            if (offset) memcpy(destination, header, size - offset);
        }'''
TAIL_OLD = '    return loaded - offset;\n'
assert TAIL_OLD in BASE

v = {}
v['size_merge'] = BASE.replace(OLD, NEW).replace(TAIL_OLD, '    return size - offset;\n').replace(
    '    s32 offset, size, loaded = 0;\n', '    s32 offset, size;\n')
v['size_merge_init'] = BASE.replace(OLD, NEW).replace(TAIL_OLD, '    return size - offset;\n').replace(
    '    s32 offset, size, loaded = 0;\n', '    s32 offset, size;\n').replace(
    '''    scan = start;''', '''    size = 0;
    scan = start;''')
v['loaded_sep_size'] = BASE.replace('    s32 offset, size, loaded = 0;\n',
                                    '    s32 offset;\n    s32 size;\n    s32 loaded;\n')
print(len(v), 'variants', flush=True)
detail.run('func_800216D4', v, jobs=3)
