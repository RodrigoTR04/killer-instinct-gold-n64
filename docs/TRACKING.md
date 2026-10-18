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
| Compiler (working hypothesis) | IDO 5.3, start `-O2 -mips2 -G 0 -non_shared -Wab,-r4300_mul -Xcpluscomm`; also try -O1 / -mips1 (docs/research.md, medium confidence) |
| libultra | unknown — RSP ucode 2.0D; CPU lib version TBD (G..J candidates) |
| Toolchain | `./tools/setup.sh`; splat64 0.50.1, spimdisasm 1.42.4, rabbitizer 1.16.2, IDO 5.3/7.1 recomp v1.2, binutils 2.43.1 mips64-elf (docs/toolchain.md) |
| Code segments | boot (0x6160 text) · main @0x8000F960 (text 0x32DB0) · ovl_7DF8 @0x801ABB20 (text 0x21930) · ovl_7E00 @0x801AD900 (text 0x16640); 7DF8/7E00 overlap → mutually exclusive. 23 other table payloads are data (docs/segments.md) |
| Build | `make extract && make` → build/kig.us.z64, sha1-checked against baserom (matching since T-006) |
| Layout | see docs/rom_layout.md: boot seg ROM 0x1000–0x7ED0; main = 1172+raw-DEFLATE @0xA94D80 → 0x8000F960 (0x3A8D0 B); 26 compressed overlays/data via table @ROM 0x7DF0 |
| Other good dumps | US V1.1 `bcc599ed…`, US V1.2 `aaeb492b…`, EU `e0ed97c7…` (later targets) |

## Progress metrics (by original code bytes; methodology from docs/n64 guide §6)
Tiers: T1 unstarted · T2 in progress · T3 behavior-validated · T4 byte-exact · excluded (libultra/SDK)
- M1 = (T3+T4 bytes) / eligible bytes
- M2 = T4 bytes / eligible bytes
Source of truth for per-function tiers is `docs/functions.csv` (created once splat runs).

| Metric | Value |
|---|---|
| M1 | n/a (no inventory yet) |
| M2 | n/a |

## Task board
Status values: Todo · In progress (owner) · Review · Done (verified by lead) · Rejected

| ID | Task | Owner | Status | Output | Notes |
|---|---|---|---|---|---|
| T-000 | Repo bootstrap, baserom selection, tracking | lead | Done | this file, .gitignore | |
| T-001 | Toolchain setup (venv, splat/spimdisasm/rabbitizer, m2c, asm-differ, MIPS binutils, IDO recomp) | sol-A | Done | tools/setup.sh, docs/toolchain.md | no sudo available |
| T-002 | ROM structure analysis (boot, entry, code segments, BSS, libultra version, compressed data) | sol-B | Done | docs/rom_layout.md, tools/analysis/ | read-only on ROM |
| T-003 | Prior-art + compiler research, cross-revision diff | sol-C | Done | docs/research.md, tools/research/ | |
| T-004 | Segment/overlay map: VRAM dest + text/data/bss bounds for main & all 26 table payloads; extractor | sol-B2 | Done | docs/segments.md, tools/analysis/segments.py, tools/analysis/extract_segments.py | stdlib only |
| T-005 | libultra version ID + boot-segment function inventory/naming | sol-C2 | In progress | docs/libultra.md, tools/analysis/boot_functions.py, tools/analysis/libultra_sig.py | |
| T-006 | splat config (boot seg + opaque bins) + Makefile/linker → byte-identical ROM rebuild | sol-A2 | Done | kig.us.yaml, Makefile, symbol_addrs.us.txt, undefined_*.txt, include/ | compressed segments stay opaque bins for now |
| T-007 | Progress tooling: function inventory → docs/functions.csv, M1/M2 calc, HTML treemap | sol-A3 | In progress | tools/progress/, docs/progress.html | |
| T-008 | Byte-exact 1172/DEFLATE recompressor (find gzip/zlib/7z/custom settings reproducing original streams) | sol-B3 | In progress | tools/compress/, docs/compression.md | blocks matching build of main/overlays |
