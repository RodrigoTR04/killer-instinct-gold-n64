# T-166

Official counts are `screen.measure` on the full owning translation unit.

## func_8001272C

- Before: 86 words, 536/540 bytes (tools/scratch/nonmatching/T-033/func_8001272C.c).
- After: 3 words, 540/540 bytes.
- Lever: the real constants (21, 2731, 26, 30) and the real intermediates (`product`, `quot`, `capped`, `scaled`, `wmul`, `adj`) are named locals. Seven `s32`s before `f32 z, y, x` and three after `obj` place the floats at sp+120/124/128 and the frame at 160. `s32 fade` (the load stays `lbu`) with `if (fade >= 12) capped = 12; else capped = fade` fills both cap delay slots. `kindId == kind` and `strength = quot + strength` fix the `bne` and `addu` operand order.

Remaining words, all scheduling:

- 35 and 37: `sw s3, 16(sp)` / `sw s4, 20(sp)` around `jal func_8002BB74` are swapped. Same pointers, same slots. IDO emits the two address args right to left, so the 5th arg lands in the delay slot. The original emits them left to right (6th arg in the delay slot).
- 69: `blez` delay is `move a0, v0` instead of `nop`. The copy is dead; `multu` still uses `v0`, and the two nops between `mflo` and `div` already match.

Dead ends:

- `if (fade < 12)` speculates `addiu` before the `beql` (84 words, 544 bytes). Assigning `capped = 12` on every path before the test hoists 12 into `s1` across the call (53 words, exact size, `* 30` becomes shifts).
- `u8 fade` scores 13. A separate radius, override local, or fade pointer displaces the saved registers.
- Call line breaks, a macro, casts, pointer temps, an array, a struct, and swapped declaration order of the three floats do not flip the two stores. A micro-test shows left-to-right stores for plain integer arguments and right-to-left stores for `&local` / pointer arguments, including when those pointers already live in saved registers.
- Inlining the product, a `u32` multiply, or `/ 26` as a literal leaves the `blez` delay-slot move in place.
- `cmp.py` counts two padding nops after the function and is not the official score. The nops between `mflo` and `div` are inside the function and already match.

## func_801C17D0

- Before: 102 words, 436/448 bytes (tools/scratch/nonmatching/T-147/func_801C17D0.c).
- After: 65 words, 448/448 bytes.
- Lever: keep the character in its own `u8` for the final call and use a separate `s32 index` for the two stat rows. Test the stored `u64` as two words (`hi != 0 || lo != 0`) instead of `*out != 0`.

Dead ends:

- The original still copies `stats` from `a0` to `a2` and the character from `t0` to `v1` before `bnez`, and loads each stat into `a0`. A `u32 *` copy of `stats`, branch-local slot pointers, and a `u8` index do not produce those moves. The `s32 index` does force a copy, but the load lands in `a2` and the frame grows from 64 to 72, so the argument home of `player` moves from sp+68 to sp+76.
- `register s32 index` still uses a 72-byte frame. Declaration order of the four locals does not change the 69-word intermediate.
- `return *out != 0` is a xor/or/`sltu` of the two halves. Separate `if (hi) return 1; if (lo) return 1;` is 70 words and 456 bytes. The `||` form is the one that restores 448 bytes. The original is `bnel` with `li v0, 1` in each delay slot, plus an unreachable `li v0, 1`.
- Full-width `player` was already known to score 110/432.

## func_800191F0

- Before: 109 words, 472/492 (tools/scratch/nonmatching/T-022/func_800191F0.c).
- After: unchanged. No commit.
- The original walks `D_801D3430` four objects at a time (stride 0x100, outer step 0x400) and reloads `vx` after storing the same halfword. A 4-wide pointer loop that stores `vx` back to itself before the divide is 106 words at the exact 492 bytes. That store is only there to force the reload, so it is not kept.
- `obj->` versus `obj[0]`, flipped `==` operands, and a fresh pointer per object do not remove the opening `move v0, v1` or put 200.0f in the early-out delay slot. The first object is still addressed through the copy, and `bnel` compares the constant against the kind.

## func_8001D47C

- Before: 134 words, 744/748 (tools/scratch/nonmatching/T-022/func_8001D47C.c).
- After: unchanged. No commit.
- Ignoring register names, that draft differs by about 10 instructions: a `nop` in the `bnez D_8004EA78` delay where the original loads `D_801D3433`, a missing copy of the palette pointer (the quotient stays out of `v0`), and the zero-fill stores rotated so `sh -8` is not in the loop-branch delay.
- Nested `if (D_8004EA78 == 0) if (D_801D3433)` still leaves the `nop`. Giving the grayscale loop its own cursor and a variable divisor of 3 reaches 748 bytes but scores 162. Writing the four stores out by hand fully unrolls the zero and copy loops (860 bytes).

## func_8001346C

- Before: 166 words, declarations-only (the full TU did not compile).
- After: 158 words, 680/704, full TU.
- Lever: `D_8004AC98` / `D_8004ACB0` are the translation unit's `RGB14` arrays, so each row is indexed once. `func_8001BDE0` is declared `u8 **` to match its definition. The second parameter stays `u8` because that is the prototype `func_800131A4` was matched with; changing it to `s32` does not change that caller, but the `s32` body scores 166/676.
- Moving the `RGB14` typedef above this function changes no other function in `main_2FF0.c` (72 symbols compared).

Dead ends:

- An explicit `palette * 3` byte offset on the `RGB14` arrays compiles to the same 158/680 as `&D_8004AC98[palette]`. The two `* 3` scales are still one.
- The `u8` parameter is saved and reloaded with `lbu` from its stack home. The original uses `a1` directly and has an 0x58 frame; this draft has a 104-byte frame.
- Field-by-field copies and a shared `* 3` were already known not to help.
