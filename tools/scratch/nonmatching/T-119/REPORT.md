# T-119 — sol-B38: func_8001B134 integration

Promoted func_8001B134 (984 bytes) into src/main/main_2FF0.c using
T-117's exact draft from T-022/func_8001B134.c. Retained the meaningful
else around the rotation path and reused the existing T117Part type and
shared declarations. Deleted the integrated draft. No commits.

Removed the four force_migration/function_owner symbol lines for
D_80048998, D_800489A0, D_800489A8 and D_800489B0. Their only C user,
the already-matched func_8001B50C, now uses plain double literals:
3.14159 / 180.0 in both trigonometric arguments. Removed its four externs.
B134 itself uses the draft's ordinary float literals; the four doubles
belong to B50C, which emits them in the original pool slots. No replacement
asm owner was needed. Full linked-image equality verifies B50C and all other
previous matches retain their bytes, including the pool layout.

Retained regenerated linker_scripts/ovl_7DF8.undefined_syms.txt and
linker_scripts/ovl_7E00.undefined_syms.txt changes: each drops the four
removed symbols. No main undefined-symbol change was needed.

Read TRACKING, latest WORKLOG, Makefile, main YAML and symbol addresses,
and reports T-117, T-046, T-045 and T-052. Missing prerequisites were
symlinked from /home/rodri/Projects/killer-instinct-gold-n64. ROM contents
were never copied or committed. No boot/overlay source, YAML, Makefile,
status.csv, TRACKING or WORKLOG edits; no other worker's functions edited.
Honest C only; no compiler changes, assembly barriers or padding.

## Final verification

`make clean && make extract && make all && make progress` passed (exit 0).
ROM and all three executable images match:

- ROM: ba52e91b44450c548467044b26951353dc491e04
- main: 81736d32e8cda8f399b319a49250dff972b81af8
- ovl_7DF8: ea830aae50ff1422da60d4b7fdbfc29f03b1be39
- ovl_7E00: 2b01138a290212b9d886981e1196f7b6fb45ecdb

`git diff --check` passed. Generated progress documents were restored after
recording the table, leaving them for the lead to regenerate. Net gain:
1 T4 function / 984 bytes.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 73,980 (25.52%) | 73,980 (25.52%) | 0 | 190 | 0 | 319 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 33,776 (23.46%) | 33,776 (23.46%) | 0 | 87 | 0 | 150 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 31,736 (23.09%) | 31,736 (23.09%) | 0 | 103 | 0 | 148 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
