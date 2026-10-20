# T-098 — sol-A33: clone family B

**0 MATCHED, 6 IMPROVED: 65→57 differing words each, 536/536 bytes. Family B remains unsolved. No commits.**

Only the six T-025 scratch drafts changed. No GLOBAL_ASM was replaced and no draft was deleted. Production C, including all matched family-A definitions, is unchanged. These drafts are diagnostic work, not behavior-validated C: the inherited late-path uninitialized alpha read remains explicitly marked.

Read TRACKING.md, latest WORKLOG.md, Makefile, and the T-097, T-048, T-053, T-057, T-074 and T-077 reports. Linked missing baserom.us.z64, ROMs, .venv and tools/ext from `/home/rodri/Projects/killer-instinct-gold-n64`. No ROM contents were copied into git. No subagents or permuter workers were used.

## A versus B

Both families use a 0x28-byte frame, preserve the display cursor owner in s0, home the remaining incoming arguments, load a signed 32-bit animation counter into a2, compare its old value with signed slti, and increment it once in an ordinary beqz delay slot. Both combine the real `func_801B19F0(f32, f32, s32, s32)` with guTranslate and display-command construction. The entry and completion flags are u8 and depth is s16.

A returns zero when its entry flag is >=2; B returns zero when its flag is below its per-copy threshold (2 through 7). A interpolates position with denominator 1, then uses the vertex helper. B interpolates an unsigned grayscale/alpha value from 0.0f to 255.0f with denominator 10, packs primitive color, translates at a constant per-copy x coordinate, then emits environment color and a shared display-list reference. B increments D_801D308C after its counter reaches 10.

The call setup must not be copied instruction-for-instruction from A. A loads nonzero f12 before f14 and stores the new counter in the jal delay slot. B instead has:

| Relative offset | Target operation |
|---|---|
| +34 / +38 | Counter lui/lw directly into a2 |
| +3C / +40 | Store-address lui at; FA000000 constant in t9 |
| +44 / +48 / +4C | slti v0,a2,10; beqz v0; increment a2 in delay slot |
| +50 / +54 | Load 255.0f into f14 |
| +58 / +5C / +60 | Counter-store lui at; zero f12; store incremented a2 |
| +64 / +68 | jal lerp; a3=10 in delay slot |
| +6C through +E8 | Unsigned float-to-u32 conversion branches and 2^31 fallback; FCSR restore is delayed to +104 |
| +EC through +124 | Mask grayscale, replicate RGB, allocate command, retain alpha separately, store words |
| +128 through +184 | Late counter store, command allocation, old stack-byte read, palette color, completion flag |
| +188 onward | Translation and final commands |

The target's stale-byte read is `lbu t7,0x27(sp)` at +130, before assigning alpha=255 at +174. It is not a palette or counter width issue. Initializing alpha changes that operation; using a separate uninitialized local changes which stack byte is read. Neither is an accepted repair.

## Retained improvement

Transferred A's explicit local `s32 *counter`, `arg1 = *counter`, postfix predicate `arg1++ < 10`, and `*counter = arg1` as the third lerp argument, with the late branch storing the same incremented value. This recovers a2/v0, the ordinary branch, its shared increment delay slot, and B's +50..+68 call setup. IDO correctly puts B's store before jal and the denominator in its delay slot; forcing A's delay-slot ownership would be wrong.

The incoming u16 color assignment caused an additional `andi ...,0xFFFF` after its existing byte mask. The retained color is u8, assigned from `(u16)value`, then explicitly masked where packed. This preserves the original low byte: truncating to 16 then 8 bits equals `value & 0xFF`. The float is still explicitly converted to **u32**, preserving the target's unsigned conversion sequence. Alpha is assigned from that byte instead of remasking the full value. No global width or prototype changed.

This combination measures 58 words. Keeping alpha assignment and the following command-word store on separate physical lines yields 57; a comment identifies this scheduling-sensitive boundary. The retained layout is ordinary multiline C. Removing the intermediate cast, joining the block, reversing the final OR, and changing command representation did not improve it. Separate full-width and byte temporaries are not interchangeable for IDO scheduling even when their low-byte arithmetic agrees.

## Remaining instruction diagnosis

`results.json` records every final differing offset and target/generated instruction text for the representative. With this candidate, all six match +188 onward under relocation masking. The unresolved regions are:

* +3C/+40: generated code hoists the old `lbu t0,0x27(sp)` to the prefix, displacing the target's counter-store address / t9 constant setup. The counter load, predicate, shared increment and call setup otherwise agree.
* Conversion: generated code allocates the command cursor before conversion completes (`lw v1` at +78; increment/store at +84/+88). Target keeps that load at +F0 and increment/store at +10C/+110. This accounts for many aligned-word differences without implying a different numerical conversion. Generated FCSR save/restore uses t8; target uses t7. Conversion status/result remains a0 and floating scratch remains f4.
* Packed result: target's final OR is `or t7,t6,t1`; candidate uses `or t7,t1,t6`. Target's primitive-color constant is t9; candidate uses t8 on the early path and t1 on the late path. The color and alpha remain separate masked bytes.
* Late path: target reloads stale alpha into t7 at +130. Candidate has already loaded it into t0. That changes palette replication temporary numbering. The target holds the completion-flag pointer in a2; candidate uses a3. Final depth/alpha handling and both tail commands agree.

The 57-word result is not close enough to promote: it still has real register/lifetime and scheduling differences, and the stale-byte C model remains unresolved.

## Experiments and rejected alternatives

All measurements compile the candidate inside the **complete owning TU**, with its other matched definitions and GLOBAL_ASM stubs intact, using production IDO 5.3 -O2 -mips2 via asm-processor. Scores include instruction-count differences and mask only actual ELF relocation fields. Compiler failures are not scored as matches. Final linked image equality is the acceptance criterion for production code.

Tested counter pointer initialization placement, common versus branch-local stores, argument assignment versus separate stores, reuse of incoming scalar arguments for conversion output, signed/full-width/narrow color and alpha locals, separate or shared branch colors, fused conversion/mask assignments, direct versus temporary float results, command cursor update order, branch-local pointer scopes, cached completion-flag pointers, alpha pointers/structs/unions/arrays, command structs/word arrays/union views, and token-preserving line layouts. Some broad layout/type runs were stopped after repeated unchanged outcomes; no exhaustive-search claim is made.

A distinct uninitialized `previous` byte produced a lower **48-word diagnostic** at the right size, but read **sp+26**, not the required sp+27, so it was rejected. Initializing alpha, altered storage extents, and stack-shape variants were not retained. Raw u32 command pointer arithmetic increased size. Alternate command field representations did not improve the final representative. Temporary compiler products and bulky per-candidate logs are not retained in the repository.

The compact harness and recheck.py reuse T-096's full-TU comparator. Run `.venv/bin/python tools/scratch/nonmatching/T-098/recheck.py` after extraction to reproduce final measurements; expanded sources and compiler products stay in /tmp.

## Per-function result

| Function | Counter | Flag threshold | Translation x | Result | Bytes |
|---|---|---:|---:|---|---:|
| func_801B2EF4 | D_801D30C0 | 2 | -125.0f | IMPROVED 65→57 | 536/536 |
| func_801B310C | D_801D30C4 | 3 | -75.0f | IMPROVED 65→57 | 536/536 |
| func_801B3324 | D_801D30C8 | 4 | -30.0f | IMPROVED 65→57 | 536/536 |
| func_801B353C | D_801D30CC | 5 | 14.0f | IMPROVED 65→57 | 536/536 |
| func_801B3754 | D_801D30D0 | 6 | 70.0f | IMPROVED 65→57 | 536/536 |
| func_801B396C | D_801D30D4 | 7 | 128.0f | IMPROVED 65→57 | 536/536 |

Each copy was independently compiled before updating its original draft. All retain D_801D3030, D_802C87D0, D_801D3094, both byte flags, and their own constants. No production declarations were needed. main, boot, ovl_7E00, YAML, Makefile, status.csv, TRACKING and WORKLOG are untouched.

## Final verification

`make clean && make extract && make all && make progress` passed (exit 0).
The ROM and all three executable images are byte-identical, preserving every already-matched function, including family A:

- ROM: ba52e91b44450c548467044b26951353dc491e04
- main: 81736d32e8cda8f399b319a49250dff972b81af8
- ovl_7DF8: ea830aae50ff1422da60d4b7fdbfc29f03b1be39
- ovl_7E00: 2b01138a290212b9d886981e1196f7b6fb45ecdb

`git diff --check` passed. No task probe processes remain. Generated docs/functions.csv and docs/progress.html were restored after recording this table. No commits. Matching totals are unchanged.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 63,432 (21.88%) | 63,432 (21.88%) | 0 | 215 | 0 | 294 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 29,576 (20.54%) | 29,576 (20.54%) | 0 | 94 | 0 | 143 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 25,388 (18.47%) | 25,388 (18.47%) | 0 | 121 | 0 | 130 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
