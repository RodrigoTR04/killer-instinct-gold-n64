"""Separate declaration statements for func_800216D4 (the lever that helped 2E150)."""
import sys

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_800216D4.c').read()
OLD = '''    u8 *start, *end, *scan, *header, *p;
    T032RomEntry *rom;
    T172Cache *entry;
    s32 offset, size, loaded = 0;
    u16 id, i, alternate = 0;
    u8 bank = kind;
'''
assert OLD in BASE

v = {'base226': BASE}
v['sep'] = BASE.replace(OLD, '''    u8 *start;
    u8 *end;
    u8 *scan;
    u8 *header;
    u8 *p;
    T032RomEntry *rom;
    T172Cache *entry;
    s32 offset;
    s32 size;
    s32 loaded = 0;
    u16 id;
    u16 i;
    u16 alternate = 0;
    u8 bank = kind;
''')
v['sep_bank_first'] = BASE.replace(OLD, '''    u8 bank = kind;
    u8 *start;
    u8 *end;
    u8 *scan;
    u8 *header;
    u8 *p;
    T032RomEntry *rom;
    T172Cache *entry;
    s32 offset;
    s32 size;
    s32 loaded = 0;
    u16 id;
    u16 i;
    u16 alternate = 0;
''')
print(len(v), 'variants', flush=True)
detail.run('func_800216D4', v, jobs=3)
