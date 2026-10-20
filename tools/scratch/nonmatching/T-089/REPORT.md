# T-089 — sol-C33

**2 MATCHED (624 bytes), 4 IMPROVED drafts, 1 UNCHANGED. No commits.**

Read TRACKING, latest WORKLOG, Makefile, tools/permuter/README.md and the
T-082/T-085 reports before starting. Missing baserom.us.z64, ROMs, .venv and
tools/ext were symlinked from the authorized shared checkout. No ROM was copied
or added to git. Only the seven assigned functions and required declarations
were edited; boot, overlays, YAML, Makefile and status.csv were untouched.

## Results

Scores below are relocation-masked differing instruction words, including
body-length differences, rather than the permuter's weighted penalties.
All retained candidates have the original body size. Scratch improvements
remain diagnostic and are not claimed as behavior-validated functions.

| Function | Best retained words (old → final) | Result | Winning change / remaining difference |
|---|---:|---|---|
| func_8002F6F4 | 18 → 2 | IMPROVED | Reorder local declarations and snapshot the chain key after accumulating delay. Only the load/store offsets for the spilled step differ (sp+0x74 versus target sp+0x64). |
| func_80015F6C | 21 → 0 | MATCHED | Chain the first two 255 color assignments. Remove redundant XOR/arithmetic; ordinary multiline braces retain the match. 268 bytes. |
| func_8001E0B4 | 24 → 24 | UNCHANGED | Best raw candidate needs an empty conditional; removing it worsens the retained baseline. Declaration, boolean and layout probes found no honest improvement. |
| func_8002E4A0 | 33 → 2 | IMPROVED | Split loading the voice-list base from adding the record offset; remove the unused player local. Remaining base load/add use a0 instead of v0. |
| func_8002A4F0 | 53 → 31 | IMPROVED | Move the loop-index declaration ahead of the synth configuration; retain normalized multiline statements. Configuration/sequence-loop allocation remains. |
| func_800121C8 | 54 → 49 | IMPROVED | Equivalent mode comparison `!(mode < 2)`, combined with reordered independent pair stores and multiline layout. Reject empty-condition variants. |
| func_8001256C | 63 → 0 | MATCHED | Stage the low color in the command value, then form its upper copy; write render-mode command before its value. Preserve paired-store line placement. 356 bytes. |

## Search and cleanup

Used the shared decomp-permuter with IDO 5.3 -O2 -mips2 through asm-processor
and the existing import helper. One local worker per search, normally six
concurrent searches; no network workers or subagents. Searches use
`--stack-diffs --stop-on-zero --best-only --better-only -j 1` and 1800-second
caps. 15F6C stopped on zero after 99 seconds. 1256C stopped after 1708 seconds
when a separately checked hand cleanup reached zero. The five remaining
functions received a complete 30-minute search with intact bodies.

The helper's upstream regex can mistake nested blocks for other functions
when the draft has dense lines or a split function signature. Initial imports
lost the 121C8 definition and nested F6F4/E4A0 blocks; 15F6C also needed its
scalar-global and random-function declarations reconciled with its TU.
Discarded those inputs and restarted from temporary multiline inputs, with
single-line signatures. No helper changes were made. Final retained drafts
were freshly imported again: 2/2/31/49/24 words respectively for
F6F4/E4A0/A4F0/121C8/1E0B4, agreeing with independent TU-prefix compilation.

Additional hand passes explored declaration order, equivalent boolean and
pointer expressions, independent command-store order, and thousands of
semicolon/brace line layouts. Lower weighted penalties do not necessarily
improve word counts. Best raw weighted penalties included 32 (F6F4), 0
(15F6C), 305 (1E0B4), 10 (E4A0), 1038 (A4F0), 1480 (121C8), and 30
(1256C); these include rejected candidates. The final hand-cleaned 1256C
matches independently despite its best saved random candidate being nonzero.

Removed empty branches, redundant XOR/constant arithmetic and unused locals.
No inline assembly, #line or register keyword was introduced. The remaining
chain-key snapshot and split voice-base assignment are ordinary local values.
1256C deliberately keeps the two command/value store pairs on shared lines;
a source comment explains the IDO scheduling dependence. Its staged color
store is equivalent to duplicating the 16-bit color and uses an unsigned
command word for the left shift.

15F6C needed the existing later audio-call declarations reconciled with its
correct void/pointer prototypes. This is a declaration-only change; existing
callers remain byte-identical. Both promotions passed complete owning-TU
relocation-aware checks and linked image/ROM verification. F6F4 and 121C8
also pass complete-TU checks at their retained nonzero counts. A4F0 and E4A0
retain the pre-existing drafts' alternate global views, which conflict with
later TU declarations; their scores use the helper's TU-prefix context and
are not integration claims.

Deleted the matched T-020/func_80015F6C.c and T-033/func_8001256C.c drafts.
Generated search directories, candidates, logs and probe scripts remain only
under /tmp/kig-t089, outside the tracked tree. No permuter output directory
is included in the deliverable.

## Final verification

`make clean && make extract && make -j6 all && make progress` passed (exit 0).
ROM and all executable images remain byte-identical:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

`git diff --check` passes. Generated docs/functions.csv and docs/progress.html
were restored after recording this output. Setup symlinks remain untracked;
do not stage them. No search/probe processes remain.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 54,832 (18.92%) | 54,832 (18.92%) | 0 | 245 | 0 | 264 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 28,184 (19.57%) | 28,184 (19.57%) | 0 | 100 | 0 | 137 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 18,180 (13.23%) | 18,180 (13.23%) | 0 | 145 | 0 | 106 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
