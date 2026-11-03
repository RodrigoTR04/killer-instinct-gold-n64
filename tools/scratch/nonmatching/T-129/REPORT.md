# T-129 — grok-2

**0 MATCHED, 0 improved drafts retained. 0 B / 2,030 B target.**

Small T-026 cluster plus the 129–160-word band. Production `src/` is unchanged. No symbol, yaml or hint edits.

## Per-function

Words are relocation-masked differing instruction words including size gaps. Incoming numbers are from `screen-2026-10-21.md` unless a later report improved them.

### Small T-026 cluster (structure first)

| Function | Orig B | Incoming words | Result | Diagnosis |
|---|---:|---:|---|---|
| func_80032738 | 20 | 10 | handwritten, not attempted as C | `daddiu`/`sd` seed+1 into `D_80048420`, delay-slot `addiu a0, zero, 0`. Native 64-bit; `-O2 -mips2` C emits word pairs. Trailing nop is TU padding. |
| func_800326F0 | 72 | 69 | handwritten, not attempted as C | `ld`/`dsll32`/`dsrl`/`dsra32` xorshift of the same seed. Same 64-bit ABI. |
| func_80032750 | 60 | 15 | handwritten register ABI | Each global address is `lui`+`addiu` into `t0`–`t4`; `t1=8` stored twice. IDO uses `lui`/`sw` with lo in the store and different temps. |
| func_8003278C | 92 | 26 | handwritten | Splat already labels it handwritten; trapping `addi t1, t1, -1`. |
| func_80031050 | 112 | 30 | skipped | Continuation into `func_80031188` with private live registers. |
| func_80032600 | 112 | 37 | skipped | Decoder state in `t4`–`t8`/`fp`, not C arguments. |
| func_80032670 | 116 | 45 | skipped | Same private decoder ABI. |
| func_80032504 | 240 | 60 | skipped | Computed jump into a store tail, `sdl`/`swl`, XOR-4 addressing. |

### Exact-size overlay drafts (highest bytes)

| Function | Orig B | Incoming → this pass | Result |
|---|---:|---|---|
| func_801B0520 | 328 | 22 → 22 | Unchanged. Full-TU C with `frame` declared first still emits `sll v1, a3, 1` at +04 (target `v0`). `&D_802956F8` in a local does not become `a1` with `addiu`+`lw 0(a1)`; IDO uses `lui`/`lw`. Inverting `>= 16` vs `< 16` grew the score (60 words, 324 B). Nested `y` does not move the first temp into `v0`. Residual is the same T-104/T-116 register/scheduling set. No rodata. |
| func_801B1210 | 284 | 28 → 28 | Unchanged. Joining the first command as `w1` then `w0` (matching the original stores) scored 31 in full TU; reverted. String pool `D_80292814`–`D_80292870` is `force_migration`/`function_owner:func_801B1210`; late `D_80292918` lives in this `.s`. Text match alone is not enough. |
| func_801B446C | 292 | 28 → 28 | Unchanged. Dropping the `addiu t0, &D_802C8CE0` and using `lui v0`/`lbu` shrinks 4 B and raises the score (~40). Target keeps `&D_802C8CE0` in `t0` as in T-074. |
| func_801C3758 | 564 | 30 → 30 | Unchanged. Address-taken `vtxIndex=&D_80290D88` / `vtxBase=&D_802D38E0` made IDO reload via `lui`/`lw` of the values and blew the size (688 B, 166 words). T-125 body (pointer `D_802D38E0`, masked animation, `s8` K&R `arg2`) remains best: exact 564 B. Original keeps those two addresses in `t1`/`t0` and zeros both `v0` and `v1` when the wrapped frame is `>= 64`. `a3=arg0` copy sits in the compare delay slot so `a0` can hold the UV row. |
| func_801C2F5C | 544 | 47 → 47 | Unchanged. Original prologue is `a3=&D_802D38C8; lbu v1,0(a3)` **before** `addiu sp`, then `a2=&D_802854D0`. After the scale store it reloads `*a3` for the X layout. Forcing that in C either kept `lui`/`lbu` into `v0` (110 words, still 544 B, 0x68 frame vs 0x60) or grew the function. T-125 body remains best. Sprite stride 0x8C and layout stride 16 are already correct. |
| func_8001AA90 | 496 | 60 → 60 | Unchanged. C body is 488 B; inventory 496 includes `jr ra; nop` at `0x8001AC78` (`alabel D_8001AC78`) before `func_8001AC80`. Doubles `D_80048930`/`D_80048938` stay asm-owned. Matching the 488-byte text would still need those 8 bytes at the original address (inventory split or TU pad). |

### 129–160-word band

| Function | Orig B | Incoming | Result |
|---|---:|---:|---|
| func_8002D9C4 | 536 | 129 | Not rewritten. Size 548/536; pointer/lifetime residue from T-024/T-027. |
| func_80030440 | 632 | 144 | Not rewritten. Glyph RLE; T-059 row-cursor form scored 89 but shrank to 364 B (wrong shape). |
| func_801BD3FC | 580 | 145 | Not rewritten. 64-bit unpack / history; C is 440 B. |
| func_80025D58 | 620 | 146 | Not rewritten. Paired-row loop; C is 328 B. Equality-termination peels to a worse 656 B (T-054). |
| func_801C1990 | 676 | 159 | Not rewritten. Stat compares and 64-bit zero stores; C is 604 B. |

## Follow-ups

- Treat `func_800326F0`/`func_80032738`/`func_80032750`/`func_8003278C` (and the decoder siblings) as handwritten or private-register, not IDO `-mips2` C.
- `func_801B1210`: migrate the eight menu strings plus `D_80292918` off this `GLOBAL_ASM` (same recipe as T-115) before promoting even an exact text draft.
- `func_8001AA90`: split `0x8001AC78` out of the function in the inventory, or accept 8 B of real `jr ra; nop` pad, before a 488 B C body can T4.
- `func_801C3758`: keep T-125; remaining 30 words are `t0`/`t1` address retention and the dual `v0`/`v1` zero. Do not take addresses of the two globals if that collapses to `lui`/`lw`.
- Near-miss RA on `func_801B0520` (22) and `func_801B446C` (28) is the same band T-123 deprioritised.

## Method

Read CONTRIBUTING, TRACKING (T-129 row), last WORKLOG techniques, permuter README, and REPORT.md hits for every assigned name. Symlinked `tools/ext`, `.venv` and `baserom.us.z64` from the lead worktree; first `make extract && make -j8 && make progress` was ROM-identical at 82,004 / 289,876 B (28.29%). Compared C objects with `elf_function` against `build/segments/ovl_7DF8.bin`. No permuter search was run (shared `tools/ext` must not be modified; a private clone exists only under `/tmp/decomp-permuter`). No artificial empty-if / dummy-goto / volatile / padding asm. `src/` restored to `GLOBAL_ASM` after failed promotions. `docs/TRACKING.md` and `docs/WORKLOG.md` not edited.
