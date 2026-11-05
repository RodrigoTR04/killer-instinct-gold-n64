"""Explore palette-local variants for func_800216D4 (target 1032 bytes)."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_800216D4.c').read()
PAL_OLD = '''    boot_dma((s32)rom->palette, (s32)(D_80063C60 + (player << 11)), 0x800);
    boot_dma((s32)(rom->palette + 0x800), (s32)(D_80064C60 + (player << 11)), 0x800);'''
PAL_NEW = '''    palette = rom->palette;
    boot_dma((s32)palette, (s32)(D_80063C60 + (player << 11)), 0x800);
    boot_dma((s32)(palette + 0x800), (s32)(D_80064C60 + (player << 11)), 0x800);'''
assert PAL_OLD in BASE

PA = BASE.replace(PAL_OLD, PAL_NEW).replace(
    '    u8 bank = kind;\n', '    u8 bank = kind;\n    u8 *palette;\n')

v = {'pal_local': PA}

# palette through the array indexing instead of rom
v['pal_idx'] = BASE.replace(PAL_OLD, '''    palette = D_80045E50[bank].palette;
    boot_dma((s32)palette, (s32)(D_80063C60 + (player << 11)), 0x800);
    boot_dma((s32)(palette + 0x800), (s32)(D_80064C60 + (player << 11)), 0x800);''').replace(
    '    u8 bank = kind;\n', '    u8 bank = kind;\n    u8 *palette;\n')

# palette declared with the other pointers (u8 *start, *end, *scan, *header, *p, *palette)
v['pal_grouped'] = BASE.replace(PAL_OLD, PAL_NEW).replace(
    '    u8 *start, *end, *scan, *header, *p;\n',
    '    u8 *start, *end, *scan, *header, *p, *palette;\n')

# palette first in the pointer list
v['pal_first'] = BASE.replace(PAL_OLD, PAL_NEW).replace(
    '    u8 *start, *end, *scan, *header, *p;\n',
    '    u8 *palette, *start, *end, *scan, *header, *p;\n')

# rom removed entirely; palette read via indexed entry
v['no_rom'] = BASE.replace(PAL_OLD, PAL_NEW).replace(
    '    T032RomEntry *rom;\n', '').replace(
    '''    rom = &D_80045E50[bank];
''', '').replace('    u8 bank = kind;\n', '    u8 bank = kind;\n    u8 *palette;\n')
detail.run('func_800216D4', v, jobs=5)
