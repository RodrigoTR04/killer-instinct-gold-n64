"""Parameter-masking variants for func_800216D4 (target masks kind, player, wanted)."""
import re
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_800216D4.c').read()
v = {'base': BASE}

# target: andi s4, a0, 0xFF  -> player is masked into a u8 local
v['player_local'] = BASE.replace(
    '    u8 bank = kind;\n',
    '    u8 bank = kind;\n    u8 who = player;\n'
).replace('[player]', '[who]').replace('(player << 11)', '(who << 11)').replace(
    'if (player == 2) return 0;', 'if (who == 2) return 0;')

# order: assign the masked wanted before the bank test
v['wanted_first'] = BASE.replace('''    wanted &= 65535;
    if (bank >= 128) {''', '''    if (bank >= 128) {''').replace(
    '''    if (player == 2) return 0;''', '''    if (player == 2) return 0;''')
# keep wanted masking but as a separate statement after bank
v['mask_late'] = BASE.replace('''    wanted &= 65535;
    if (bank >= 128) {''', '''    if (bank >= 128) {''').replace(
    '    if (player == 2) return 0;', '    wanted &= 65535;\n    if (player == 2) return 0;')

# declare the masked args as the only u8s, wanted as u16
v['u16_wanted'] = BASE.replace('    wanted &= 65535;\n', '    wanted = (u16)wanted;\n')

# both masks as casts
v['casts'] = BASE.replace('    u8 bank = kind;\n\n    wanted &= 65535;\n',
                          '    u8 bank = (u8)kind;\n    u8 who = (u8)player;\n\n    wanted = (u16)wanted;\n').replace(
    '[player]', '[who]').replace('(player << 11)', '(who << 11)').replace(
    'if (player == 2) return 0;', 'if (who == 2) return 0;')

detail.run('func_800216D4', v, jobs=5)
