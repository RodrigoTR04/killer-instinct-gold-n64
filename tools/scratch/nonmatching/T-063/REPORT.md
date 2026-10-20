# T-063 — sol-C24: rebase T-055 matches onto current master

All eight functions landed matching on base `bbb858d`. No commits made; changes are left for lead review.

## Matches

- `func_80014250`
- `func_80035F10` (`osPfsFileState`, main_265B0; original symbol retained)
- `func_800249DC`
- Boot `func_80001564` (boot is now 100% matched)
- `func_80013CD8`
- `func_80018664`
- `func_80016BE0`
- `func_80016258`

Together these add 6,216 matching bytes. Applied the original T-055 patch with `git apply --3way`, then reconciled declarations against master. The unrelated `func_80017378` draft improvement was deliberately left unchanged.

## Declaration and integration changes

- Retained master's `s8 D_8004A5E0[][7]`, `s8 D_8004A688[][7]`, `u8 D_8004A730[8]`, and `s8 D_8004A738[8]`. Array accesses use the correct indices, including `D_8004A688[1][0]` for offset 7 and `D_8004A738[0]` for scalar accesses.
- `func_80016BE0` uses an unsigned byte array view of `D_8004A5E0` for its stores. This preserves master's declaration while retaining the original matching unsigned-store code generation. Direct signed stores shared constants differently (42 instruction words differed).
- Kept the single master `func_8001C43C(s32, u8 *, u8 *, u8 *, u8 *)` prototype; removed duplicate extern declarations, including overlapping grouped global declarations.
- Retained T-055's `u8` declarations for `D_8004AC89`, `D_8004AC8A`, `D_80061520`, and `D_8004AA2C`.
- Added T-055's move-kind, vertex, and object structs. `D_801D3430` has one typed 40-element object-array declaration. Existing `func_80016910` byte accesses use a `u8 *` view; its output remains byte-identical. A scalar declaration plus a struct cast prevented IDO from generating the matching unrolled pointer loop in `func_80018664`.
- `func_80018418` uses literal `650.0f`. The only symbol_addrs.main.us.txt change is removal of the `D_800488CC` function-owner hint. Master's C43C removals and B134 ownership remain intact.
- The only Makefile change is the `main_265B0.c.o` `-O2 -mips1` override.
- Kept regenerated linker_scripts/ovl_7DF8.undefined_syms.txt and ovl_7E00.undefined_syms.txt changes (obsolete `D_800488CC` entries removed).
- No overlay source, yaml, or tools/progress/status.csv edits. No inline asm or register tricks.

## Deleted matched drafts

- T-020/func_80014250.c
- T-022/func_80018664.c
- T-026/func_80035F10.c
- T-032/func_800249DC.c
- T-033/func_80013CD8.c
- T-033/func_80016258.c
- T-033/func_80016BE0.c
- T-037/main_265B0.c (alternate draft of the same matched pfs function)
- T-038/func_80001564.c

## Validation

Completed `make clean && make extract && make all && make progress` (MAKEFLAGS=-j8 for the clean/extract/all steps). Exit status 0. Full ROM and all images match, which also verifies all existing master matches, including func_80016760, func_80016910, func_8001C43C, func_8002A9DC, and func_8001B620.

- ROM SHA1: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8` (239824 bytes)
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39` (957392 bytes)
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb` (153904 bytes)

Missing local setup paths were symlinked from `/home/rodri/Projects/killer-instinct-gold-n64`: baserom.us.z64, ROMs, .venv, and tools/ext. No ROM data was added to git. The setup symlinks are left in place; some appear untracked.

## Final make progress

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 62,060 (19.45%) | 62,060 (19.45%) | 0 | 290 | 0 | 272 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 37,628 (21.72%) | 37,628 (21.72%) | 0 | 138 | 0 | 152 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 15,964 (11.62%) | 15,964 (11.62%) | 0 | 152 | 0 | 99 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
