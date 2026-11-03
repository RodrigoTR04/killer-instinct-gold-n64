# T-128 — grok-1 (91–119-word band + func_8002FB80)

**0 MATCHED, 0 B / 2,030-byte target.** Two drafts improved. No production C promoted.

## Per-function results

Words are relocation-masked differing instruction words, including size mismatch.

| Function | Original B | Words before → after | Compiled B | Notes |
|---|---:|---:|---:|---|
| func_8002FB80 | 544 | 23 → 20 | 544 | Exact size. Case 0xC0/0x40 tails only. |
| func_801BADEC | 568 | 102 → 101 | 560 | Direct `arg4->scale`; still 8 B short. |
| func_8002FDA0 | 572 | 107 → 107 | 556 | s16-view rewrite was worse (128/552); not retained. |
| func_801C11F0 | 580 | 113 → 113 | 584 | Unchanged; one extra instruction plus call/frame diffs. |
| func_8001272C | 544 | 103 | — | Screened only. |
| func_801BBC84 | 508 | 112 | — | Screened only. |
| func_800191F0 | 476 | 110 | — | Screened only. |
| func_801B677C | 492 | 117 | — | Screened only. |
| func_80016078 | 448 | 119 | — | Screened only. |
| func_80012390 | 500 | 101 | — | Screened only. |
| func_8002DDD4 | 444 | 104 | — | Screened only. |
| func_8001CD50 | 436 | 98 | — | Screened only. |
| func_801CD1F0 | 456 | 91 | — | Screened only; pfs cursor/saved regs. |
| func_801C17D0 | 436 | 103 | — | Screened only. |
| func_80032360 | 116 | 105 | 420 | Wrong reconstruction; skipped. |
| func_80026738 | 388 | 96 | — | Screened only. |

## func_8002FB80 diagnosis

T-125 already matched cases 0x80 and 0 and almost all of 0xC0 (including `slti`/`bnez` with `srl t7, address, 24` in the delay slot). The remaining 20 words are two tails:

1. **0xC0 join (5 words):** original stores `address>>24` (live `t7`) first, then computes `>>16`/`>>8`, with `data++` between those shifts and the last three stores. IDO hoists the later shifts before the first store. Putting `data++` immediately after `out[0]=address>>24` recovers the `addiu a0, a0, 1` slot (23→20 with the 0x40 change).
2. **0x40 (15 words):** original loads `data[0]`, increments both pointers, masks the index, interleaves `data[1]` with the `sll`/`addu`/`lw`, stores `data[1]`/`data[2]`, then address bytes, then `data[3]` last. Storing `out[1]=data[1]` before the texture load is what currently scores best, but it still loads `data[1]` first.

declorder exhausted 1,564 layouts at 20 words (`--context full`, seed 128). Permuter (`--stack-diffs`, ~10 min) reached weighted 775 via a texture temporary; that is 21 words, not better. Rejected: empty branches, extra dummy locals that inflate the frame, byte-wise texture copies.

## Other attempts

- **func_801BADEC:** family-C lesson (do not cache scale). Direct field reads drop 102→101 and 552→560 B. Direct `D_801F3AA0` globals (matching the `lui`/`lo` original) lost size and scored 133.
- **func_8002FDA0:** inner loop already uses a shared case 1/2 subtract-byte path. An `s16 *` view of previous/out did not recover the `sll j, 1` addressing.

No yaml, symbol, or Makefile edits. Production `GLOBAL_ASM` lines were not replaced.

## Follow-ups

- func_8002FB80: force `sb address>>24` before the later shifts without an artificial barrier; interleave 0x40 `data[1]` with the texture pointer math.
- func_801BADEC: still not the unconditional two-draw family-C shape (two animation windows, early skip). Coordinate spills at 0x54/0x4C after the first jal.
