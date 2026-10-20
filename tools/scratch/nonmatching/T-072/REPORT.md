# T-072 — sol-A25: main source-line layouts

**0 MATCHED, 5 IMPROVED drafts, 11 UNCHANGED.** All 16 assigned functions
were attempted, closest first. Changes are uncommitted for lead review.
Deleted drafts: **none**. No production function was promoted.

Read TRACKING, latest WORKLOG, Makefile and reports T-067, T-071, T-052,
T-054, T-059, T-046 and T-051 before probing. Missing baserom.us.z64, ROMs,
.venv and tools/ext were symlinked from the authorized main checkout.
No ROM was copied or committed.

## Method

Production IDO 5.3 `-O2 -mips2` flags throughout. First reconciled draft
structures, global declarations and callee declarations against their TUs.
The allocation-list view has head/tail/free at +0/+4/+8; particle records
are 16 bytes; stage records are 12 bytes; actor records are 0x100 bytes;
render-cache records are 0x30 bytes. Kept the RNG return type, array BSS
ownership and existing callback declarations consistent with the owning TU.
No unrelated source declarations were changed in the worktree.

Every function received 159 distinct token-preserving statement/brace layouts:
separate statements, own-line function/conditional braces, joined runs and
bounded deterministic mixed boundaries. Follow-up tested separate/combined
local declarations, split assignment chains and assignment/call-argument line
breaks. Counts: 2,544 initial layout probes, 273 declaration/chain/readability
probes, 640 expression-layout probes, 36 structural/type probes and 212
focused probes on the four closest functions. The focused pass checked real
local ordering/spill placement, white-channel store forms, and quit-loop
expressions. Diagnostic forms that altered behavior were never retained.
The bounded search is not an exhaustive claim.

All 16 final candidates also compiled through **asm-processor inside complete
owning TUs**, with all other functions present. The scores exactly agree
with the TU-prefix probes. Four needed later TU declarations hoisted in the
temporary copy: 15F6C's audio calls, B22C's DMA pool and callback ABI,
287D4's particle type, and A4F0's sequence pointer. Compatible typed views
preserve the shared globals rather than replacing other function bodies.
`complete_context.py` records those transformations; production TUs are untouched.

Scores are corresponding differing instruction words, masking only actual ELF
relocations, **plus absolute body-length delta in words**. They are diagnostics,
not linked matches or behavioral certification. Earlier reports often counted
only emitted mismatches. For example, AA90's previous 61 plus two missing
words is 63 here; BB64's 143 plus eleven missing words is 154. 18F20 also
changes under current TU declarations (141/688 B versus historical standalone
90/696 B), so its improvement is specifically **141→140 in the same TU
context**, not an improvement over the historical standalone metric.
Every retained candidate preserves its fresh baseline's emitted size.

## Per-function results

| Function | Result (old→new score) | Emitted / target B | What remains |
|---|---|---:|---|
| func_8002AEE4 | UNCHANGED 3→3 | 336 / 336 | +0x48 message-address setup and +0x9C/+0x108 quit constant register versus immediate. |
| func_80017378 | UNCHANGED 8→8 | 1752 / 1752 | Endpoint/base setup +0x590/+0x598 and loop pointer-increment/store schedule +0x59C..+0x5B0. |
| func_8002F45C | UNCHANGED 20→20 | 404 / 404 | Frame 0x30 versus 0x38, spill offsets and pan/temporary allocation. Local declaration permutations did not recover them. |
| func_80015F6C | UNCHANGED 21→21 | 268 / 268 | White constant allocation and dependent temporary registers; separate/chain/channel-order forms did not improve. |
| func_8001E0B4 | IMPROVED 26→24 | 648 / 648 | Own-line braces remove two scheduling differences; setup registers, render-cache address and branch delay scheduling remain. |
| func_8001AA90 | UNCHANGED 63→63 | 488 / 496 | Float call/spill/loop allocation and two missing words; widened phase temporary does not help. |
| func_80023EF0 | UNCHANGED 71→71 | 296 / 312 | Frame and saved-register allocation, actor traversal/count and facing control flow; width variants do not improve. |
| func_80018F20 | IMPROVED 141→140 | 688 / 696 | Reconciled BSS/global arrays; one layout scheduling word improves. Broad setup/constant allocation and missing words remain in TU context. |
| func_80024714 | UNCHANGED 94→94 | 712 / 712 | Resource-slot/address setup and register allocation, especially from +0xB0. |
| func_8002B22C | IMPROVED 93→91 | 392 / 380 | Separate statements remove two schedule differences. Cache-list traversal/frame/register shape and twelve excess bytes remain. |
| func_800287D4 | IMPROVED 89→77 | 560 / 556 | Separate statement/brace lines recover twelve words. Particle/RNG loop registers and one excess word remain. |
| func_80012390 | UNCHANGED 109→109 | 464 / 476 | Packed-image traversal/pixel-copy unrolling, frame and three missing words. |
| func_800191F0 | UNCHANGED 110→110 | 476 / 492 | Four-way actor update loop allocation/unrolling and four missing words; typed signed velocity view does not improve. |
| func_8002A4F0 | IMPROVED 65→53 | 920 / 920 | Separate statement/brace lines recover twelve words. Config-store schedule, stack slots and sequence-loop registers remain. |
| func_8001BB64 | UNCHANGED 154→154 | 592 / 636 | Color-copy loop/switch allocation and eleven missing words; array globals reconciled for TU probes. |
| func_8001D47C | UNCHANGED 141→141 | 748 / 748 | Grayscale division, unrolling and register allocation; byte-palette view and pixel widths do not improve. |

Updated the five improved drafts in their original T-022/T-024 locations.
No function_owner hint was removed or reassigned because no function was
converted. No boot, overlay, YAML, Makefile, status.csv, TRACKING or WORKLOG
edits; T-069's functions are untouched. Probe objects/logs remain under /tmp;
results.json keeps compact scores, sizes and final mismatch offsets. Scripts
describe the experiment stages and expect incoming drafts from the parent
revision when regenerating the original baseline. Duplicate candidate copies
were removed after retaining the five drafts.

## Final validation

`make clean && make extract && make all && make progress` **passed (exit 0)**.
The rebuilt ROM and all three images are byte-identical:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

Regenerated undefined-symbol files were retained; they have no final diff.
Generated progress documents also have no final diff. `git diff --check` passed.
Progress is unchanged because all five improvements remain drafts.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 66,040 (20.70%) | 66,040 (20.70%) | 0 | 275 | 0 | 287 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 39,772 (22.96%) | 39,772 (22.96%) | 0 | 129 | 0 | 161 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 17,800 (12.95%) | 17,800 (12.95%) | 0 | 146 | 0 | 105 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
