# T-050 — ovl_7DF8 polish round 5

Worker sol-B17. Uncommitted changes for lead review.

**45/45 functions attempted: 0 MATCHED, 16 IMPROVED, 29 UNCHANGED.** No C source integrations were made. All retained changes are in the listed functions’ original draft files.

## Method and limits

Each function received a bounded compile-and-compare experiment, rather than only a baseline screen. The general pass tested applicable typed table indexing, local declaration permutations, display-list postincrements, adjacent zero-store chains, and power-of-two shift expressions. The four requested clones additionally received coordinate materialization/order, early offset-load and scale-type experiments plus a rewrite using four named coordinates. None matched; no sibling was integrated. Missing callee prototypes were checked against existing C definitions; the Controller Pak error-handler calls were also inspected against the target assembly.

The row counts are fresh comparisons of HEAD drafts versus final drafts, with actual ELF relocation fields masked. **Score = differing aligned words + absolute instruction-count difference.** This includes missing/extra words, unlike the T-039 screen; consequently several old counts differ from the user’s screen counts. Compiled size is shown separately. A lower score is a draft improvement, not proof of correct relocations, rodata or matching. No zero scores occurred.

The first helper used T-047’s shared temporary filenames. A collision was observed; T-050/probe.py uses separate filenames, and every retained improvement and original baseline was recompiled with that helper before reporting.

## Per-function results

| Function | Draft | Result (score old→new) | C bytes old→new | Attempt / remaining issue |
|---|---|---|---|---|
| func_801BA088 | T-023 | UNCHANGED (132) | 540→540 | Coordinate ordering, scale widths, early offset loads and a four-coordinate rewrite did not resolve spills/scheduling. |
| func_801BA280 | T-023 | IMPROVED 131→129 | 532→532 | Load the shared y offset before the scale/coordinate calculations. Remaining instruction/register/layout differences prevent matching. |
| func_801BA470 | T-023 | UNCHANGED (133) | 552→552 | Same clone-family rewrites did not improve coordinate/spill scheduling. |
| func_801BA674 | T-023 | IMPROVED 136→135 | 564→564 | typed indexed tables. Remaining instruction/register/layout differences prevent matching. |
| func_801CC3BC | T-021 | IMPROVED 101→88 | 404→364 | remove spurious arguments to no-argument callees; reuse error parameter. Remaining instruction/register/layout differences prevent matching. |
| func_801B3B84 | T-025 | IMPROVED 131→114 | 440→552 | correct missing callee prototypes: func_801B19F0. Remaining instruction/register/layout differences prevent matching. |
| func_801CD1F0 | T-034 | UNCHANGED (107) | 452→452 | Declaration permutations leave the saved-register allocation and buffer cursor unresolved. |
| func_801C8004 | T-021 | UNCHANGED (110) | 444→444 | Declaration/order and shift forms compile but retain traversal/type/control differences. |
| func_801BBC84 | T-023 | UNCHANGED (112) | 508→508 | Shift forms and declaration permutations leave fire traversal and random-call scheduling unresolved. |
| func_801BD3FC | T-023 | UNCHANGED (145) | 440→440 | Callee declarations and local ordering leave 64-bit unpacking/history loads unresolved. |
| func_801B677C | T-029 | UNCHANGED (117) | 492→492 | Tested applicable declaration, cursor/store and shift forms; Division scheduling, normalized argument lifetimes and integer temporary registers differ. |
| func_801C2D34 | T-030 | IMPROVED 120→95 | 548→548 | baseline. Remaining instruction/register/layout differences prevent matching. |
| func_801C11F0 | T-023 | UNCHANGED (126) | 568→568 | Tested applicable declaration, cursor/store and shift forms; Digit buffer/float-bit union stack layout and call scheduling differ. |
| func_801AD568 | T-019 | UNCHANGED (128) | 560→560 | Tested applicable declaration, cursor/store and shift forms; Stack frame 0x28 versus target 0x40; display-command pointer lifetimes and scheduling differ. |
| func_801C2F5C | T-030 | UNCHANGED (128) | 556→556 | Tested applicable declaration, cursor/store and shift forms; Sprite/layout pointer lifetimes, callback arguments, frame (0x90 vs 0x60) and scheduling differ. |
| func_801AD7D8 | T-019 | UNCHANGED (132) | 544→544 | Tested applicable declaration, cursor/store and shift forms; 544-byte reconstruction versus 556-byte target; command-pointer increments/stores are folded, changing scheduling and registers. |
| func_801C9698 | T-034 | IMPROVED 136→135 | 1148→1148 | local declaration order. Remaining instruction/register/layout differences prevent matching. |
| func_801C1990 | T-023 | UNCHANGED (159) | 588→588 | Tested applicable declaration, cursor/store and shift forms; Stat-array comparisons, branch layout and 64-bit zero stores differ. |
| func_801BB258 | T-023 | UNCHANGED (138) | 556→556 | Tested applicable declaration, cursor/store and shift forms; Rendering-coordinate temporaries, stack spills, table loads and scheduling differ. |
| func_801B1DE4 | T-025 | IMPROVED 138→113 | 568→556 | correct missing callee prototypes: func_801AF5EC, func_801B19F0. Remaining instruction/register/layout differences prevent matching. |
| func_801BB594 | T-023 | UNCHANGED (140) | 580→580 | Tested applicable declaration, cursor/store and shift forms; Rendering-coordinate temporaries, stack spills, table loads and scheduling differ. |
| func_801AFFAC | T-025 | IMPROVED 140→129 | 580→568 | correct missing callee prototypes: func_801AFA80. Remaining instruction/register/layout differences prevent matching. |
| func_801BADEC | T-023 | UNCHANGED (144) | 580→580 | Tested applicable declaration, cursor/store and shift forms; Rendering-coordinate temporaries, stack spills, table loads and scheduling differ. |
| func_801BB024 | T-023 | UNCHANGED (148) | 600→600 | Tested applicable declaration, cursor/store and shift forms; Rendering-coordinate temporaries, stack spills, table loads and scheduling differ. |
| func_801B6BD8 | T-029 | UNCHANGED (153) | 628→628 | Tested applicable declaration, cursor/store and shift forms; Text helper float argument typing, saved count register, stack slots and scheduling differ. |
| func_801BEA74 | T-023 | UNCHANGED (154) | 676→676 | Tested applicable declaration, cursor/store and shift forms; 64-bit mixed-radix multiply/add sequencing and stack/register allocation differ. |
| func_801AD114 | T-019 | UNCHANGED (159) | 648→648 | Tested applicable declaration, cursor/store and shift forms; 648-byte reconstruction versus 628-byte target; control-flow layout, argument spills and registers differ. One m2c structured-exit goto remains in this draft only. |
| func_801B2B8C | T-025 | IMPROVED 193→189 | 756→884 | correct missing callee prototypes: func_801B19F0. Remaining instruction/register/layout differences prevent matching. |
| func_801B1A7C | T-025 | IMPROVED 218→206 | 668→596 | correct missing callee prototypes: func_801B1A14. Remaining instruction/register/layout differences prevent matching. |
| func_801B0A40 | T-025 | IMPROVED 168→163 | 700→684 | correct missing callee prototypes: func_801AFA80. Remaining instruction/register/layout differences prevent matching. |
| func_801C67CC | T-030 | UNCHANGED (171) | 704→704 | Tested applicable declaration, cursor/store and shift forms; Frame (0x60 vs 0x28), double lifetime/spills and unsigned-result conversion registers differ. |
| func_801C1434 | T-023 | UNCHANGED (176) | 736→736 | Tested applicable declaration, cursor/store and shift forms; 64-bit score loads/call ABI, branches and saved-register allocation differ. |
| func_801ACB1C | T-034 | UNCHANGED (176) | 756→756 | Tested applicable declaration, cursor/store and shift forms; ~130 lines; same logic. Target keeps the message pointer address in s0 and caches *msg in a0, keeps gfxStart on the stack (sp5C) rather than s0, frame is 0x60 (here 0x68), and disp |
| func_801BBE88 | T-023 | UNCHANGED (184) | 804→804 | Tested applicable declaration, cursor/store and shift forms; Display-list pointer/register allocation and command-store scheduling differ. |
| func_801C3AA0 | T-030 | UNCHANGED (206) | 908→908 | Tested applicable declaration, cursor/store and shift forms; Particle/random arithmetic, saved float/integer registers and vertex-store scheduling differ. |
| func_801B01EC | T-025 | IMPROVED 210→193 | 860→828 | correct missing callee prototypes: func_801AFA80, func_801AF5D4, func_801AF5EC. Remaining instruction/register/layout differences prevent matching. |
| func_801C90D4 | T-034 | UNCHANGED (219) | 1192→1192 | Tested applicable declaration, cursor/store and shift forms; DRAFT. Same instruction count (300); remaining diff is scheduling/register allocation around the first call's stack args and the fade-loop setup. D_80292698 is a u8 ***[] table (st |
| func_801BB7B4 | T-023 | UNCHANGED (220) | 960→960 | Tested applicable declaration, cursor/store and shift forms; Audio-handle loads/types, saved temporaries and branch scheduling differ. |
| func_801BAA78 | T-023 | IMPROVED 223→222 | 912→912 | local declaration order. Remaining instruction/register/layout differences prevent matching. |
| func_801C317C | T-030 | IMPROVED 226→225 | 940→940 | local declaration order. Remaining instruction/register/layout differences prevent matching. |
| func_801AF68C | T-025 | UNCHANGED (231) | 940→940 | Tested applicable declaration, cursor/store and shift forms; Callback dispatch and queue-compaction loop induction/unrolling, stack layout and temporary registers differ. |
| func_801B0668 | T-025 | IMPROVED 248→231 | 996→976 | correct missing callee prototypes: func_801AFA80. Remaining instruction/register/layout differences prevent matching. |
| func_801BD640 | T-023 | UNCHANGED (265) | 1100→1100 | Tested applicable declaration, cursor/store and shift forms; Font/matrix pointers, float/double temporaries, stack and scheduling differ. |
| func_801B3DB0 | T-025 | UNCHANGED (277) | 1344→1344 | Initialized-local declaration order, zero-store chains and coordinate shifts leave loop induction/unrolling unresolved. |
| func_801AFAA4 | T-025 | IMPROVED 292→290 | 1264→1264 | local declaration order. Remaining instruction/register/layout differences prevent matching. |

## Ownership and deleted drafts

No new rodata subsegments. Existing T-043 ownership remains unchanged. No drafts deleted, because no function matched. No inline assembly, register binding, padding, compiler-flag or build-system changes. No main, boot, ovl_7E00, status.csv, tracking or worklog edits.

Setup prerequisites are symlinks to /home/rodri/Projects/killer-instinct-gold-n64. ROM content was not copied into tracked files or committed.

## Validation

`make clean && make extract && make all && make progress` completed successfully (exit 0). ROM and all three linked images are byte-identical. `git diff --check` passed. No progress/status overrides were changed; matching totals are unchanged.

- ROM SHA1: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 49,928 (15.65%) | 49,928 (15.65%) | 0 | 320 | 0 | 242 | 437 (138,092) |
| boot | 8,468 | 8,108 (95.75%) | 8,108 (95.75%) | 0 | 1 | 0 | 20 | 99 (16,028) |
| main | 173,204 | 28,684 (16.56%) | 28,684 (16.56%) | 0 | 155 | 0 | 135 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 13,136 (9.56%) | 13,136 (9.56%) | 0 | 164 | 0 | 87 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
