# T-130 — grok-3

**0 MATCHED. 2 drafts improved. 0 B / 2,030 B target.**

Rewrite band 129–242 words. Production `src/` is unchanged. No symbol, yaml or hint edits.

Fresh m2c from `asm/nonmatchings/...` went to `/tmp/grok-3-m2c/`. Each assigned function was rewritten at least once from that control-flow, then scored with `tools/permuter/screen.py` (`measure`, full TU first). Permuter ran on `func_801BAA78` (~8 min, best permuter-score 1523 from a dummy `do { ... } while (0)` wrap; not retained). Search dirs were under `/tmp/grok-3-*`.

## Per-function

Incoming numbers are `screen-2026-10-21.md`.

| Function | Orig B | Incoming words / compiled | This pass | Notes |
|---|---:|---|---|---|
| func_8002D9C4 | 536 | 129 / 548 | 132 / 504 (not retained) | m2c peels `to[0]`/`from[0]` then copies `[1..4]`. Peeling the first float and an explicit five-field copy both shrank the body and raised the score. The T-024 loop draft stays best. Frame 0x68, `f20`/`f22` hold frame/duration. |
| func_80030440 | 632 | 144 / 556 | 156 / 536 (not retained) | Original inner run fill is remainder-then-4 with xor-swap; extra row is remainder-then-4 sequential zeros. Caching `D_80069F70 + index*0x120` did not recover that unroll. T-059 row-cursor (89 words / 364 B) still rejected as the wrong size. |
| func_801BD3FC | 580 | 145 / 440 | **134 / 484** | Two `__ull_rshift` helpers at the prologue (`input >> 32`, `input >> 16`). `u64` in `a2`/`a3`, state pointer at `sp+0x28`. History compares use the low word at `D_802D3678[player]+4`. Shift results are still unused after the jal; size remains 96 B short. |
| func_80025D58 | 620 | 146 / 328 | 146 / 636 (not retained) | m2c is a 2-row unroll: if `height` is odd, peel `y=10` (xor 0), then `do { y; y+1; y += 2; } while (y != end)`. Restores original length (±16 B) but overlapping instruction diffs rise, so the word count does not fall. Aggregate 13-/14-byte height copies were already correct. |
| func_801C1990 | 676 | 159 / 604 | 167 / 696 (not retained) | m2c first `func_801C17D0` is `NULL` when `cpu==3`, and `(void*)((cpu-1)&0xFF)` when `cpu>0`. Wiring that grew the body past 676 B. `u64 D_802D3800[2] = 0` is the right 64-bit zero store. |
| func_801B1A7C | 872 | 206 / 596 | 213 / 312 (not retained) | Original is remainder-then-4 on 16-byte vertices. `for (i = 0; i < count+1; i++)` and pointer walks under-unroll (2× or none). T-025 indexed loop remains best. |
| func_801BB7B4 | 940 | 220 / 960 | 226 / 944 (not retained) | m2c `s32` audio handles vs the T-023 `u8`/`*(s32*)&` view. Two- vs three-argument `func_8002F6DC` is real (K&R). Score moved the wrong way in declaration context. |
| func_801BAA78 | 884 | 222 / 912 | **208 / 892** | T-023 had collapsed `y0` and `y1` onto `scale*0xB4`. Restore `y0 = scale*0xB4` and `y1 = scale*0x350`, `s32 arg0` plus Gfx cursor like family C. Counter at `D_801F3A50[arg5]` increments *before* the draws. Still 8 B long. |
| func_801C317C | 936 | 225 / 940 | unchanged | Already a typed m2c in T-030 (`FrontendRenderContext` matrices, `D_80285574` walker). 4 B long; leftover is float temp / saved-counter scheduling. |
| func_800216D4 | 1032 | 229 / 1040 | unchanged | T-032/T-093 already match m2c (bank specials, 8-aligned DMA, `D_8004D278[i][player]` stride 0x18). 8 B long. |
| func_80031A38 | 920 | 229 / 680 | not rewritten as C | m2c is a packed RLE walk over `D_8004CED0` keyed by `D_8004EA78`. T-045 flagged a private decoder ABI; the 240 B size hole matches an unroll the current draft never emits. |
| func_801AF68C | 956 | 231 / 940 | 234 / 936 (not retained) | `D_802A1990`..`D_802A1A60` is 52 pointers. Using `&D_802A1A60` as the scan sentinel (they are adjacent) did not beat `D_802A1990 + 52`. First-loop Gfx is remainder-then-4; compaction copies 4 pointers at a time. |
| func_80027E1C | 936 | 234 / 940 | unchanged | T-054 is already cleaned m2c (age lerp, 4-vertex quad, postincrement Gfx). 4 B long. |

## Follow-ups

- `func_801BAA78`: finish the 8 B / 208-word residue (counter wrap vs family-C post-increment; Gfx `F9000000`/`0xFA` store order).
- `func_801BD3FC`: consume the `>> 32` / `>> 16` results (stick/high half) instead of leaving the libcalls unused; that is the remaining ~96 B.
- `func_80025D58`: keep the 2-row form in mind; next gain is dropping the extra 16 B without re-collapsing to the 328 B single-row loop.
- `func_80031A38`: confirm whether it is IDO-unrolled RLE or a private-register decoder before more C passes.
- `func_801C1990`: `func_801C17D0(NULL, 0)` vs `func_801C17D0(stats, 0)` needs the callee’s real prototype from `func_801C17D0.s`.

## Method

Read CONTRIBUTING, TRACKING (T-130), WORKLOG, permuter README, and REPORT.md hits for every assigned name. Symlinked `tools/ext`, `.venv` and `baserom.us.z64` from the lead worktree. First `make extract && make -j8 && make progress` was ROM-identical at 82,004 / 289,876 B (28.29%). No artificial empty-if / dummy-goto / volatile / padding asm. `src/` left as `GLOBAL_ASM`. `docs/TRACKING.md` and `docs/WORKLOG.md` not edited.
