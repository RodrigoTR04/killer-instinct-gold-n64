# T-121 — sol-A41, structure-first 128–176-word band

Measurements use IDO 5.3 `-O2 -mips2`, asm-processor, and the relocation-masked positional word comparison from `tools/permuter/screen.py`. A word score includes extra/missing words; it is not the permuter's weighted score. Byte columns are compiled/original. Full TU was preferred; legacy conflicting declarations required the declarations fallback for 800170C4, 801C9698, 8001D47C, and the initial 8001BB64, and prefix context for 800241BC and 801ACB1C.

## Results

| Function | Result | Bytes before → after | Words before → after | Structural finding / remaining issue |
|---|---|---|---|---|
| func_801C2F5C | IMPROVED | 556/544 → 548/544 | 128 → 53 | Full-width scale local and one Gfx cursor remove narrowing/lifetime overhead. Explicitly caching the initial sprite/scale index reaches 544 B but initially scores 71; remaining issue is reload lifetime and scheduling. |
| func_801AFFAC | IMPROVED | 568/576 → 576/576 | 129 → 99 | Separate branch stores and cache the color before advancing the command cursor; avoids an alias-sensitive global reload. Remaining conversions/register allocation differ. |
| func_800170C4 | UNCHANGED | 696/692 | 134 | Original copies eight vertices with four-way unrolling. Pointer/countdown forms change IDO's unroll decision (552–736 B); explicit four-lane copies get unrolled again. No defensible improvement. |
| func_801C9698 | UNCHANGED | 1148/1148 | 135 | Correct u8 index and Gfx/matrix widths confirmed. Original frame B0 versus draft C8; eye/name/matrix lifetimes and FP hoisting remain. Cached zero/-400 values did not help. |
| func_8002FDA0 | UNCHANGED | 556/572 | 107 | Fresh baseline already contains T-112's improvement, unlike the supplied 584 B screen. Flags are u16; widening/signing worsens the code. Three-position loop and byte-color tail scheduling remain. |
| func_80018F20 | UNCHANGED | 688/696 | 138 | Original constants 1289/1100/1198 confirmed. Externalizing literals only saves one positional word and leaves the size gap; not retained. |
| func_8001D47C | UNCHANGED | 748/748 | 141 | Grayscale division by three is four-way unrolled; output cursor intentionally begins at address zero. Reusing the incoming argument worsened register allocation. |
| func_80017A68 | UNCHANGED | 764/772 | 149 | Original external constants are 359 and 0.01. Literal conversion did not recover the missing two instructions. |
| func_801C4240 | IMPROVED | 1344/1344 | 150 → 126 | Cache the first display-list address across calls; combine the scale assignment. No fabricated depth array/padding. FP spill slots and helper-call allocation remain. |
| func_801B6BD8 | UNCHANGED | 628/628 | 153 | Original accumulates matrix count in s0. Reusing count shrinks to 612 B but loses target shape. A 624 B permuter candidate used first/second before initialization and was rejected. |
| func_8001BB64 | IMPROVED | 592/636 → 632/636 | 154 → 142 | Color channels and brightness are s16, recovering target sign-extension sequences. Reconciled existing array declarations so the retained draft compiles in the full TU. Endpoint-cache variants trigger unwanted unrolling. |
| func_801BEA74 | MATCHED | 676/664 → 664/664 | 154 → 0 | s32 scores remove three masks; independent byte cursors avoid argument writeback. Accumulator/flag declaration order recovers spill slots; for-loop initialization/update layout recovers the last twelve words. Integrated C, deleted draft. |
| func_8001DE5C | UNCHANGED | 624/600 | 155 | Found real draft errors: x2 decrement is unconditional, only negative bounds subtract 0x10000, stride is s32, calls take three arguments, and sprite indexing must use byte stride 28. Corrected diagnostic is 636 B/155 words, so preserved separately as bounds_abi_candidate.c rather than claiming improvement. |
| func_801B0668 | IMPROVED | 984/984 | 156 → 154 | Moving the used sin spill local among command locals improves stack allocation. State caching already present; narrowing state to u8 worsens code. |
| func_800241BC | IMPROVED | 840/820 | 160 → 158 | Reuse the packed-resource cursor for its next stage, consistent with original s0 progression. DMA widths/argument lifetimes and 20 excess bytes remain. |
| func_801B0A40 | IMPROVED (text only) | 684/668 → 668/668 | 163 → 0 | u32 tick conversion, single height local with float assignment before subtraction, integer division by two, and used eye-vector fields recover target. Constant emission is checked separately below. |
| func_8001346C | IMPROVED (size) | 696/704 → 704/704 | 165 → 165 | Reuse loop index as the transform flag to restore two instructions. Switch/jump-table ownership already exists; restoring the older post-switch render structure instead grows to 732–748 B. |
| func_801ACB1C | UNCHANGED | 756/744 | 176 | Original reuses s0 for message address then Gfx cursor address; draft frame 68 versus target 60. Message/event caching and switch forms did not improve it. |

## Matching details

`func_801BEA74`: full-width score locals, separate input cursors, and the for-loop header are all material. The declaration sequence is result, flag, multiplier; it produces the original 0x48 frame and 0x40/0x30 u64 spills. This function owns no constant hints.

`func_801B0A40`: unsigned conversion avoids the signed correction sequence. The easing expression must first round into the f32 height before subtracting 35. Dividing by integer 2 retains the target double divide, whereas 2.0 produces strength reduction. The eye vector's three fields are used by guLookAtReflect. This TU already has a rodata section; there are no function_owner hints for this function or its four constants. A literal-only variant has the same size but changes the frame by eight bytes (11 words). Named const definitions preserve the exact text match, but IDO emits them into .data: the linked overlay grows by 16 bytes and fails its image check. That integration was reverted. The exact extern-constant draft is retained; it needs constant-pool emission/ownership resolved before promotion. Literal-only declaration permutations and eye-component reuse reached two differing words but no linked match. `literal_pool_candidate.c` preserves this variant: only the angle store/reload uses +0x50 instead of the target +0x54. Both that diagnostic and `bounds_abi_candidate.c` are excluded from promotion and contain no assembly.

## Searches and rejected experiments

Used the shared decomp-permuter with `-j5`, stack differences, best-only/better-only output, and bounded 15-minute searches on equal-sized 801C9698, 8001D47C, 801C4240, 801B0668, 801B6BD8, then equal-sized C2F5C/1346C/AFFAC candidates. BEA/0A also received declaration-layout searches and focused manual multiline/layout experiments. Outputs stayed in /tmp; no permuter output directories are retained.

All candidate bodies were reviewed before adoption. Besides the uninitialized count candidate, a lower AFFAC score removed the alpha mask and changed behavior outside the expected fade range; rejected. Explicit stack padding, unused vector fields, and changed loop trip counts were not retained. The Gfx/matrix layouts were checked against include/render.h and T-069. Correct types and local caching mattered more than broad random mutation.

## Validation

`MAKEFLAGS=-j8 make clean && MAKEFLAGS=-j8 make extract && MAKEFLAGS=-j8 make all && MAKEFLAGS=-j8 make progress` passed. Main, ovl_7DF8 and ovl_7E00 images match their reference SHA-1 values. The rebuilt ROM and baserom both hash to `ba52e91b44450c548467044b26951353dc491e04`; the build reports byte identity and unchanged ROM bytes outside the spliced slots. `git diff --check` passed. No function_owner hints changed, and regenerated undefined-symbol files have no retained changes. Generated docs/functions.csv and docs/progress.html were restored; status.csv was not edited. No commits.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 74,068 (25.55%) | 74,068 (25.55%) | 0 | 189 | 0 | 320 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 32,792 (22.78%) | 32,792 (22.78%) | 0 | 88 | 0 | 149 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 32,808 (23.87%) | 32,808 (23.87%) | 0 | 101 | 0 | 150 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |

