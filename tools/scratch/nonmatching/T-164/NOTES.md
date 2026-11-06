# T-164

Official counts are full-TU positional words from `tools/permuter/screen.py` unless noted.

| Function | Before | After | Bytes | Lever |
|---|---:|---:|---|---|
| func_801B01EC | 191 | 120 | 820 / 820 | The sample record is a 4-byte struct, so the index scales by 4, and the elapsed tick is written back through `arg3`. Colour still lives in a saved register (`s1`) instead of the stack slot at 0x64; declaration order only reached 120. |

None of the other pool functions got a lower official count. Attempts that scored the same or worse were not kept:

- func_801B0CDC stayed at 155 / 1332. Splitting the faded tick out before the `arg3 < 0x28` test does not fill the delay slot, and the frame stays 0x18 short.
- func_801AF68C: `p != D_802A1A60` scored 232 / 944 (was 231 / 940). A clean rewrite scored 236. Full TU still dies on `s32 D_802A1A60[]` after the function.
- func_80024CE0: reassociating the big-endian block length scored 392 and 395 (was 390). Full TU dies on `func_800268C0`'s pointer argument versus the `(u8 *, s32, s32, s32)` definition.
- func_801C317C: early returns plus `D_80285574[index]` scored 232 / 920 (was 215 / 932). The `u8 ***` extern conflicts with the later `s32 D_80285574`.
- func_8001346C stayed at 166 / 676. Adding case 6 does not change the jump table. Indexing the colour tables as 3-byte structs still shares one `*3` (the original computes it twice) and stays 166; copying the fields one by one scored 174 / 692. Full TU dies on the `u8` prototype and on `u8 D_8004AC98[]` versus the later `RGB14` extern.
- func_801B01EC else-if that duplicates `func_8002F6F4` scored 172 / 876. Swapping the `D_801D2EB0` / `D_801D2EB4` stores scored 129. All 720 orders of the six scalars, with the lookat array kept first, scored 120–122.
- func_8002E724 (658 words, 2728 / 2832) and func_801BC1B0 (583, 2480 / 2496) differ in many small blocks, not one missing region. func_801C1C34 has the same 12 calls and 4 branches and is 5 instructions short (242 words).
- func_80021B6C still does not compile in the full TU. `D_8004AC8A` is `s8` in `main_D3F0.c` and `u8` in the draft; matching that exposes further conflicts (`D_8004AC89`, `D_801D3430`, `D_8004D278`, `func_8001EC74`) plus an undefined `scale` member. The last time it compiled it was about 1726 words and 108 bytes over.
- func_801C08F8, func_8001178C, func_80019880 and func_801B6E4C were left at their declarations scores (561, 556, 1297, 1417). Full TU fails on a conflicting extern or a bad operand, and the size gaps are tens to hundreds of bytes spread through the function.
