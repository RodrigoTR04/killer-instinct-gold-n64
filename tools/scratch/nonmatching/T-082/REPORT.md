# T-082 — sol-A28: decomp-permuter

**4 MATCHED (1,096 bytes), 3 IMPROVED drafts, 17 UNCHANGED (including six conditional family-A siblings).**
No commits. Installed the external tool in the shared gitignored tools/ext
location and its dependencies into the shared repo .venv. Local ROM and tools
were symlinked from the authorized project checkout; no ROM was copied into git.

Read TRACKING, latest WORKLOG, toolchain.md, Makefile, the HTML tool list, and
T-067/T-071/T-072/T-077 reports before searches. Used IDO 5.3 -O2 -mips2 via
asm-processor with the exact Makefile game flags. The helper in tools/permuter
builds a preprocessed TU-prefix context with other definitions stripped to
prototypes and assembles the original splat function plus late rodata.

Each of the 18 listed representatives received a local random search with a
900-second wall-clock cap, one worker each, concurrently; searches stop early
on zero, or when a separately checked cleanup completes the match. No network
workers/subagents. Used --stack-diffs --stop-on-zero --best-only --better-only.
The parser normalizes source lines before its initial score. This sometimes
loses an incoming draft's scheduling improvement; the original draft is kept
unless the cleaned candidate improves independently checked instruction words.

Permuter penalties and differing-word counts are distinct. Word checks mask
only real ELF relocation fields and include absolute body-length difference.
Promoted candidates were checked inside complete owning TUs and verified by
resolved full-image/ROM comparisons. Scratch improvements are diagnostic,
not behavior certification. Mutation scores can improve while semantics
regress: e.g. C7998's low-score `& 0xFF` candidate eliminates high-button
cases and is rejected. External-type rewrites are not adopted blindly.

## Winning changes and cleanup

- B9B4: initial parser formatting puts each matrix call on its own line; no
  expression changes. 316 bytes.
- B1EC: ordinary named s32 zero temporary, initialized before the call, fixes
  separate load/store address materialization. Replacing it with literal zero
  loses the match; this small remaining oddity is deliberate. 64 bytes.
- C7CD0: inline the replay-byte read at its call rather than snapshotting it
  earlier. No intervening call or aliasing store modifies the byte. Removed
  the unused local and permuter's empty statement, flattened the assignment
  chain and formatted the else-if; match retained. 380 bytes.
- AEE4: permuter narrows the quit flag to unsigned short (cleaned to u16),
  removing both quit-constant register misses. Independent cleanup changes
  the opaque client object from 12 to 8 bytes, recovering its sp+0x48 address.
  Evidence: boot client at D_8000BF48 precedes its queue at D_8000BF50; the
  registration routine func_80001EF4 ignores this first pointer entirely.
  The 8-byte local has no initialized/read contents. Added its correct void
  prototype. No padding/inline asm/#line/register workaround. 336 bytes.

## Per-function outcomes

Best raw permuter penalties include rejected candidates. The word column is
the retained C result; 0 for promotions includes linked verification. AA98/AAEC
start at 10 here: the old nine emitted mismatches also omit one target word.
The six extra family-A siblings were conditional transfer targets, not separate
random searches; no representative solution was found.

| Function | Best raw permuter penalty | Result | Words old→final | Winning change / disposition |
|---|---:|---|---:|---|
| func_801BF720 | 60 | UNCHANGED | 2→2 | No retained improvement; default return register remains. |
| func_801BF914 | 105 | UNCHANGED | 2→2 | No improvement; default register/return delay slot remains. |
| func_801C4E38 | 28 | UNCHANGED | 2→2 | No improvement; switch spill/reload slot remains. |
| func_801B6528 | 95 | UNCHANGED | 3→3 | Lower weighted score has more differing words; retained 3-word draft. |
| func_801B695C | 26 | UNCHANGED | 4→4 | No improvement; 0x30 versus 0x28 frame remains. |
| func_801C5064 | 20 | UNCHANGED | 4→4 | Recovered the existing 4-word draft after normalization; no further improvement. |
| func_801C7998 | 5 | UNCHANGED | 6→6 | Best raw score changes button semantics with &0xFF; rejected. |
| func_801C7CD0 | 0 | MATCHED | 6→0 | Inline replay-byte read at call; cleaned unused local/empty statement. |
| func_801C6A80 | 180 | UNCHANGED | 8→8 | Lower weighted candidate has more differing words; retained 8-word draft. |
| func_801B2010 | 1180 | UNCHANGED | 14→14 | No useful prefix solution; lower weighted candidates worsen word count. |
| func_8002AEE4 | 5 | MATCHED | 3→0 | u16 quit flag, then independently recover 8-byte client object; final match. |
| func_8002B1EC | 0 | MATCHED | 4→0 | Named zero temporary before osAiGetLength. |
| func_80017378 | 190 | UNCHANGED | 8→8 | No improvement; loop endpoint/increment scheduling remains. |
| func_8002AA98 | 10 | IMPROVED | 10→2 | Explicit narrowed s16 temporary; remaining mflo v0 versus a2 (2 words). |
| func_8002AAEC | 10 | IMPROVED | 10→2 | Explicit narrowed s16 temporary; remaining mflo v0 versus a2 (2 words). |
| func_8002B9B4 | 0 | MATCHED | 10→0 | Initial parser formatting: separate matrix-call lines. |
| func_8002A900 | 135 | UNCHANGED | 15→15 | Lower weighted score worsens aligned word differences; retained existing draft. |
| func_8002F45C | 193 | IMPROVED | 20→13 | Extra key-pointer temporary; removed dead if(0). Retained penalty-253 candidate (13 words), rather than raw best. |
| func_801B21B4 | — | UNCHANGED | 14→14 | No family-A solution to transfer; sibling draft retained. |
| func_801B2358 | — | UNCHANGED | 14→14 | No family-A solution to transfer; sibling draft retained. |
| func_801B24FC | — | UNCHANGED | 14→14 | No family-A solution to transfer; sibling draft retained. |
| func_801B26A0 | — | UNCHANGED | 14→14 | No family-A solution to transfer; sibling draft retained. |
| func_801B2844 | — | UNCHANGED | 14→14 | No family-A solution to transfer; sibling draft retained. |
| func_801B29E8 | — | UNCHANGED | 14→14 | No family-A solution to transfer; sibling draft retained. |

## Retained drafts and artifacts

AA98 and AAEC improve 10→2 words (the earlier nine-word metric omitted the
missing instruction word). Both retain 84/84 bytes. The raw AA98 chain of two
copies simplifies to the same named s16 temporary used for AAEC. Their last
two words are mflo v0 / dependent shift versus target a2.

F45C improves 20→13 words, 404/404 bytes. Its extra savedKey pointer and later
key assignment must remain: collapsing either alias returns to 20 or 22
words. Removed the dead if(0) and retained the owning TU's list declaration
through a layout-compatible typed view. This temporary is a scratch oddity,
not promoted C. All three final drafts were independently checked in their
complete owning TUs through asm-processor; these exact word counts agree.

The four matched drafts were deleted from T-024 (AEE4, B1EC, B9B4) and T-030
(C7CD0). Three improved drafts remain in T-024. New reviewable files are
only tools/permuter/{import_fn.py,README.md} and this T-082 directory
(REPORT.md, results.json, check_candidate.py). No bulky generated output is
included. results.json records all 18 run durations and penalties. Four
searches stop early on zero or checked cleanup; the other fourteen terminate
at the 900-second cap (timeout exit 137). No permuter processes remain.

No SDK TUs belonging to T-078/T-080, boot, ovl_7E00, YAML, Makefile,
status.csv, TRACKING or WORKLOG were edited. Generated progress documents
were restored after recording their output. Local dependency symlinks remain
untracked and must not be staged. No commits.

## Final verification

`make clean && make extract && make all && make progress` **passed (exit 0)**.
This includes the final C simplifications and correct registration prototype.
ROM and all executable images are byte-identical:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

Helper import/assemble/compile smoke checks passed for all 18 representatives;
the final helper was additionally imported and debug-scored on BF914.
Shared .venv `pip check` and `git diff --check` passed.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 71,652 (22.45%) | 71,652 (22.45%) | 0 | 268 | 0 | 294 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 45,004 (25.98%) | 45,004 (25.98%) | 0 | 123 | 0 | 167 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 18,180 (13.23%) | 18,180 (13.23%) | 0 | 145 | 0 | 106 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
