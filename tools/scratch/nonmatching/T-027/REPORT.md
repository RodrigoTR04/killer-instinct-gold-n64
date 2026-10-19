# T-027 — sol-C12

Worktree: `/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-0356ecbe`.
Base commit: `7dcd581`. No commits made. Main checkout and ROMs were not modified.

## Result

1 match (108 bytes), 5 improved drafts, 53 unchanged candidates. There are 58 remaining drafts. Only the verified match is retained in `src/main/main.c`; all failed candidates were restored to `GLOBAL_ASM`.

Deleted draft: `tools/scratch/nonmatching/T-024/func_8002B8B0.c`.

All 59 existing drafts were inspected and compiled in standalone IDO probes, supplying existing main.c types where required. The smallest diffs received targeted scheduling/register/stack experiments. A further bounded sweep tried 64 declaration-order and equivalent loop variants across 18 larger functions. Larger functions with no useful variant remain baseline-only inspections, not exhaustive reconstruction attempts. No function received more than approximately 30 candidate variants.

The five improved drafts were each inserted into main.c and tested with `make`, individually. Each compiled but failed byte identity; the table reports their unmasked linked word counts. Standalone probes only mask actual ELF relocations and are diagnostic, not match acceptance. In particular, func_8002A40C has four masked standalone differences but six linked differences.

## Changes and remaining blockers

- `func_8002B8B0`: word-sized `s32 mode`, plus explicit `case 0` alongside `default`, reproduces the original switch dispatch and stores. No unusual compiler extensions or data definitions.
- `func_8002A1A0`: use a 2048-byte indexed array access for the first bank. This retains the original two index shifts and reaches the original 60-byte body size. Four scheduling words remain; original trailing four-byte padding also remains relevant to promotion.
- `func_8002A40C`: assemble the big-endian size in byte order 0, 1, 2, 3. Linked differences remain at +0x48, +0x4C, +0x54, +0x58, +0x5C, +0x9C.
- `func_8002E680`: use a 16-byte local event record. The 0x50-byte frame now matches. Event stack placement, saved-register allocation, and scheduling remain different (16 words).
- `func_8002F31C`: an unused eight-byte local reproduces the 0x48-byte frame. This is an explicit stack-layout experiment, not a recovered semantic local. Four argument/save scheduling words remain at +0x20, +0x24, +0x28, +0x30.
- `func_8002F3DC`: unsigned 16-bit counters initialized immediately before each list walk reduce the mismatch to the prologue's three spill/load scheduling words (+0x0C, +0x10, +0x14).
- `func_8002AB64`: the 36-byte function body matches. Full insertion testing shows `func_8002AB90` at 0x8002AB88 rather than 0x8002AB90. The two nops occur after `endlabel` in the extracted assembly; replacing the pragma removes those eight bytes. The next GLOBAL_ASM does not restore 16-byte file alignment. A natural file-boundary solution would require alignment/configuration changes outside the permitted edits; no inline assembly or padding function was introduced.
- The other near matches remain blocked by store order (B3A8), ra-save ordering (F8F8/B95C), pointer spill position (2970C), initial stack/constant scheduling (B7E0), address commoning (B1EC), argument spills (B91C/A150), address construction order (B500), floating load scheduling (DCC8), and loop prologue/epilogue scheduling (A1E0).
- `func_8002FFDC` remains constrained by the second/fourth `s16` parameters declared outside this range at src/main/main.c:401 and :572. Word-sized forwarding parameters need lead review; those declarations were not changed.
- The large switch drafts retain their jump-table/rodata ownership blocker. No new data or rodata was defined. Existing matched functions and functions outside 0x80028000–0x80030000 were preserved.

## Status table

Unchanged rows retain the previous worker's T-024 diff notes; those numbers are not claimed as new linked measurements. Improved rows use this run's full translation-unit linked measurements.

| Function | Status | Remaining diff / evidence |
|---|---|---|
| `func_8002AB64` | UNCHANGED | Body matches; missing 8 bytes after the body; next symbol moves to 0x8002AB88 |
| `func_8002B3A8` | UNCHANGED | T-024: 2 differing words; 56/56 bytes |
| `func_8002A1A0` | IMPROVED DRAFT | 4 linked words; 60/60 bytes |
| `func_8002B1EC` | UNCHANGED | T-024: 4 differing words; 64/64 bytes |
| `func_8002B91C` | UNCHANGED | T-024: 4 differing words; 64/64 bytes |
| `func_8002A150` | UNCHANGED | T-024: 3 differing words; 68/68 bytes |
| `func_8002FFDC` | UNCHANGED | T-024: 18 differing words; 80/68 bytes |
| `func_8002F8F8` | UNCHANGED | T-024: 2 differing words; 76/76 bytes |
| `func_8002AA98` | UNCHANGED | T-024: 10 differing words; 80/84 bytes |
| `func_8002AAEC` | UNCHANGED | T-024: 10 differing words; 80/84 bytes |
| `func_8002B95C` | UNCHANGED | T-024: 2 differing words; 88/88 bytes |
| `func_8002970C` | UNCHANGED | T-024: 2 differing words; 100/100 bytes |
| `func_800281C4` | UNCHANGED | T-024: 11 differing words; 108/108 bytes |
| `func_8002B8B0` | MATCHED | 0; 108/108 bytes; full ROM and all images OK |
| `func_8002F2B0` | UNCHANGED | T-024: 21 differing words; 100/108 bytes |
| `func_8002A1E0` | UNCHANGED | T-024: 6 differing words; 116/116 bytes |
| `func_8002B500` | UNCHANGED | T-024: 4 differing words; 124/124 bytes |
| `func_8002F3DC` | IMPROVED DRAFT | 3 linked words; 128/128 bytes |
| `func_8002E680` | IMPROVED DRAFT | 16 linked words; 164/164 bytes |
| `func_8002A254` | UNCHANGED | T-024: 27 differing words; 172/172 bytes |
| `func_8002FAC0` | UNCHANGED | T-024: 41 differing words; 168/180 bytes |
| `func_8002E08C` | UNCHANGED | T-024: 19 differing words; 192/184 bytes |
| `func_8002F944` | UNCHANGED | T-024: 46 differing words; 176/184 bytes |
| `func_8002A9DC` | UNCHANGED | T-024: 45 differing words; 192/188 bytes |
| `func_8002F31C` | IMPROVED DRAFT | 4 linked words; 192/192 bytes |
| `func_8002B710` | UNCHANGED | T-024: 34 differing words; 180/196 bytes |
| `func_8002B7E0` | UNCHANGED | T-024: 2 differing words; 208/208 bytes |
| `func_8002F5F0` | UNCHANGED | T-024: 50 differing words; 220/212 bytes |
| `func_8002A40C` | IMPROVED DRAFT | 6 linked words; 220/220 bytes |
| `func_8002A900` | UNCHANGED | T-024: 55 differing words; 224/220 bytes |
| `func_8002DF98` | UNCHANGED | T-024: 57 differing words; 240/244 bytes |
| `func_80028600` | UNCHANGED | T-024: 18 differing words; 264/264 bytes |
| `func_8002A300` | UNCHANGED | T-024: 45 differing words; 296/268 bytes |
| `func_8002DCC8` | UNCHANGED | T-024: 4 differing words; 268/268 bytes |
| `func_8002B3E0` | UNCHANGED | T-024: 13 differing words; 280/280 bytes |
| `func_80029AB0` | UNCHANGED | T-024: 69 differing words; 284/304 bytes |
| `func_8002B9B4` | UNCHANGED | T-024: 10 differing words; 316/316 bytes |
| `func_8002A004` | UNCHANGED | T-024: 20 differing words; 324/324 bytes |
| `func_8002AEE4` | UNCHANGED | T-024: 76 differing words; 320/336 bytes |
| `func_8002B57C` | UNCHANGED | T-024: 76 differing words; 348/368 bytes |
| `func_8002B22C` | UNCHANGED | T-024: 95 differing words; 396/380 bytes |
| `func_8002F45C` | UNCHANGED | T-024: 80 differing words; 416/404 bytes |
| `func_8002B034` | UNCHANGED | T-024: 30 differing words; 440/440 bytes |
| `func_8002DDD4` | UNCHANGED | T-024: 104 differing words; 444/452 bytes |
| `func_8002E4A0` | UNCHANGED | T-024: 115 differing words; 428/480 bytes |
| `func_8002F6F4` | UNCHANGED | T-024: 30 differing words; 516/516 bytes |
| `func_8002D9C4` | UNCHANGED | T-024: 134 differing words; 476/536 bytes |
| `func_8002FB80` | UNCHANGED | T-024: 109 differing words; 512/544 bytes |
| `func_800287D4` | UNCHANGED | T-024: 91 differing words; 560/556 bytes |
| `func_8002FDA0` | UNCHANGED | T-024: 143 differing words; 580/572 bytes |
| `func_800297A4` | UNCHANGED | T-024: 180 differing words; 780/780 bytes |
| `func_8002E150` | UNCHANGED | T-024: 180 differing words; 836/844 bytes |
| `func_8002AB90` | UNCHANGED | T-024: 210 differing words; 816/852 bytes |
| `func_8002A4F0` | UNCHANGED | T-024: 155 differing words; 916/920 bytes |
| `func_80028230` | UNCHANGED | T-024: 242 differing words; 932/976 bytes |
| `func_80029BE0` | UNCHANGED | T-024: 263 differing words; 1048/1060 bytes |
| `func_8002E724` | UNCHANGED | T-024: 699 differing words; 2364/2832 bytes |
| `func_80028A00` | UNCHANGED | T-024: 802 differing words; 3264/3340 bytes |
| `func_8002BBD0` | UNCHANGED | T-024: 1919 differing words; 7804/7668 bytes |

## Validation

Baseline: `make extract && make && make progress` passed ROM and all three images, with 107 total T4 functions.

Final validation: `make clean && make extract && make && make progress` passed. The ROM and all three images are byte-identical. `git diff --check` passed. Total T4 increased from 107 to 108; main T4 increased from 56 to 57. The generated docs/functions.csv and docs/progress.html changes were restored after capturing these results, to honor the allowed edit scope.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,544 | 10,984 (3.44%) | 10,984 (3.44%) | 271 | 190 | 0 | 108 | 430 (137,648) |
| boot | 8,468 | 0 (0.00%) | 0 (0.00%) | 21 | 0 | 0 | 0 | 99 (16,028) |
| main | 173,204 | 5,596 (3.23%) | 5,596 (3.23%) | 135 | 98 | 0 | 57 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 5,388 (3.92%) | 5,388 (3.92%) | 108 | 92 | 0 | 51 | 0 (0) |
| ovl_7E00 | 444 | 0 (0.00%) | 0 (0.00%) | 7 | 0 | 0 | 0 | 162 (87,228) |

`probe.py` is a reproducible standalone diagnostic, for example:

```sh
.venv/bin/python tools/scratch/nonmatching/T-027/probe.py func_8002A1A0 func_8002A40C func_8002F3DC
```

Build logs are outside tools/scratch, under /tmp. The requested setup symlinks (.venv, ROMs, baserom.us.z64, tools/ext) remain local setup artifacts.
