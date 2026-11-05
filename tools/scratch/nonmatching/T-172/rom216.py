"""Make `rom` the single entry pointer for func_800216D4 (target spills it at 0x54/0x58)."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_800216D4.c').read()
v = {'base': BASE}

# assign rom in the else branch, reuse it later (one variable, two assignments)
v['rom_single'] = BASE.replace('''    } else {
        start = D_80045E50[bank].start;
        end = D_80045E50[bank].end;
    }''', '''    } else {
        rom = &D_80045E50[bank];
        start = rom->start;
        end = rom->end;
    }''').replace('''    rom = &D_80045E50[bank];
    scan = start;''', '''    scan = start;''')

# rom assigned before the player test
v['rom_early'] = BASE.replace('''    if (player == 2) return 0;
    rom = &D_80045E50[bank];''', '''    rom = &D_80045E50[bank];
    if (player == 2) return 0;''')

# entry pointer used for the palette read only, palette read through a local
v['pal_local'] = BASE.replace('''    boot_dma((s32)rom->palette, (s32)(D_80063C60 + (player << 11)), 0x800);
    boot_dma((s32)(rom->palette + 0x800), (s32)(D_80064C60 + (player << 11)), 0x800);''',
    '''    palette = rom->palette;
    boot_dma((s32)palette, (s32)(D_80063C60 + (player << 11)), 0x800);
    boot_dma((s32)(palette + 0x800), (s32)(D_80064C60 + (player << 11)), 0x800);''').replace(
    '    u8 bank = kind;\n', '    u8 bank = kind;\n    u8 *palette;\n')

# combine
v['both'] = v['rom_single'].replace(
    '''    boot_dma((s32)rom->palette, (s32)(D_80063C60 + (player << 11)), 0x800);
    boot_dma((s32)(rom->palette + 0x800), (s32)(D_80064C60 + (player << 11)), 0x800);''',
    '''    palette = rom->palette;
    boot_dma((s32)palette, (s32)(D_80063C60 + (player << 11)), 0x800);
    boot_dma((s32)(palette + 0x800), (s32)(D_80064C60 + (player << 11)), 0x800);''').replace(
    '    u8 bank = kind;\n', '    u8 bank = kind;\n    u8 *palette;\n')
detail.run('func_800216D4', v, jobs=4)
