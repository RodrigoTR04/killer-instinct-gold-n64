# T-083 — sol-C31: FU-15 part 1

Changes are uncommitted for lead review. No status.csv changes.

## Inventory

T4 identity is now (image, original VRAM), with accepted names from the original
baseline, the corresponding symbol_addrs*.txt, and src-owned symbols in the
image linker map. Comments are stripped before C-definition and assembly-inclusion
checks. Any INCLUDE_ASM/GLOBAL_ASM mentioning an accepted alias blocks credit.
The fresh post-build map must attribute the **same C-defined name** to a src
object at the original address; an unrelated/unused C definition cannot qualify.
Original assembly presence, successful make, exact ROM comparison, and exact
per-image comparisons remain mandatory. Explicit exclusions still win.

The CSV deliberately retains original names as stable inventory labels; symbol
renames are represented in symbol_addrs and C. Thus docs/functions.csv remains
byte-identical, including its name column, and original-functions.json is unchanged.
README documents alias resolution.

## Reference verification and renames

Verified the names and characteristic bodies/call relationships against
[n64decomp/ultralib](https://github.com/n64decomp/ultralib/tree/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src),
using the pre-VERSION_J branches where applicable. Existing local reference
checkout: /tmp/t075-ultralib (commit above). The ROM contains an older variant:
for example __osPfsGetStatus requests all channels through __osPfsRequestData
rather than the later one-channel helper, and osPfsInit lacks the later
activebank=-1 initialization. These differences do not change function identity.
The existing matching C bodies were preserved exactly apart from names.

Reference source groups:

- pfsisplug.c: plug polling/retry, request packet construction, controller status extraction.
- pfsinit.c, pfsgetstatus.c, pfssearchfile.c: initialization/checker call chain, Pak status/error decoding, directory/name search.
- pfschecker.c: checker and corrupted_init/corrupted inode-cache helpers.
- pfsreadwritefile.c: bank/page traversal (__osPfsGetNextPage), block read/write loop.
- pfsallocatefile.c: page allocation, __osPfsDeclearPage (SDK spelling), __osClearPage zero-fill.
- pfsnumfiles.c, pfsfilestate.c, pfsdeletefile.c, pfsfreeblocks.c: directory count, inode-chain size/state, release/checksum, free-page accounting.
- contpfs.c: byte sum, paired ID checksums, ID repair/redundant-copy checks, ID loading/checking, primary/mirror inode I/O, bank selection. The ROM uses its pre-J one-argument __osPfsSelectBank.
- contramread.c/contramwrite.c: SI DMA/CRC retry loops and static packet helpers.
- gu/lookathil.c: guLookAtHiliteF vector normalization, two hilite calculations and LookAt direction conversion; also confirmed by T-069/T-073's matching body and constant-pool evidence.

| Original | SDK name |
|---|---|
| func_80034180 | osPfsIsPlug |
| func_8003431C | __osPfsRequestData |
| func_800343F4 | __osPfsGetInitData |
| func_800344B0 | osPfsInit |
| func_80034554 | __osPfsGetStatus |
| func_80034630 | osPfsFindFile |
| func_800347D0 | osPfsChecker |
| func_80034DBC | corrupted_init |
| func_800350A0 | corrupted |
| func_80035240 | __osPfsGetNextPage |
| func_80035320 | osPfsReadWriteFile |
| func_80035690 | osPfsAllocateFile |
| func_80035A84 | __osPfsDeclearPage |
| func_80035C84 | __osClearPage |
| func_80035DE0 | osPfsNumFiles |
| func_80035F10 | osPfsFileState |
| func_800361C0 | osPfsDeleteFile |
| func_80036440 | __osPfsReleasePages |
| func_80036644 | __osBlockSum |
| func_8003B3E0 | __osSumcalc |
| func_8003B45C | __osIdCheckSum |
| func_8003B558 | __osRepairPackId |
| func_8003B8A4 | __osCheckPackId |
| func_8003BA08 | __osGetId |
| func_8003BC0C | __osCheckId |
| func_8003BD24 | __osPfsRWInode |
| func_8003BFC0 | __osPfsSelectBank |
| func_8003C030 | __osContRamRead |
| func_8003C25C | __osPackRamReadData |
| func_8003C3C0 | __osContRamWrite |
| func_8003C5E4 | __osPackRamWriteData |
| func_8003C750 | osPfsFreeBlocks |
| func_800330B0 | guLookAtHiliteF |

Renamed symbol_addrs.main.us.txt entries, C definitions, prototypes and all src
callers. This includes the user's explicitly approved 18 name-only lines in
src/ovl_7DF8/ovl_7DF8_200C0.c; no overlay logic changed. No old-name uses remain
under src. No libaudio function, boot source, Makefile, YAML, or T-082 function
was changed. Regenerated linker scripts are retained.

## Classification recommendation (lead decision)

Recommend excluding these 33 functions as SDK: 32 pfs functions (14,800 B) and
guLookAtHiliteF (1,900 B), total 16,700 B. Public SDK API signatures, internal
helper names, data layouts, error codes, inode/CRC algorithms and the reference
call graph establish SDK provenance; the unusual -O2 -mips1 pfs build is a
compiler configuration difference, not game-specific functionality. Prior
full-image matches and this rename-only build provide independent binary evidence.
The checker/packet/page helpers belong to those SDK implementations even where
the reference declares them static. Keep their existing linkage here to avoid
changing IDO code generation. Consistency with the already excluded libultra
functions favors exclusion; keeping them eligible would inflate game-code
progress based on a historical missed identification. status.csv is untouched,
and all 33 remain eligible T4 pending the lead's decision.

## Validation

- python3 -m unittest tools/progress/test_inventory.py: PASS (2 test methods;
  16 new fixture combinations with and without symbol-table aliases).
- Fixtures verify renamed T4, old/new-name GLOBAL_ASM rejection, wrong VRAM,
  non-src ownership, unrelated linked symbol, ROM mismatch and image mismatch.
- Before renames, make extract && make all && make progress: PASS; 290 T4,
  docs/functions.csv identical to tracked baseline with the new inventory.
- Final make clean && make extract && make all && make progress: PASS.
  ROM and all three decompressed images are byte-identical. SHA1:
  ROM ba52e91b44450c548467044b26951353dc491e04;
  main 81736d32e8cda8f399b319a49250dff972b81af8;
  ovl_7DF8 ea830aae50ff1422da60d4b7fdbfc29f03b1be39;
  ovl_7E00 2b01138a290212b9d886981e1196f7b6fb45ecdb.
- Before/after progress tables compare identical; cmp of docs/functions.csv
  against the saved pre-rename CSV passes. Generated progress.html and the
  baseline also have no git diff. git diff --check passes.
- Missing prerequisites were symlinked from
  /home/rodri/Projects/killer-instinct-gold-n64. No ROM was copied or committed.
  These local setup symlinks (.venv, ROMs, tools/ext) remain untracked.
- Regenerated overlay undefined_funcs.txt files contain the 33 SDK name
  substitutions. undefined_syms.txt files have no net changes.

## Before renames

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 70,556 (22.11%) | 70,556 (22.11%) | 0 | 272 | 0 | 290 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 44,288 (25.57%) | 44,288 (25.57%) | 0 | 126 | 0 | 164 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 17,800 (12.95%) | 17,800 (12.95%) | 0 | 146 | 0 | 105 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |

## After renames

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 70,556 (22.11%) | 70,556 (22.11%) | 0 | 272 | 0 | 290 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 44,288 (25.57%) | 44,288 (25.57%) | 0 | 126 | 0 | 164 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 17,800 (12.95%) | 17,800 (12.95%) | 0 | 146 | 0 | 105 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
