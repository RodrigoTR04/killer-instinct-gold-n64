# T-076 — sol-A26: ovl_7DF8 structure-first round 2

**0 MATCHED, 9 IMPROVED, 1 UNCHANGED.** All ten functions inspected and probed.
Changes are uncommitted and confined to the assigned scratch drafts and this
report/tool directory. No production source, declarations, YAML, Makefile or
status.csv changes. No drafts deleted; no GLOBAL_ASM replacements.

Scores are relocation-masked positional differing instruction words plus the
instruction-count delta, using the T-056/T-070 method. Baselines were reproduced
in this checkout. Retained scores were also measured from complete owning TU
objects compiled through production asm-processor/IDO flags; those scores agree
with the declaration-prefix probe. These are diagnostic scores, not matching or
behavior-validation claims.

| Function | Result | C / original bytes | Retained change and remaining differences |
|---|---|---:|---|
| func_801B0668 | IMPROVED **159→156** | 984 / 984 | Ordinary postincrement display-list allocation. Signed state locals, explicit byte-increment narrowing, matrix union/alignment and separated cosine temporaries did not improve it. Frame remains 0xB8 vs 0xA0, with different state-address materialization, state temporaries, FP spills and command scheduling. |
| func_801C4240 | UNCHANGED **167** | 1344 / 1344 | Inspected tick arithmetic, projected-distance output, coordinate outputs and depth lifetimes. Projection records, tick widths and integer divisors did not improve it. A three-slot depth array scored 164 but was discarded: the unused middle slot had no established record interpretation. Projection/depth stack placement and global-address/register choices remain. |
| func_801BD640 | IMPROVED **195→191** | 1068 / 1068 | Reused the running x float before and after guTranslate; full-width unsigned current-character temporary. This follows the target's continuous f20 lifetime. Matrix pointer representations and alpha caching did not improve it. Saved-register assignment, matrix-base spill, packed color temporaries and loop constant scheduling remain. |
| func_801B0CDC | IMPROVED **209→204** | 1336 / 1332 | Ordinary display-list allocation postincrements. Tried aligned matrix scratch representations, angle-spill simplification and shared zero value. Still one instruction too long; scratch matrix/float spills, command scheduling and state-address allocation differ. Kept unsigned tick/40 division exactly as recovered previously. |
| func_801B132C | IMPROVED **240→237** | 1144 / 1168 | Narrowed the sine-derived temporary to s8 at assignment, matching the target's immediate signed-byte truncation. Result reuse, countdown traversal, alpha widths and divisor spelling did not improve it. FP/constant lifetimes, loop allocation and tail scheduling still differ; candidate remains 24 bytes shorter. |
| func_801C1C34 | IMPROVED **262→242** | 1224 / 1244 | Advance both byte-table pointers directly while finding maxima instead of indexing each load. Player/max widths and buffer-size variants were rejected. Register lifetimes, local buffer/float stack positions and maxima-loop lowering remain; candidate is 20 bytes shorter. |
| func_801B3DB0 | IMPROVED **277→255** | 1360 / 1360 | Recovered [entry][player] two-column halfword/float arrays, with natural indexed initialization. Reconciled four draft extern widths with declarations later in the owning TU. D_8012834B remains declared s8 as in that TU; unsigned-character lvalue access preserves this function's lbu semantics. Tried mode widths and multiline/compact layouts. Still differs in pointer endpoints/induction, saved registers, local spills and initialization scheduling. |
| func_801BDA6C | IMPROVED **300→289** | 1336 / 1320 | Ordinary display-list allocation postincrements. Tried common command cursor, shared double advance and typed matrix-base representations. Frame remains 0x120 vs 0xD8; glyph/highlight FP lifetimes, packed color handling and saved-register allocation differ. Candidate is 16 bytes longer. |
| func_801C7310 | IMPROVED **301→281** | 1264 / 1276 | Explicit g/h/t branch chain and indexed initial list-base expression reproduce more of the original traversal setup than the switch. Preserved countdown postdecrement and the existing final D_802D39CE=1 stop transition. Audio-state address lifetimes, float constants/registers and dispatch scheduling remain. |
| func_801BF190 | IMPROVED **303→284** | 1256 / 1256 | Compare table-header addresses as u32, matching the target's unsigned pointer comparison against D_80127DA8. Tried byte/aggregate/memcpy name copies and for-loop forms; rejected them. The target uses swl/swr for the unaligned four-byte name copy; the retained honest byte copy and stack/saved-register allocation still differ. |

## Method and reproducibility

Read TRACKING, latest WORKLOG, Makefile, and T-070/T-056/T-067/T-069 before
probing. Missing baserom.us.z64, ROMs, .venv and tools/ext were symlinked from
`/home/rodri/Projects/killer-instinct-gold-n64`. No ROM was copied or staged.

Bounded structural experiments covered matrix alignment and indexing, shared
versus separate float/command lifetimes, byte narrowing, array dimensions,
loop induction and exit tests, real projection-output types, name-copy lowering,
and command allocation. Ordinary statement/braces/comma line layouts were also
tried; none reached scheduling-only proximity. The final paired-array B3DB0 draft
uses multiline source. No inline assembly, #line, register variables, compiler
flags or output rewriting were used. Rejected candidates and bulky logs remain
outside the repository under /tmp.

Run from the repository root after extraction:

```
.venv/bin/python tools/scratch/nonmatching/T-076/check_drafts.py
```

The helper compiles each retained draft in a separate complete TU and measures
its resulting function. One scratch-only declaration reconciliation is required:
T-071 added a second anonymous render-context type after C1C34's pragma. The
helper omits the later `extern T030Render2D34 D_802C9F70`, using the draft's
identically laid-out declaration (0xF8 padding followed by matrices) throughout
that temporary TU. Neither production declaration nor any other function is
edited. B3DB0's four formerly conflicting signedness declarations are reconciled
in the retained draft itself, so it needs no helper substitution.

`probe.py`, `tu.py`, and `ad.py` are the small T-070 probe tools with isolated
/tmp/t076 paths. The full-TU checker prints both prefix and full-TU scores,
compiled size, and original size. There are no deleted drafts.

## Final validation

`make clean && make extract && make all && make progress` passed after the
retained changes. All ten full-TU scratch compilations also passed; full-TU
scores agree with the table above. `git diff --check` passed.

- ROM SHA1: `ba52e91b44450c548467044b26951353dc491e04`, byte-identical.
- main: `81736d32e8cda8f399b319a49250dff972b81af8`, byte-identical.
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`, byte-identical.
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`, byte-identical.

Progress remains unchanged because the improved drafts remain assembly-backed.
Generated progress files and linker undefined-symbol lists have no net changes.
No commits were made.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
| Total | 319,100 | 69,508 (21.78%) | 69,508 (21.78%) | 0 | 273 | 0 | 289 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 43,240 (24.96%) | 43,240 (24.96%) | 0 | 127 | 0 | 163 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 17,800 (12.95%) | 17,800 (12.95%) | 0 | 146 | 0 | 105 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
