# T-126 — sol-A44

Partial result: `func_801C7A98` promoted, **568 B (0.196% of 289,876 B)**.
The 2,030 B target was not reached. All eleven remaining assigned drafts had
a bounded structural pass; no further zero was found. No artificial branches,
register bindings, padding, ROM edits, toolchain edits or subagents were used.

## Pool migration

The original 90 regular string objects occupy 0x80294F10–0x80295430,
inside the existing complete 1BD90 .rodata range. Converted them to ordered
`const` C arrays, preserving duplicate objects and the five leading spaces
in D_802953A0 (splat had rendered this string as nine words). The exact T-124
function body now replaces its GLOBAL_ASM. Deleted the promoted T-030 draft.

Changed all 90 `force_migration:True function_owner:func_801C7A98` hints to
`force_not_migration:True`. Simply removing ownership is insufficient:
splat automatically migrates directly referenced strings into other remaining
GLOBAL_ASM functions, producing duplicate definitions against C. Explicit
non-migration leaves the complete regular pool C-owned while their original
late floating constants and C7998's jump table retain normal ownership.
No YAML change was needed. In include/frontend.h, the three existing string
externs (D_802952E0/52FC/531C) now have const-qualified element types to agree
with their definitions. Other function bodies were left unchanged.

## Per-function results

Counts include relocation-masked positional words and missing/extra words.
Compiled/original sizes are bytes; drafts are not promotions.

| Function | Before → after words | Final size | Result / diagnosis |
|---|---:|---:|---|
| func_801C7A98 | 0 → 0 text | 568/568 | Promoted after pool migration. |
| func_801C4240 | 126 → 126 | 1344/1344 | Unchanged. Scale-result assignment, FP spill elimination and packet order tried; FP lifetimes/scheduling remain. |
| func_801C9698 | 135 → 135 | 1148/1148 | Reconciled draft's array view and removed conflicting externs for C-owned strings; now measures in full TU. Tried FP alpha, colour widths, cached FP positions, extracting stats-text call, count-pointer and addition ordering. Frame/FP hoisting and saved registers remain. |
| func_801B0668 | 154 → 154 | 984/984 | Unchanged. Angle precision/lifetime, pre-scaled sine, state increment forms; FP call/frame allocation remains. |
| func_801BBE88 | 150 → 147 | 808/808 | Saved improved T-023 draft: command-word order plus statement joins. Separate command scopes/cursors and late height-pointer assignment were worse. Command temporary allocation remains. |
| func_801C1434 | 132 → 132 | 720/720 | Unchanged. Player widths, flag reloads and explicit score temporaries; input homing and score ABI/scheduling remain. |
| func_8001346C | 165 → 165 | 704/704 | Unchanged. Separate transform flag, direct palette-array references and indexed clearing; measured declaration fallback due existing legacy pointer prototypes. |
| func_8001D47C | 141 → 134 | 744/748 | Saved T-022 draft: u8 palette parameter and advancing source cursor. Pixel/level widths tried; still short one instruction and allocator differences. Declaration fallback due existing D_8004CE90 view. |
| func_801B6BD8 | 153 → 141 | 620/628 | Saved T-029 draft: accumulate first row directly in count. Other first/second/count lifetime forms, helper x type and shade/offset widths tried; count lifetime/frame scheduling remains. |
| func_801B1DE4 | 111 → 111 | 556/556 | Unchanged. Real completion-block exits, distance placement and packet cursor lifetime; allocator/call scheduling remains. |
| func_8002B22C | 74 → 70 | 380/380 | Saved T-024 draft: explicit end-of-buffer local. Pool pointer, start/end caching, address reuse, odd widths and previous-node placement tried. Target retains pool address in s1 and homes request address, unlike draft. |
| func_800300DC | 74 → 74 | 316/316 | Unchanged. Token/distance reuse, signedness, count width and copy-loop forms; saved output register and token/count allocation remain. |

## Bounded searches

Production-context baseline and structural sweeps used screen.measure with
four compiler workers. The sweeps covered 30 matrix-count/packet candidates,
35 small DMA/decoder candidates, 16 distinct command-scope candidates,
76 whole-band candidates, 30 further decoder candidates, 48 count-width
candidates, 36 DMA extent candidates and 18 name-render candidates.
Counts include baselines and diagnostic failures, not unique new algorithms.

Two 120-second declaration/layout searches: DMA 74→73 (superseded by the
70-word structural draft), decoder unchanged. Two 240-second permuter searches
used --stack-diffs --stop-on-zero --best-only --better-only, two workers each.
Their outputs did not produce additional matches or improve the retained
structural drafts on independent full-TU remeasurement. A decoder candidate's
redundant XOR-zero was removed before measurement, never adopted. The DMA
permuter import needed a minimal equivalent declaration context because the
import helper stripped required libaudio array typedefs; full TU remained the
independent authority. Temporary permuter/dependencies were installed only
under /tmp; shared tools/ext and .venv were never modified.

Search logs and disposable candidates are under /tmp/t126-* and are not build
inputs. The pool evidence from T-115 remains applicable. The matched C function
and complete pool were already confirmed by a clean linked byte-identical
build before the final clean/extract/build/progress run.

## Final validation and follow-ups

`make clean && make extract && make -j8 && make progress` completed with exit 0.
All three executable images and the ROM match their original hashes.
`docs/functions.csv` marks func_801C7A98 T4. `git diff --check` passes.
Generated functions.csv, progress.html and progress-map.svg are retained;
README.md is restored as requested. TRACKING, WORKLOG and status.csv unchanged.

```
OK: rebuilt ROM is byte-identical to baserom.us.z64
| Total | 289,876 | 82,572 (28.49%) | 82,572 (28.49%) | 0 | 175 | 0 | 334 | 490 (167,316) |
```

Baseline M2 was 82,004 B / 333 T4; final M2 is 82,572 B / 334 T4.
Follow-up: all eleven nonmatched functions remain available, with the four
improved drafts above. The complete 1BD90 string pool is now C-owned, so
future C9698/C9B14/CAA00 promotions must use the existing string symbols and
must not reintroduce assembly migration of those objects. Their late numeric
constants still require the usual ownership/literal decision upon promotion.
