"""Combine the palette local with other redundant-reload removals in func_800216D4.

pal_local already removed one redundant reload (1040 -> 1036 = one instruction).
The `loaded = 0` store is a second candidate (target has no such store).
"""
import sys

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_800216D4.c').read()
PAL_OLD = '''    boot_dma((s32)rom->palette, (s32)(D_80063C60 + (player << 11)), 0x800);
    boot_dma((s32)(rom->palette + 0x800), (s32)(D_80064C60 + (player << 11)), 0x800);'''
PAL_NEW = '''    palette = rom->palette;
    boot_dma((s32)palette, (s32)(D_80063C60 + (player << 11)), 0x800);
    boot_dma((s32)(palette + 0x800), (s32)(D_80064C60 + (player << 11)), 0x800);'''
assert PAL_OLD in BASE

PAL = BASE.replace(PAL_OLD, PAL_NEW).replace(
    '    u8 bank = kind;\n', '    u8 bank = kind;\n    u8 *palette;\n')

v = {'pal236': PAL}

# palette + no zero-init on loaded
v['pal_noload'] = PAL.replace('    s32 offset, size, loaded = 0;\n',
                              '    s32 offset, size, loaded;\n')

# palette + rom read once into a local for the entry pointer too
v['pal_romlocal'] = PAL.replace(
    '    rom = &D_80045E50[bank];\n', '    rom = &D_80045E50[bank];\n')

# palette local declared with the other u8 pointers
v['pal_grouped'] = BASE.replace(PAL_OLD, PAL_NEW).replace(
    '    u8 *start, *end, *scan, *header, *p;\n',
    '    u8 *start, *end, *scan, *header, *p, *palette;\n')

print(len(v), 'variants', flush=True)
detail.run('func_800216D4', v, jobs=4)
