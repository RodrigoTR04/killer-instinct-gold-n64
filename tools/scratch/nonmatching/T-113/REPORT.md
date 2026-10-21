# T-113 — sol-B36: screen refresh and closest-draft diagnosis

**0 MATCHED, 2 IMPROVED, 13 UNCHANGED. No commits.**

Read TRACKING, latest WORKLOG, overview, Makefile, permuter README/screener,
T-099 screen, T-104/T-109 near-miss reports, T-096/T-097 diagnosis method and
T-067 line-layout findings. Missing baserom.us.z64, ROMs, .venv and tools/ext
were symlinked from the authorized shared checkout. No ROM was copied or staged.

## Screen and method

`screen.md` records all 195 current T2 drafts: 131 full-TU, 25 prefix,
37 declaration-fallback results and two compilation errors (8001D080 and
80021B6C). The errors remain explicit; these functions are outside the selection.
Full owning TUs are preferred; the remaining prefix/declaration fallbacks are
explicitly marked. `selected.json` records the closest 15 after excluding all
four T-112 TUs, T-111's family B/B258/ADEC functions and the eleven private-ABI
decoder kernels. Selection sorts by differing words, then function name;
all selected bodies have the original size. The screen is the incoming baseline,
so it deliberately still includes the subsequently improved C7998 draft.

Every selected function received an instruction-level diagnosis, concrete C
probes, then token-preserving multiline/joined-line layouts. Comparisons use
IDO 5.3 -O2 -mips2 through asm-processor and count differing instructions plus
length differences, masking only actual ELF relocation fields. `instructions.json`
records every incoming differing instruction. Frame/slot/width observations
below refer to the incoming draft, not an independently invented ABI.

Search/compiler artifacts live under /tmp/kig-t113, outside git. Searches use
local decomp-permuter, -j5, --stack-diffs --stop-on-zero --best-only --better-only.
The 15 bounded searches run concurrently; each receives 900 wall-clock seconds.
Weighted permuter penalties are distinct from independent instruction counts.
All inputs are smoke-compiled before searches launch. Audio preprocessing needs
-D_LANGUAGE_C to retain ADPCM_STATE and related SDK types. Input preparation
first exposed a missing asm glob, then that preprocessing issue; neither failed
preparation launched a search. The corrected preparation uses parsed C function
declarations to remove other bodies while retaining complete return/parameter
types. No preliminary malformed input is counted as search evidence.

## Per-function results

Offsets are relative to the function. All instruction widths are four bytes;
byte/halfword below describe memory operations. Frames and unaffected slots
remain those of the incoming draft unless explicitly discussed.

| Function | Incoming → retained words | Result | Diagnosis and concrete hypotheses tested |
|---|---:|---|---|
| func_800269AC | 2 → 2 | UNCHANGED | Only +88/+8C primitive stores are reversed: target writes t8 to +4 before t7 to +0. Cursor ownership and all three command positions agree. Reversed/combined stores, grouped cursor/store lines and ordinary layouts do not recover both without other differences. No width/frame change retained. |
| func_8002F6F4 | 2 → 2 | UNCHANGED | +68/+160 load/store s4 at sp+74 instead of sp+64; frame 80, start event +50, repeat event +40, repeat time +68 and halfword repeat +6E agree. Declaration orders, event/key scopes, inlined key and timing-in-event diagnostics do not recover the spill. The existing uninitialized-step path on failed first allocation is unchanged; no initialization or fake padding is introduced. |
| func_801BF720 | 2 → 2 | UNCHANGED | +1C default space belongs to v1 instead of v0; +64 return delay slot needs move v0,v1 instead of nop. All explicit case returns agree. Result widths, signed/unsigned input views, else/default placement, shared return and layouts do not solve ownership. Narrow return types worsen code. Prefix context retains the later signed-input prototype reconciliation requirement. |
| func_801BF914 | 2 → 2 | UNCHANGED | +68 default 27 belongs to v1 instead of v0; +70 return delay slot needs move v0,v1. Result widths, input/result reuse, default placement, common case exits and layouts fail. Prefix context has the same later signed-input prototype issue. |
| func_801C4E38 | 2 → 2 | UNCHANGED | +88/+B8 selector spill/reload is sp+18 instead of sp+1C, same frame 20. Meaningful selector snapshots with byte/word widths at several call boundaries and layouts worsen or retain the miss. Declaration fallback contains legacy scalar/global declaration conflicts; no fallback zero or integration is claimed. |
| func_801CC908 | 2 → 2 | UNCHANGED | Only +0C/+19C frame allocation/free is 40 instead of 30. Mask/status/handle homes otherwise agree. Removing dead mask home, consolidating status and 48 declaration orders can reduce frame but disturb live slots/order. No padding object or dead-code workaround retained. |
| func_801B6528 | 3 → 3 | UNCHANGED | +178 card reload owns a0 instead of a2; +1A0/+1E8 index loads inherit that base. Same frame and +24 card spill. Late typed/void card aliases, arg2 reuse and declaration/line layouts do not change ownership. Search score improvements independently remain 3 or worsen to 9 words. |
| func_8002F45C | 4 → 4 | UNCHANGED | +B4/+C0 decay load/add uses a1 instead of v1; +DC/+E4 key-byte load/mask uses v1 instead of t3. Equivalent decay comparison, direct flag assignment, byte/word flag locals and layouts fail. Shared audio header ABI and all existing spills remain intact. |
| func_801B695C | 4 → 4 | UNCHANGED | Frame is 30 versus 28; +08/+5C arg0 home follows frame at +30 instead of +28. Other spills agree. Frame-offset algebra, inlined bank, earlier player-offset setup and layouts fail. Prefix context still requires reconciling the later asset-view declaration before integration. |
| func_801C85C0 | 4 → 4 | UNCHANGED | +48/+4C next index add/mask must precede byte/word clears at +50/+58; draft emits first clears earlier. Precomputed next indices with several widths, real store/argument expression grouping and layouts fail. Byte callee argument, loop-clearing widths and frame remain unchanged. |
| func_801B5534 | 5 → 5 | UNCHANGED | +18/+7C player reload must be lbu at sp+23 instead of lw +20; +68/+74 offset slot must be +1C instead of +18; +70 call uses move instead of andi. Byte/halfword/K&R input views, index snapshots, explicit narrowing and layouts do not solve all requirements. Shared random sample and both table writes preserved. |
| func_801C224C | 6 → 6 | UNCHANGED | Entry +04..+1C saves/order and input owner differ: target initial byte store uses a2, draft moves input to s0 early; later body agrees. Parameter widths, separate initial mode, separate later selectors and layouts disturb allocation or retain six. No new ABI is proposed. |
| func_801C7998 | 6 → 0 (body only) | IMPROVED, rodata blocked | Actual input is one u64, not separate unused-byte and u16 arguments. Target homes a0/a1 then masks the low word and zeros the high word. One u64 parameter and switch(buttons & 0xFFFF) recover all six entry differences, frame 18 and every slot. Clean full-TU instruction zero; integration fails linked rodata ownership. Reverted production integration and retained the clean draft. See ABI/rodata evidence below. |
| func_801BD270 | 7 → 7 | UNCHANGED | +154..+170 high sum, low sum/carry, high spill and sign contribution have different owners/order. Existing s16 Y/u16 buttons homes already match. Unsigned low-word views, OR packing, reassociation and layouts do not recover the target chain. Narrowing or signedness changes were not retained. |
| func_80017378 | 8 → 6 | IMPROVED | Joining only the model/rotation setup and while opening recovers endpoint/base setup at +590/+598. +59C..+5B0 still stores four model words before pointer increments; target advances rotation/model first and stores at negative offsets. Early increments, reversed initialization and joined loop prefixes fail to solve the remaining six. Minimal three-line join retained in the original draft; full-TU measurement confirms 1752 B / six words. |

## ABI evidence and cleanup

C7998's caller is func_801CAA00. At 801CB1AC/801CB1B0 it loads a0/a1
from the two-word packed input at sp+20/+24, then calls C7998 at 801CB1B4.
The callee's homes at sp+18/+1C and 64-bit switch now follow directly from
that single value. Keeping both high button cases 0x8000/0x4000 is essential.
A raw one-word permuter result masks the value to eight bits and was rejected.
The CAAA00 scratch draft still declares the old two-argument guess; it is
outside this task's chosen functions and was not edited. Its future integration
must pass the packed value using the recovered one-u64-argument ABI.

The clean C7998 draft uses a named index and explicit fallthrough comments.
No inline asm, #line, register keyword, new helper/global, padding object,
compiler flag, YAML, Makefile, boot, ovl_7E00 or status.csv changes are used.
Only the chosen C7998 and 17378 drafts change. Production source is unchanged.
Existing matched functions are checked by the linked image build.

## Linked rodata blocker

The first required clean build deliberately tested the C7998 integration. It
failed the overlay compression-slot check: ovl_7DF8 compressed to 308901 B
(308912 aligned) versus its fixed 308896 B slot. Direct image comparison then
identified a 0x90-byte rodata expansion. The generated 33-entry jump table is
inserted at 80294F10 while the original jtbl_80295430 remains in asm-owned data;
subsequent symbols shift by 0x90. The instruction comparison masks the table
relocation, so its zero cannot certify linked-image equality.

The owning TU has no .rodata subsegment in the current YAML. Assigning its
original rodata to C is a lead follow-up; YAML edits are explicitly outside
this task. No linker/assembler trick or code workaround was substituted.
Production C7998 was restored byte-for-byte to the incoming GLOBAL_ASM source,
and the readable one-u64-input candidate was saved as an IMPROVED draft.
The zero is an instruction-body result, **not** a claimed byte-exact integration.

## Search review and final verification

All 15 corrected searches ran 900.4–900.6 seconds with -j5 and exited normally
following the bounded interrupt. No additional acceptable result emerged.
The C7998 eight-bit-mask candidate loses valid high button cases and is rejected;
F720's redundant full-width mask is worse under independent instruction counts.
C85C0/B5534/B6528 weighted improvements worsen independent counts. 17378's retained improvement was reduced to the minimal setup-line join.
Search output directories and compiler products remain outside git.

The final clean rebuild after restoring production integration is recorded below.


`make clean && make extract && make all && make progress` passed (exit 0).
ROM and all three executable images are byte-identical:

- ROM: ba52e91b44450c548467044b26951353dc491e04
- main: 81736d32e8cda8f399b319a49250dff972b81af8
- ovl_7DF8: ea830aae50ff1422da60d4b7fdbfc29f03b1be39
- ovl_7E00: 2b01138a290212b9d886981e1196f7b6fb45ecdb

Final independent screens confirm C7998 at 0 words / 256 B and 17378 at
6 words / 1752 B, both in their complete owning TUs. Progress is unchanged.
`git diff --check` passes. No production source, status.csv, YAML, Makefile,
boot or ovl_7E00 changes remain. No task search/probe processes remain.
Generated progress documents match the incoming versions. Dependency symlinks
stay untracked; no ROM, object or permuter output tree is staged. No commits.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 70,628 (24.36%) | 70,628 (24.36%) | 0 | 195 | 0 | 314 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 31,204 (21.67%) | 31,204 (21.67%) | 0 | 90 | 0 | 147 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 30,956 (22.53%) | 30,956 (22.53%) | 0 | 105 | 0 | 146 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
