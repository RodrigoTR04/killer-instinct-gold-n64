# T-062 — sol-A22: ovl_7DF8 finishing pass

**1 MATCHED (200 bytes), 3 IMPROVED, 2 UNCHANGED.** Changes are uncommitted for lead review. All six requested functions were probed with IDO 5.3 production flags in their owning translation unit's preceding C context. Over 7,000 variants were screened; scores below use T-056/T-060's relocation-masked differing-word metric, not a claim of linked equivalence for drafts.

| Function | Result | Final bytes / target | Findings and remaining differences |
|---|---|---:|---|
| func_801C4E38 | UNCHANGED (2) | 556 / 556 | Tested meaningful mode/player/table/callback locals, scalar and aggregate local forms, 8/16/32/64-bit switch expressions, callee/callback return declarations and argument widths. Still spills/reloads v0 at sp+0x18 instead of target sp+0x1C. No artificial padding retained. |
| func_801B6528 | UNCHANGED (3) | 596 / 596 | Tested declaration permutations, typed card/matrix parameters, unused fourth-parameter types and omission, local/field/return widths, branch-scoped index locals, guTranslate declarations, cursor updates and address locals. Reload of the card pointer still uses a0 rather than target a2, with two dependent loads differing. |
| func_801C35D8 | IMPROVED 5→4 | 384 / 384 | Unsigned byte-offset pointer arithmetic reproduces the target's addition operand order: `(T030Cloud *)((u32)offset + (u8 *)arg1)`. Tried initialization placement, all 5,040 permutations of seven local declarations, command-pointer/field types, loop types and callee declarations. Initial display-list command and loop-initialization scheduling remain. |
| func_801BFB40 | MATCHED (8→0) | 200 / 200 | `D_802D37EA[0] = D_802D37EA[1] = 0` reproduces the byte-base register and temporary numbering. Corrected the final chained reset's symbol order after linked comparison exposed relocation differences hidden by the screening metric. The actual one-argument `func_801ADAD4(s32)` declaration/call also matches; removed the draft's unnecessary extra arguments. Integrated into ovl_7DF8_13FF0.c. |
| func_801B446C | IMPROVED 34→31 | 292 / 292 | Declare both byte tables unsigned, consistent with the TU's existing matched selection function. Tested flag/bit/choice/position widths including 64-bit locals, update forms, struct/array pointer views and flag expression order. Target still retains &D_802C8CE0 in t0; base retention and scheduling differ. |
| func_801C7CD0 | IMPROVED 63→34 | 380 / 380 | Use the byte argument directly; call func_801C7A98 with no argument; correct music-call arity and remove unused extra func_801CD038 arguments. The replay state is two u64 values of 0x1000, producing the target's explicit high/low word stores. Tested mode/replay widths, global pointer/array views, reset order and replay initialization forms. Global pointer and mode/replay register allocation, redundant narrowing and scheduling remain. |

## Draft disposition and scope

Deleted: `tools/scratch/nonmatching/T-023/func_801BFB40.c`.

Improved in place:
- `T-030/func_801C35D8.c`
- `T-029/func_801B446C.c`
- `T-030/func_801C7CD0.c`

The other two drafts are unchanged. Production edits are confined to replacing func_801BFB40's GLOBAL_ASM and its local declarations in `src/ovl_7DF8/ovl_7DF8_13FF0.c`. No T-061 function, other image source, YAML, Makefile, status.csv, tracking or worklog was edited. No inline assembly, register bindings or artificial padding were used. ROM/tool prerequisites are symlinks to the main checkout; ROM data was neither copied nor committed.

## Probe tools and evidence

`probe.py`, `tu.py`, and `ad.py` are local copies of the prior tools. Temporary compiler files use `/tmp/t062-*`; no build binaries are delivered. The experiment scripts retain the tested variants:

- `round1.py`, `spill2.py`, `spill3.py`, `card2.py`: spill/parameter/local/callee sweeps.
- `pair.py`: byte-clear and pair-store permutations; zero score at candidate 385.
- `cloud.py`, `cloud2.py`, `cloud3.py`: pointer arithmetic, initialization, declarations and type sweeps.
- `flags.py`, `arrays.py`, `replay.py`, `shapes.py`, `wide.py`: global access forms, declaration widths and replay reconstruction.

Run from the repository root. Scripts that use incoming draft text expect that version of the draft; the matched pair draft is now deleted. Logs in `logs/` preserve the actual run results (including an initial shapes sweep stopped by a script lookup error, then corrected and rerun). `integrate.py` records the mechanical integration used before correcting the music prototype and reset order.

## Final verification

`make clean && make extract && make all && make progress` completed successfully (exit 0). The rebuilt ROM is byte-identical to baserom, SHA1 `ba52e91b44450c548467044b26951353dc491e04`. All image checks passed:

- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

The whole overlay comparison validates that all previously matched functions still match with the new declaration context. `git diff --check` passed. Generated docs/functions.csv and docs/progress.html were restored after recording the following progress output; generated linker files have no final changes. status.csv remains untouched for the lead.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 56,044 (17.56%) | 56,044 (17.56%) | 0 | 297 | 0 | 265 | 437 (138,092) |
| boot | 8,468 | 8,108 (95.75%) | 8,108 (95.75%) | 0 | 1 | 0 | 20 | 99 (16,028) |
| main | 173,204 | 31,772 (18.34%) | 31,772 (18.34%) | 0 | 145 | 0 | 145 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 16,164 (11.76%) | 16,164 (11.76%) | 0 | 151 | 0 | 100 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |

