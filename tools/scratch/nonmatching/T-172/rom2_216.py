"""rom_single with different declaration placements for func_800216D4."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_800216D4.c').read()
ROM_SINGLE = BASE.replace('''    } else {
        start = D_80045E50[bank].start;
        end = D_80045E50[bank].end;
    }''', '''    } else {
        rom = &D_80045E50[bank];
        start = rom->start;
        end = rom->end;
    }''').replace('''    rom = &D_80045E50[bank];
    scan = start;''', '''    scan = start;''')

v = {'rom_single': ROM_SINGLE}

# declare rom as the last pointer
v['rom_last'] = ROM_SINGLE.replace(
    '    T032RomEntry *rom;\n', '').replace(
    '    u16 id, i, alternate = 0;\n', '    u16 id, i, alternate = 0;\n    T032RomEntry *rom;\n')

# declare rom after the entry pointer
v['rom_after_entry'] = ROM_SINGLE.replace(
    '''    T032RomEntry *rom;
    T172Cache *entry;''', '''    T172Cache *entry;
    T032RomEntry *rom;''')

# rom as the first local
v['rom_first'] = ROM_SINGLE.replace(
    '''    u8 *start, *end, *scan, *header, *p;
    T032RomEntry *rom;''', '''    T032RomEntry *rom;
    u8 *start, *end, *scan, *header, *p;''')
detail.run('func_800216D4', v, jobs=4)
