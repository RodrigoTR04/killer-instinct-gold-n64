# T-100 — sol-C37

Five matches integrated (1,596 bytes), six improved drafts retained, nine unchanged. No commit made.

## Function results

Words are relocation-masked differing instruction words, including size differences. Sizes are candidate/target bytes. Initial words use the requested screen except 8001373C, whose refreshed starting draft was already 48 words (requested screen: 66).

| Function | Result, old → new words | Final bytes | Diagnosis / retained change |
|---|---|---:|---|
| func_8002F5F0 | MATCHED 50 → 0 | 212/212 | Incoming typed voice directly; free-list head assignment in each branch removes extra pointer lifetime/instructions. |
| func_8001AA90 | IMPROVED 63 → 60 | 488/496 | Reuse incoming float for initial angle; eight-byte deficit remains around angle/control-flow temporaries. |
| func_8001373C | IMPROVED 48 → 36 | 256/256 | Reuse arg1 for squared distance, literal constants; remaining floating-point scheduling/register differences. |
| func_80015450 | IMPROVED 68 → 66 | 328/324 | Token-preserving line layout; extra instruction and allocation around loop remain. |
| func_80029AB0 | MATCHED 69 → 0 | 304/304 | Fully indexed effect accesses rather than advancing pointer; complete effect layout. |
| func_801BE540 | UNCHANGED 69 | 280/288 | Target homes/reloads matrix argument; cursor/table allocation and signed glyph indexing remain. |
| func_80023EF0 | UNCHANGED 71 | 296/312 | Facing branch/frame/traversal structure remains. Rejected field widening changed record stride. |
| func_801B465C | UNCHANGED 71 | 332/328 | Selection temporaries and saved-register allocation remain. |
| func_801C0610 | MATCHED 71 → 0 | 372/372 | Scoped graphics-command temporaries, store order and matrix address typing. |
| func_801C2ADC | IMPROVED 72 → 71 | 600/600 | Line layout; remaining call scheduling/register differences. |
| func_801C6D40 | MATCHED 74 → 0 | 300/300 | Reuse tick argument, byte phase updates, correct callee arities, 0.6 literal; clamp tick before update. |
| func_800300DC | UNCHANGED 76 | 312/316 | Decoded token/distance reuse, backreference loop and saved output register remain. |
| func_800287D4 | UNCHANGED 77 | 560/556 | Particle/RNG loop allocation remains; rejected inequality substitution could change changing-count behavior. |
| func_80030220 | UNCHANGED 77 | 340/348 | Endpoint/count saved registers and final division remain. |
| func_801BB464 | IMPROVED 78 → 76 | 308/304 | Precompute y before mirror branch; one extra instruction remains. |
| func_801BE790 | UNCHANGED 78 | 372/384 | Table initializer base and persistent pointers/constants remain. |
| func_801C49A8 | UNCHANGED 83 | 548/548 | Frame/mode/flag spills and rendering-call scheduling remain. |
| func_801BA884 | UNCHANGED 86 | 496/500 | Coordinate spills and both rendering-call sequences remain. |
| func_801BED0C | MATCHED 86 → 0 | 408/408 | Eight-byte score entries, normalized name reused in text, subtraction retained in u64 index arithmetic. |
| func_800245B4 | IMPROVED 87 → 83 | 348/352 | Preserve rangeStart, reuse incoming start for current entry data; traversal/allocation deficit remains. |

## Integration and measurement

All five matches replace GLOBAL_ASM in their owning translation units; corresponding drafts are deleted. Full clean build verifies their actual linked bytes. Necessary declarations were adjusted without changing other function bodies. func_801C0610 retains an old-style single-s32-argument definition: an existing caller passes an unused second argument, while declaring that parameter introduces an unwanted argument home store. func_8002F5F0 uses a nonprototype forward declaration to accommodate the existing caller's alternate voice view.

The six improved drafts are updated in place. func_8001373C remains assembly-owned: its force_migration hints are untouched; the improved draft uses literals. No linker undefined-symbol changes survived regeneration.

Draft measurements use the full owning TU where possible. 8001373C, 80015450, 800287D4 and 801BE790 require prefix context; 800300DC and 800245B4 require declarations-only context because of existing conflicting draft declarations. These provisional scores do not establish integration matches. baseline.json, structure.json, experiments.json and final.json record diagnostics; probe.py and sweep.py support reproduction. The restored 80023EF0 draft was independently rechecked at 71 words, 296/312 bytes.

Original instruction sequences were inspected before declaration, structural and line-layout sweeps. Permuter searches used -j5, --stack-diffs, --stop-on-zero, --best-only and --better-only. Approximately 20 minutes on 8001373C and 15 minutes each on 801C2ADC/801C49A8 produced weighted-score reductions, but no acceptable improvement over the retained clean drafts. Duplicate masks in a 1373C candidate and artificial do/while wrappers were rejected. Searches on the subsequently matched F5F0/C0610/29AB0 were stopped after independent structural matches. All search output stays under /tmp; no permuter output directories are included.

The apparently improved 80023EF0 experiment was rejected because widening the facing field changed the point-record stride from 12 to 16. Its original draft was restored. No inline assembly, #line or register keyword was introduced.

## Final validation

`make clean && make extract && make all && make progress` completed successfully, in that order. The rebuilt ROM and all images are byte-identical:

| Artifact | SHA-1 | Bytes |
|---|---|---:|
| ROM | ba52e91b44450c548467044b26951353dc491e04 | |
| main | 81736d32e8cda8f399b319a49250dff972b81af8 | 239824 |
| ovl_7DF8 | ea830aae50ff1422da60d4b7fdbfc29f03b1be39 | 957392 |
| ovl_7E00 | 2b01138a290212b9d886981e1196f7b6fb45ecdb | 153904 |

Generated docs/functions.csv and docs/progress.html were restored after recording progress. status.csv, Makefile, YAML, boot and ovl_7E00 sources were not edited. Local dependency symlinks remain untracked and must not be committed.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 65,028 (22.43%) | 65,028 (22.43%) | 0 | 210 | 0 | 299 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 30,092 (20.90%) | 30,092 (20.90%) | 0 | 92 | 0 | 145 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 26,468 (19.26%) | 26,468 (19.26%) | 0 | 118 | 0 | 133 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
