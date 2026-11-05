#!/usr/bin/env python3
"""BB7B4: rebuild the two play blocks with post-increment index, and inline the
(arg0+1)&0xFF expression so no stack slot is reserved for it."""
from pathlib import Path

BASE = Path(__file__).resolve().parent / 'best_bb7b4_195.c'
src = BASE.read_text()

# 1. post-increment counter inside the sound index (block A)
src = src.replace(
    """            temp_a1 = D_801F2EB8[D_80127CE8[D_802C8D0D][0]].sound;
            D_802C8D0D += 1;
            func_8002F6F4(D_80066C40, temp_a1, D_8004A258);""",
    """            func_8002F6F4(D_80066C40, D_801F2EB8[D_80127CE8[D_802C8D0D++][0]].sound, D_8004A258);""", 1)

# 2. post-increment counter inside the sound index (block B)
src = src.replace(
    """            temp_a1_2 = D_801F2EB8[D_80127CF3[D_802C8D0E]].sound;
            D_802C8D0E += 1;
            func_8002F6F4(D_80066C40, temp_a1_2, D_8004A25C);""",
    """            func_8002F6F4(D_80066C40, D_801F2EB8[D_80127CF3[D_802C8D0E++]].sound, D_8004A25C);""", 1)

# 3. drop the now-unused s16 temps
src = src.replace("""    s16 temp_a1;
    s16 temp_a1_2;
    s32 temp_t7;""", """    s32 temp_t7;""", 1)

# 4. inline (arg0 + 1) & 0xFF instead of the var_a2 local
src = src.replace("""    u8 var_a2;

""", "", 1)
src = src.replace("    var_a2 = (arg0 + 1) & 0xFF;\n", "", 1)
src = src.replace("var_a2", "((arg0 + 1) & 0xFF)")

# 5. the else arm's duplicated conditions read the same expression
src = src.replace(
    """        var_a1 = var_v1;
        if ((var_v1 & 1) && (((arg0 + 1) & 0xFF) == 1) && (D_802C8CE0 & ((arg0 + 1) & 0xFF)) && !(D_802C8D0D & 1) && (func_8002F6DC(*(s32 *) D_8004A258) == 0)) {""",
    """        var_a1 = var_v1;
        if ((var_v1 & 1) && (((arg0 + 1) & 0xFF) == 1) && (D_802C8CE0 & ((arg0 + 1) & 0xFF)) && !(D_802C8D0D & 1) && (func_8002F6DC(*(s32 *) D_8004A258) == 0)) {""", 1)

Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-fda05941/tools/scratch/nonmatching/T-170/v_inc.c').write_text(src)
print('written')
