# Killer Instinct Gold (N64) — Decompilation Tracking

This is the **single source of truth** for who is doing what. Read it before you start anything.
The lead (orchestrator) vets every change before it lands. Subagents don't mark their own work "Done". They set it to "Review", and the lead moves it to "Done" after verifying it.

## Target
| Field | Value |
|---|---|
| Primary target | Killer Instinct Gold (U) (V1.0) — `NKIE`, rev 0 |
| baserom | `baserom.us.z64` → `ROMs/Killer Instinct Gold (U) (V1.0) [!].z64` (symlink, gitignored) |
| SHA1 | `ba52e91b44450c548467044b26951353dc491e04` |
| Size | 12,582,912 bytes (12 MiB), big-endian .z64 |
| Entrypoint (header) | `0x80000400` (CIC 6102, unchanged) |
| Compiler (game) | **IDO 5.3 `-O2 -mips2`** (+ `-G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul`, aux flags unproven): 10/12 probe fns match, excludes O1/O3/mips1/-g/7.1 (docs/compiler_flags.md). libultra: IDO 5.3 -O1 -mips2 |
| libultra | **SM64-US-identical lineage (pre-2.0I)**, built IDO 5.3 `-O1 -mips2` (asm: `-mips3 -32`); 98 boot + 169 main SDK fns named (docs/libultra.md). RSP ucode 2.0D |
| Toolchain | `./tools/setup.sh`; splat64 0.50.1, spimdisasm 1.42.4, rabbitizer 1.16.2, IDO 5.3/7.1 recomp v1.2, binutils 2.43.1 mips64-elf (docs/toolchain.md) |
| Code segments | boot (0x6160 text) · main @0x8000F960 (text 0x32DB0) · ovl_7DF8 @0x801ABB20 (text 0x21930) · ovl_7E00 @0x801AD900 (text 0x16640); 7DF8/7E00 overlap → mutually exclusive. 23 other table payloads are data (docs/segments.md) |
| Compression | **solved**: GoldenEye gzip 1.2.4 `-n -9`, strip gzip hdr/trailer, prefix `11 72`, zero-pad to 16 B → 29/29 streams byte-exact (docs/compression.md) |
| Assets | 0x7ED0–0xA94D80: 99.986% covered by code-referenced entries (1,526 B in 400 small gaps near audio); 85.8% packed graphics, ~13.6% audio (2 B1 banks, 484 samples, 48 S1 seqs) (docs/assets.md) |
| Graphics | decoder `tools/analysis/gfx_decode.py` → 6,022 PNGs: 813/842 sprite records, 6,012/6,369 frames (94.4%), 10/10 portraits; stage packets (13) undecoded (docs/gfx_format.md) |
| Build | `make extract && make` → boot asm + per-image asm → rarezip → spliced into ROM → sha1 check (matching; code-dependent since T-013) |
| Layout | see docs/rom_layout.md: boot seg ROM 0x1000–0x7ED0; main = 1172+raw-DEFLATE @0xA94D80 → 0x8000F960 (0x3A8D0 B); 26 compressed overlays/data via table @ROM 0x7DF0 |
| Other good dumps | US V1.1 `bcc599ed…`, US V1.2 `aaeb492b…`, EU `e0ed97c7…` (later targets) |

## Progress metrics (by original code bytes; methodology from docs/n64 guide §6)
Tiers: T1 unstarted · T2 in progress · T3 behavior-validated · T4 byte-exact · excluded (libultra/SDK)
- M1 = (T3+T4 bytes) / eligible bytes
- M2 = T4 bytes / eligible bytes
Source of truth for per-function tiers is `docs/functions.csv` (created once splat runs).

| Metric | Value |
|---|---|
| Scope measured | all CPU text of boot/main/ovl_7DF8/ovl_7E00 (999 fns). Text not in fns: boot 432 B pad, main 708 B, 7DF8 92 B, 7E00 4,040 B (31 inline data pools, listed in symbol_addrs.ovl_7E00.us.txt) |
| M1 | 10,876 / 319,544 B (3.40%) |
| M2 | 10,876 / 319,544 B (3.40%) |
| Functions | 271 T1 · 191 T2 · 0 T3 · 107 T4 · 430 excluded (137,648 B: 267 libultra + boot entry asm + 162 ovl_7E00 handwritten asm) |
| Per image (eligible B / T1 fns / excluded) | boot 8,468/21/99 · main 173,204/135/169 (56 T4, 99 T2) · ovl_7DF8 137,428/108/0 (51 T4, 92 T2) · ovl_7E00 444/7/162 |

Regenerate with `make progress` (writes docs/functions.csv + docs/progress.html). Tier overrides: tools/progress/status.csv (lead-maintained). Never hand-edit numbers; paste the `--markdown` output here.

## Known follow-ups
- ~~FU-1~~ (fixed in T-009): inventory keyed by (segment, vram).
- FU-2: splat hint of rodata at boot ROM 0x7D40; boot.s not yet split per original file.

- ~~FU-3~~ (T-012): merge T-005 SDK names (tools/analysis/data/{boot,main}_functions.csv) into symbol_addrs.*.txt and mark them excluded/libultra in tools/progress/status.csv — after T-009 lands.
- ~~FU-4~~ (T-018 → FU-12): libultra can likely be built from SM64-US lib sources for byte-exact SDK objects (lead verified 7 fns).
- ~~FU-5~~ (T-013): rarezip.py caches its gzip build in /tmp/kig-t008 (volatile, needs network); move cache to tools/ext/ when wiring compression into the Makefile.
- ~~FU-6~~ (T-013): wire build: compile/assemble main+overlays → recompress with rarezip → splice into ROM, replacing opaque compressed blobs (after T-009).
- ~~FU-7~~ (T-012): ovl_7E00 text has 12.5k `.word` lines (≈50 KB, e.g. func_801ADE68) that are valid MIPS but spimdisasm fell back to data → fix splat/symbol hints so all 0x16640 text bytes are functions.
- FU-8: opaque.bin still carries the original compressed code bytes under the spliced slots (overwritten at splice) → split kig.us.yaml so slots are not sourced from baserom; later support relocation of the 0x7DF0 table for non-matching builds.
- ~~FU-9~~ (T-016): ovl_7E00 has inline data pools inside text (handwritten-asm signature) → determine which ovl_7E00 functions are handwritten asm vs IDO C before assigning decomp work there. → 162 asm excluded; 7 tiny leaves (444 B) stay T1/uncertain.
- ~~FU-10~~ (T-017; 23 stage textures + 222 sprite frames still undecoded, documented in gfx_format.md): decode the 13 stage graphics packets (0x7E60–0x7EC0) + remaining 357 frames; update assets.csv class labels per T-014 corrections.
- FU-11 (T-018): main inventory folds a separate `jr ra; nop` stub at 0x80039AC0 into osAiGetLength (24 B; SM64 body is 12 B) → add a symbol at 0x80039AC0 and refresh original-functions.json baseline.
- FU-12 (T-018): integrate SM64-US libultra objects into the build (52 MATCH + 96 MATCH_MASKED fns, 93/94 whole-object placements; osAiSetFrequency needs 0x10 tail trim). 118 SDK fns (mostly libaudio, __lookupVoice etc.) absent from SM64 → stay asm. See docs/libultra_rebuild.md.
- FU-13: cleanup pass on matched C: replace m2c raw offset casts with structs (e.g. func_80018418 on D_8004A4C0/D_8004A998), unify duplicated per-function externs into headers, apply suggested names (T-020/T-021/T-022 replies). Must keep the build matching.

## Task board
Status values: Todo · In progress (owner) · Review · Done (verified by lead) · Rejected

| ID | Task | Owner | Status | Output | Notes |
|---|---|---|---|---|---|
| T-000 | Repo bootstrap, baserom selection, tracking | lead | Done | this file, .gitignore | |
| T-001 | Toolchain setup (venv, splat/spimdisasm/rabbitizer, m2c, asm-differ, MIPS binutils, IDO recomp) | sol-A | Done | tools/setup.sh, docs/toolchain.md | no sudo available |
| T-002 | ROM structure analysis (boot, entry, code segments, BSS, libultra version, compressed data) | sol-B | Done | docs/rom_layout.md, tools/analysis/ | read-only on ROM |
| T-003 | Prior-art + compiler research, cross-revision diff | sol-C | Done | docs/research.md, tools/research/ | |
| T-004 | Segment/overlay map: VRAM dest + text/data/bss bounds for main & all 26 table payloads; extractor | sol-B2 | Done | docs/segments.md, tools/analysis/segments.py, tools/analysis/extract_segments.py | stdlib only |
| T-005 | libultra version ID + boot-segment function inventory/naming | sol-C2 | Done | docs/libultra.md, tools/analysis/boot_functions.py, tools/analysis/libultra_sig.py | |
| T-006 | splat config (boot seg + opaque bins) + Makefile/linker → byte-identical ROM rebuild | sol-A2 | Done | kig.us.yaml, Makefile, symbol_addrs.us.txt, undefined_*.txt, include/ | compressed segments stay opaque bins for now |
| T-007 | Progress tooling: function inventory → docs/functions.csv, M1/M2 calc, HTML treemap | sol-A3 | Done | tools/progress/, docs/progress.html | |
| T-008 | Byte-exact 1172/DEFLATE recompressor (find gzip/zlib/7z/custom settings reproducing original streams) | sol-B3 | Done | tools/compress/, docs/compression.md | blocks matching build of main/overlays |
| T-009 | splat main + ovl_7DF8 + ovl_7E00 (decompressed), per-segment matching rebuild, inventory FU-1 fix | sol-A4 | Done | kig.<seg>.us.yaml, Makefile, tools/progress/inventory.py | ROM still embeds original compressed blobs until T-008 |
| T-010 | Determine game-code compiler flags (IDO ver, -O, -mips, -g) by matching a handful of small main/overlay game functions in scratch | sol-C3 | Done | docs/compiler_flags.md, tools/scratch/flagprobe/ | no build-system edits |
| T-011 | Asset region map ROM 0x7ED0–0xA94D80: code-referenced asset tables, every entry bounded+classified (audio, gfx, anim…), compressed vs raw | sol-B4 | Done | docs/assets.md, tools/analysis/assets.py, tools/analysis/data/assets.csv | read-only, no build edits |
| T-012 | FU-7 (ovl_7E00 text fully as functions) + FU-3 (merge T-005 SDK names into symbol_addrs, mark excluded in status.csv) | sol-A5 | Done | symbol_addrs*.txt, kig.*.us.yaml, tools/progress/status.csv, docs/functions.csv, docs/progress.html | |
| T-013 | FU-5+FU-6: build pipeline recompresses built main/ovl images (rarezip) and splices them into the ROM; gzip cache → tools/ext | sol-B5 | Done | Makefile, tools/compress/rarezip.py, tools/build/ | no yaml edits (T-012 owns) |
| T-014 | Packed-graphics format RE (main table +00 records, 825 self-sized records, palettes, 0x9900 RGBA5551 images) → decoder + PNG previews | sol-C4 | Done | docs/gfx_format.md, tools/analysis/gfx_decode.py | read-only, no build edits |
| T-015 | C build infra (IDO 5.3 -O2 -mips2, INCLUDE_ASM, src/ per image) + land T-010's 10 matched game fns as first T4 | sol-A6 | Done (verified) | Makefile, kig.*.yaml, src/, include/, symbol_addrs*.txt | |
| T-016 | FU-9: classify ovl_7E00 functions handwritten-asm vs IDO-C (read-only), recommend exclusions | sol-C5 | Done (verified) | docs/ovl_7E00_asm.md, tools/analysis/data/ovl_7E00_asm.csv | lead applies status.csv changes |
| T-017 | FU-10: decode 13 stage packets (table 0x7E60–0x7EC0) + remaining frames; fix assets.csv labels per T-014 | sol-C6 | Done (verified) | docs/gfx_format.md (stage section), tools/analysis/gfx_decode.py, tools/analysis/assets.py, tools/analysis/data/assets.csv | read-only on build |
| T-018 | FU-4 research: rebuild SM64-US libultra objects (IDO 5.3 -O1 -mips2, asm -mips3 -32) in scratch and compare every excluded libultra fn vs ROM bytes (reloc-masked) | sol-B6 | Done (verified) | tools/scratch/libultra/, docs/libultra_rebuild.md | scratch only; no Makefile/yaml/src/status edits |
| T-019 | Match ovl_7DF8 unit 0 (src/ovl_7DF8/ovl_7DF8.c, 0x801ABB20–0x801ADEA0): 25 T1 fns, 8,616 B | sol-A7 | Done (verified): 17 matched (1,632 B), 5 T2 drafts, 3 not attempted (func_801ABB20, func_801ACB1C, func_801ADCFC) | src/ovl_7DF8/ovl_7DF8.c, tools/scratch/nonmatching/T-019/ | worktree isolation |
| T-020 | Match main 0x8000F960–0x80018000 (src/main/main.c): 49 T1 fns, 34,500 B | sol-C7 | Done (verified): 13 matched (1,276 B), 9 T2 drafts, 27 not attempted (still T1, re-assignable) | src/main/main.c (only fns in range), tools/scratch/nonmatching/T-020/ | worktree isolation |
| T-021 | Match ovl_7DF8 0x801C2000–0x801CD440 (src/ovl_7DF8/ovl_7DF8_2380.c, only fns in range): 106 T1 fns, 45,832 B | sol-B7 | Done (verified): 23 matched (2,716 B), 36 T2 drafts, rest still T1 (re-assignable) | src/ovl_7DF8/ovl_7DF8_2380.c (range only), tools/scratch/nonmatching/T-021/ | worktree isolation |
| T-022 | Match main 0x80018000–0x80020000 (src/main/main.c, range only): 52 T1 fns, 36,084 B | sol-C8 | Done (verified): 21 matched (2,548 B), 31 T2 drafts (all attempted) | src/main/main.c (range only), tools/scratch/nonmatching/T-022/ | worktree isolation |
| T-023 | Match ovl_7DF8 0x801BA000–0x801C2000 (src/ovl_7DF8/ovl_7DF8_2380.c, range only): 55 T1 fns, 32,884 B | sol-B8 | Done (verified): 4 matched (352 B), 51 T2 drafts (all attempted; low yield, mostly regalloc/scheduling diffs) | src/ovl_7DF8/ovl_7DF8_2380.c (range only), tools/scratch/nonmatching/T-023/ | worktree isolation |
| T-024 | Match main 0x80028000–0x80030000 (src/main/main.c, range only): 78 T1 fns, 32,272 B (chosen over 0x80020000 range: smaller fns) | sol-C9 | Done (verified): 19 matched (1,288 B), 59 T2 drafts (all attempted) | src/main/main.c (range only), tools/scratch/nonmatching/T-024/ | worktree isolation |
| T-025 | Match ovl_7DF8 0x801ADEA0–0x801B4000 (src/ovl_7DF8/ovl_7DF8_2380.c, range only): 39 T1 fns, 25,580 B | sol-A10 | In progress | src/ovl_7DF8/ovl_7DF8_2380.c (range only), tools/scratch/nonmatching/T-025/ | worktree isolation |
| T-026 | Match main 0x80030000–0x80040000 (src/main/main.c, range only): 71 T1 fns, 38,452 B (small fns, best yield) | sol-B11 | In progress | src/main/main.c (range only), tools/scratch/nonmatching/T-026/ | worktree isolation |
