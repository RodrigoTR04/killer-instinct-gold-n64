# T-079 — sol-B26

0 MATCHED; four drafts improved. Changes are uncommitted for lead review.
No production source or declaration was changed; all four functions remain
assembly-backed. No drafts were deleted.

Scores are relocation-masked positional differing instruction words plus the
instruction-count delta (T-056 method). They are diagnostics, not behavioral
validation or linked matching claims. Retained drafts compile both with their
owning declaration prefix and, separately, through asm-processor in their complete
owning TU; both measurements agree.

| Function | Result | Retained / original bytes | What remains |
|---|---|---:|---|
| func_801BDF94 | IMPROVED **406→353** | 1440 / 1452 | Natural glyph loop and command allocation; typed 64-byte aligned matrices, 8-byte glyph records, two-word Gfx records, and float matrix/LookAt prototypes. Saved-register allocation, FP lifetimes, matrix scratch frame, command scheduling and loop lowering still differ. |
| func_801BCB70 | IMPROVED **416→391** | 1676 / 1676 | Typed Gfx cursor and halfword mask indexing; unsigned source coordinates/row step and run count recover the unsigned FP conversions. Restored the missing unused fifth parameter so later stack arguments occupy their actual ABI slots. Clipping temporaries, mask-run loop, saved registers and packet scheduling still differ. |
| func_801C23C0 | IMPROVED **362→222** | 1812 / 1820 | Complete camera context through matrix pointer at +0xF8, three-argument sound prototype, removed artificial spill-copy locals, ordinary Gfx postincrements. Integer divisor `2` preserves target div.s for camera interpolation; `2.0f` folds to multiplication. Stack frame/vector placement, FP temporaries, global addresses and tail scheduling remain. |
| func_801C08F8 | IMPROVED **565→561** (raw TU baseline did not compile) | 2216 / 2296 | Existing TU pair structs, real float renderer prototypes and byte color arguments, pulse captured before first renderer call, natural mutable packed-score loop and explicit u64 radix. Honest byte copy replaces unaligned u32 name store. 64-bit helper sequencing, alphabet-loop unrolling, buffer layout and FP/register allocation remain far apart. |

C08F8's numeric baseline uses only declaration reconciliation: remove its
conflicting D_802D37D8/D_802D37E0/D_802D37F0 extern arrays and index the existing
pair records through their s32 representation. Its unchanged body then scores
565, 2276 bytes. The original draft itself fails in the TU; no numeric score is
claimed for that failed compilation.

## Recovered structure and experiments

BDF94 reserves an optional scale matrix, optionally rotates the whole string,
sets reflected lighting, counts the string for the 30-degree stagger, and emits
per-glyph translation/rotation/scale/list commands. Glyph indices are signed
bytes; '.' maps to glyph 26 and 'j' enables fixed advance. Its glyph table holds
a display-list address and float width. Ordinary natural loops replaced the
m2c temporary graph. A shared command pointer variant and signed/full-width
character variants were measured; the best natural rewrite is retained.

BCB70 traverses source columns with a u16 bit mask and groups consecutive selected
rows into runs (up to the target's five-step test). Each selected run emits the
texture-image/tile/load/sync/rectangle/texture-coordinate packet. Left/top source
bounds and screen rectangle coordinates are clipped separately. Unsigned
conversion expressions explain the original 2^32 corrections. Fixed packet
indexing shortened the function but did not improve its score and was rejected.

C23C0 interpolates camera position/velocity from twelve cubic coefficients,
blends pitch/yaw, optionally applies a decaying circular offset, updates the
render camera, draws the scene, then dispatches the timed UI/audio sequence.
The unsigned tick difference and x/z/y camera field order are retained. Vector
records, alternate vector ordering, divisor spellings and command postincrements
were measured. The target frame is 0x70; the candidate still allocates a larger
frame. It has not reached scheduling-only proximity.

C08F8 decodes ten base-36 pairs above the base-11 score digits, finds the minimum
nonzero components, draws up to five category lines, then the pulse/cursor,
alphabet rows and entered name. Packed score is divided in place during category
traversal, as in asm. The initial shade uses the value captured before BE660,
while the digit is read afterward. The asm stores the four-byte name with
swl/swr at name+1; the candidate uses defined byte accesses rather than an
unaligned u32 lvalue.

Ordinary multiline statements/braces and several structural/type variants were
measured for each function. No inline asm, #line, register variables, flag changes
or output rewriting was used. Large positional scores can obscure structural
improvements; none of these candidates warrants promotion.

## Reproduction and scope

Read TRACKING, latest WORKLOG, Makefile and T-070/T-076/T-069/T-056/T-067 reports.
Missing prerequisites are symlinks to the authorized main checkout at
`/home/rodri/Projects/killer-instinct-gold-n64`. No ROM was copied or staged.

Run `.venv/bin/python tools/scratch/nonmatching/T-079/check_drafts.py` after
extraction. Small probe helpers are copied from T-076 with isolated /tmp/t079
outputs. Rejected candidates and bulky output remain outside the repository.

The full-TU checker reconciles C23C0's local Gfx type with the later matched
function's aligned command union, and omits the later duplicate context extern.
The matched function body is unchanged. Those substitutions exist only in the
temporary TU; no production declaration was changed. All other candidates need
no checker-specific declaration substitutions.

No main, boot, ovl_7E00, YAML, Makefile, status.csv, TRACKING or WORKLOG edits.

## Final clean validation

`make clean && make extract && make all && make progress` passed.
`git diff --check` passed. Generated progress files and linker symbol lists have
no net changes. All four full-TU scratch checks passed before the clean build.

- ROM: `ba52e91b44450c548467044b26951353dc491e04`, byte-identical.
- main: `81736d32e8cda8f399b319a49250dff972b81af8`, byte-identical.
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`, byte-identical.
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`, byte-identical.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 70,556 (22.11%) | 70,556 (22.11%) | 0 | 272 | 0 | 290 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 44,288 (25.57%) | 44,288 (25.57%) | 0 | 126 | 0 | 164 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 17,800 (12.95%) | 17,800 (12.95%) | 0 | 146 | 0 | 105 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
