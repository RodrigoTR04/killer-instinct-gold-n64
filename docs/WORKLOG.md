# Work log (append-only, newest at bottom)

Format: `YYYY-MM-DD | task ID | who | what changed | verification`

2026-10-18 | T-000 | lead | git init, .gitignore (ROMs excluded), baserom symlink to US V1.0, TRACKING.md | sha1 verified ba52e91b…
2026-10-18 | T-002 | sol-B → lead | docs/rom_layout.md + tools/analysis/{inspect_rom,compressed_blocks}.py | lead re-verified: IPL3 md5 (6102), entry words, all 27 table entries inflate to EOF, main sha1 81736d32…, RSP 2.0D string, 0xFF padding
2026-10-18 | T-003 | sol-C → lead | docs/research.md + tools/research/{revdiff,compression_probe}.py(+json) | lead re-verified: US1.0 vs 1.1 differ in [0x1000,0x100000) only at 0x7DF7–0x7EC7 (104 B, the segment table); US1.2 (−16) and EU (+16) shifted [0x8000,0x100000) byte-identical; IPL3 identical across all four. Web sources not re-fetched (marked as cited).
2026-10-18 | T-001 | sol-A → lead | tools/setup.sh, requirements.txt, docs/toolchain.md | lead re-verified: venv imports (spimdisasm 1.42.4, rabbitizer 1.16.2), IDO 5.3 -O2 -mips2 compiled a loop fn, mips64-elf-objdump disassembled it, m2c --help, m2c pinned commit matches
2026-10-18 | T-006 | sol-A2 → lead | kig.us.yaml, Makefile, symbol_addrs.us.txt, include/macro.inc, .gitignore (asm/ assets/ bin/ *.ld) | lead re-ran make clean/extract/make: sha1 ba52e91b… OK. Lead fix: entrypoint size 0x50 + func_80000450 symbol (splat had merged boot func into entrypoint); rebuild still OK. 117 boot funcs → 118 after fix. Follow-up: possible rodata at ROM 0x7D40; boot.s is one file (no per-file split yet)
2026-10-18 | T-004 | sol-B2 → lead | docs/segments.md, tools/analysis/{extract_segments,segments}.py | lead re-verified by disassembly: 7DF8 inflate→0x801ABB20 + jal at 0x800122E0; 7E00→0x801AD900 at 0x8000FC6C; main CPU text ends jr ra @0x80042700, RSP boot @0x80042710; 7DF8 BSS 0x802956F0–0x802D3FF0 = vram+size; 7DF8 text ends 0x801CD440; 7E00 text ends 0x801C3F38. Correction accepted: dup table entry is 0x7EC0 == 0x7E90 (lead's T-004 brief wrongly said 0x7E88)
2026-10-18 | T-007 | sol-A3 → lead | tools/progress/{inventory,progress,treemap}.py, status.csv, original-functions.json, README; docs/functions.csv, docs/progress.html | lead re-ran: deterministic CSV, 118 fns/24,496 B (432 B padding), T4 rule requires src def + no INCLUDE_ASM + matching make + map attribution. Lead added `make progress` target. Logged FU-1 (VRAM key collision for overlays)
2026-10-18 | T-005 | sol-C2 → lead | docs/libultra.md, tools/analysis/{boot_functions,libultra_sig}.py, tools/analysis/data/*.{csv,json} | lead independently rebuilt SM64-US (9921382a) lib with our IDO 5.3 -O1 -mips2 / binutils -mips3 -32: bzero, osInvalDCache, osInvalICache exact; osCreateMesgQueue, osInitialize(0x230), osPiStartDma, osRecvMesg 100% relocation-masked vs ROM. boot_functions.py deterministic.
2026-10-18 | T-008 | sol-B3 → lead | tools/compress/{rarezip,verify_all,deflate_info,compare_candidates}.py, docs/compression.md | lead re-ran verify_all: 29/29 PASS; independently recompressed 0xAB5810 (ovl_7DF8) and 0xB14BA0 → identical bytes, zero padding. Logged FU-5 (/tmp cache), FU-6 (splice into build)
2026-10-18 | T-009 | sol-A4 → lead | kig.{main,ovl_7DF8,ovl_7E00}.us.yaml, symbol_addrs.<img>.us.txt, Makefile (extract+per-image build+verify-images), tools/progress (segment-keyed inventory, verify_images.py, test_inventory.py), linker_scripts undefined lists | lead ran make clean/extract/make/progress: ROM OK + main/ovl_7DF8/ovl_7E00 sha1 OK (main 81736d32 matches T-002). Coverage: main 207,596/208,304 B text in fns, 7DF8 137,428/137,520; 7E00 only 54,020/91,712 → FU-7 logged
2026-10-18 | process | lead | NOTE: 'Track T-010'/'Track T-011' commits (ff4b8e8, ab67f46) used git commit -a and accidentally included in-progress T-009 edits (Makefile, inventory.py, functions.csv, original-functions.json) before vetting. Content was vetted afterwards in the T-009 entry above and is correct at c546ee5. Board-only commits now stage docs/TRACKING.md explicitly.

2026-10-18 | T-011 | sol-B4 → lead | docs/assets.md, tools/analysis/assets.py, tools/analysis/data/assets.csv | lead re-verified: depth-0 rows (1021) form exact contiguous partition 0x7ED0–0xA94D80; B1 magic at 0x8F9FA0/0x9AF4B0, S1 count 48 at 0x992AF0; main table @0x80045E50 entries 0 and 12 match doc; 1172 streams 0xA77960 (→0x9900) and 0x121F70 inflate to EOF
2026-10-18 | T-010 | sol-C3 → lead | docs/compiler_flags.md, tools/scratch/flagprobe/ (12 C probes + compare.py) | lead re-ran compare.py: 10 MATCH under 5.3 -O2 -mips2, 2 NO MATCH as documented; independently compiled 801B55DC (relocation-free) → byte-identical under 5.3, differs under 7.1. These 10 C files are T2-quality drafts outside the build (not counted until integrated in src/)
2026-10-18 | T-013 | sol-B5 → lead | Makefile (build/%.1172 + splice), tools/build/splice_rom.py, tools/compress/rarezip.py (cache → tools/ext, flock, KIG_GZIP_CACHE), tools/setup.sh (prebuild gzip) | lead: make OK; tamper of build/main.bin byte → FAIL, restore → OK. Lead fixed .gitignore (`build/` → `/build/`, it hid tools/build/). Logged FU-8
2026-10-18 | T-012 | sol-A5 → lead | kig.ovl_7E00.us.yaml (31 inline data subsegments, subalign 4), symbol_addrs*.txt (+87 boot, 169 main SDK names; main_ prefix for dup memcpy/strlen/strchr), status.csv (267 libultra excluded), regenerated linker undefined lists, functions.csv, progress.html, original-functions.json (baseline refreshed pre-C; boundaries corrected) | lead: clean extract/make all OK; progress 406,772 eligible / 731 T1 / 268 excl; inspected pool @0x801AE2AC = halfword table after j (genuine data). Logged FU-9
2026-10-18 | T-014 | sol-C4 → lead | docs/gfx_format.md, tools/analysis/gfx_decode.py | lead regenerated into /tmp: same counts (6,022 PNGs); viewed character kick frame and portrait_00 — clearly correct imagery. Lead added correction banner to docs/assets.md. Logged FU-10
2026-10-18 | T-015/016/017 | lead | all three Codex workers failed on usage limit (resets 20:58). T-015 partial (yaml c-subsegment switch + splat-generated src/) reverted since Makefile not yet adapted; T-016/T-017 left no files. Build re-verified OK at HEAD. Tasks back to Todo
2026-10-18 | T-015/016/017 | lead | r1 child runs auto-resumed after the 20:58 limit reset (queued retries); lead did NOT launch r2 to avoid duplicate work. T-016 had one 'model at capacity' failure, still has pending runs. Edits remain unvetted until each worker reports
2026-10-18 | T-016 | sol-C5 → lead | docs/ovl_7E00_asm.md, tools/analysis/ovl_7E00_classify.py, tools/analysis/data/ovl_7E00_asm.csv; lead: status.csv (+162 ovl_7E00:0x… excluded), functions.csv, progress.html | lead re-ran classifier: deterministic (md5 f6040412…), overlay sha256 d1d2f269…, 169/169 entries == functions.csv ovl_7E00 rows. Re-disassembled evidence: 801AD964 sw ra,0(sp) + k0/k1 saves, 801AD9E4 mfc0 Status, 997 k0/k1 uses outside entry fn, 801BC5A0 ra→t3 around jal, 801B2750/2794 sit in j delay slots. Excluded 161 high + 1 medium (801BAEC0); 7 uncertain leaves (444 B) left T1. Progress regenerated in clean worktree at HEAD (make extract/all OK): eligible 406,772 → 319,544. Lead slip: cp of regenerated functions.csv/progress.html overwrote T-015's in-flight generated copies in the main tree (generated only; T-015 must re-run make progress)
2026-10-18 | T-015 | sol-A6 → lead | Makefile (IDO 5.3 game CFLAGS, asm-processor rule, c-subsegment objects), kig.main/ovl_7DF8 yaml (c subsegments; split at 0x2380), tools/setup.sh (asm-processor f3b2f85a), tools/progress/inventory.py (implicit-text nonmatchings scan), include/{common,include_asm,ultra64}.h, src/main/main.c, src/ovl_7DF8/{ovl_7DF8,ovl_7DF8_2380}.c, CONTRIBUTING.md, diff_settings.py; docs/functions.csv, progress.html | lead: clean worktree at HEAD + T-015 files, make clean/extract/all/progress: ROM + 3 images OK; 10 T4 (1,064 B), totals unchanged (999 fns, 319,544 eligible). Verified split: alignment nop at 801ADE9C → 0x801ADEA0 boundary; lead renamed unit 'math' → ovl_7DF8_2380 (name was unevidenced). Tamper (801B55DC 0x30→0x31) → make FAIL and inventory refuses to regenerate. First automatic T4: M1=M2=0.33%
2026-10-18 | T-017 | sol-C6 → lead | docs/gfx_format.md (stage section), docs/assets.md, tools/analysis/{gfx_decode,assets}.py, tools/analysis/data/assets.csv | lead: assets.py regen byte-identical to committed CSV; depth-0 rows 1021 still exact partition 0x7ED0–0xA94D80; 12 unique stage_packet rows (slot 0x7EC0 aliases 0x7E90). gfx_decode run twice → 6,525 PNGs, identical md5s; counts 839/842 records, 6,147/6,369 sprite frames, 368/391 stage textures, 13 OBJ. Viewed stage_05 textures (stone/metal/pipe art, correct colours) and top-down OBJ render (coherent arena geometry)
2026-10-18 | T-018 | sol-B6 → lead | docs/libultra_rebuild.md, tools/scratch/libultra/{.gitignore,fetch.sh,build.py,compare.py,results.csv} | lead re-ran build+compare: 135/135 objects, results.csv md5 identical (edb7abf8…); 267 rows = all libultra exclusions: 52 MATCH (4,716 B), 96 MATCH_MASKED (23,328 B), 1 NO_MATCH (24 B), 118 NOT_FOUND (23,716 B). Reviewed compare.py: masks only R_MIPS_26 low 26 bits and HI16/LO16 low 16 bits, PC16 resolved locally; tail must be zero padding. Agrees with lead's earlier 7-fn check (bzero/osInvalICache/osInvalDCache MATCH; 4 masked). Disassembled NO_MATCH: 0x80039AC0 is a separate jr ra;nop stub folded into osAiGetLength → FU-11. Logged FU-12 (integration); FU-4 closed
2026-10-18 | T-020 | sol-C7 → lead | src/main/main.c (13 fns in 0x8000F960–0x80018000), tools/scratch/nonmatching/T-020/ (9 drafts); lead: status.csv (+9 T2), functions.csv, progress.html | lead reviewed diff: all edits in range, natural C, no tricks; applied patch to HEAD in clean worktree: make clean/extract/all/progress → ROM + 3 images OK, 23 T4 total (main 16). Drafts recorded as T2 so they are not redone. M1=M2 2,340/319,544 (0.73%). Names suggested (initMessageQueue/loadOverlay/setupPerspective) not yet applied
2026-10-18 | T-019 | lead | worker failed 'model at capacity', no pending runs. Partial unvetted edits remain in its worktree (~/.t3/worktrees/killer-instinct-gold-n64/t3-e4a647e2: ovl_7DF8.c, 6 drafts). Per user rule, not taken over or relaunched; user resumes manually
2026-10-18 | T-021 | sol-B7 → lead | src/ovl_7DF8/ovl_7DF8_2380.c (23 fns in 0x801C2000–0x801CD440), tools/scratch/nonmatching/T-021/ (36 drafts + REPORT.md); lead: status.csv (+36 T2), functions.csv, progress.html | lead: all 23 removed GLOBAL_ASM in range; C reviewed (natural; 390.0f literal materialized inline, no rodata); applied to HEAD in clean worktree → ROM + 3 images OK, 46 T4 total. Worker scratch had 83 func_*.c (incl. m2c output for not-attempted fns) — lead imported only the 36 REPORT.md DRAFT rows still GLOBAL_ASM (2 'DRAFT' rows were later MATCHED). M1=M2 5,056/319,544 (1.58%). Also: main T1 in TRACKING corrected 274→265 (T-020 drafts had been double-counted as T1)
2026-10-18 | T-022 | sol-C8 → lead | src/main/main.c (21 fns in 0x80018000–0x80020000), tools/scratch/nonmatching/T-022/ (31 drafts + README); lead: status.csv (+31 T2), functions.csv, progress.html | lead: 21 removed GLOBAL_ASM all in range; no asm/register tricks; applied to HEAD in clean worktree → ROM + 3 images OK, 67 T4 total. All 31 drafts still GLOBAL_ASM → T2. M1=M2 7,604/319,544 (2.38%). Logged FU-13 (m2c-style offset casts in func_80018418 etc., extern/header cleanup, names)
2026-10-18 | T-019/023/024 | lead | all three workers hit the Codex usage limit (resets 2026-10-19 02:07). Partial unvetted edits stay in their worktrees (T-019 t3-e4a647e2, T-023 t3-1fba501a; T-024 none). Per user rule, not taken over; user resumes manually. HEAD c2c83e2+board: 67 T4, M1=M2 2.38%

## 2026-10-19 02:41 — T-019/T-023/T-024 resumed
- The user resumed all three workers after the 02:07 usage reset; they continue in their existing worktrees (same r1 runs, no relaunch).
- New rule: if a worker stops on the usage limit, the lead schedules a resume ("continue" in the same child thread) for 3 minutes after the stated reset time. The lead still doesn't take over the work itself.

## 2026-10-19 — T-019 vetted (ovl_7DF8 unit 0)
- Worker reported 17/25 matched, 5 DRAFT, 3 NOT ATTEMPTED. The diff removed exactly 17 GLOBAL_ASM stubs, all inside 0x801ABB20–0x801ADEA0. Plain C, no asm tricks; there's a local partial `RenderState` struct.
- Applied to HEAD (worktree base was 25d5e2b) in a clean /tmp worktree. `make clean && make extract && make all && make progress` is byte-identical, T4 67 → 84.
- 5 DRAFTs (func_801AD114, func_801AD3BC, func_801AD568, func_801AD7D8, func_801ADA04) still GLOBAL_ASM → T2 rows; drafts in tools/scratch/nonmatching/T-019/.
- Not attempted, re-assignable: func_801ABB20, func_801ACB1C, func_801ADCFC. Suggested names noted in the T-019 README (for FU-13).
- M1 = M2 = 9,236 / 319,544 B (2.89%).

## 2026-10-19 — T-023 vetted (ovl_7DF8 0x801BA000–0x801C2000)
- Worker reported 4/55 matched and 51 DRAFT, with all 55 attempted. The diff removed exactly 4 GLOBAL_ASM stubs (func_801BFB10, func_801BFC08, func_801BFC8C, func_801C0784), all in range. Plain C, no tricks.
- Applied to HEAD (worktree base ce157f9) in a clean /tmp worktree. The build is byte-identical, T4 84 → 88.
- Spot-checked drafts: these are real hand-shaped attempts with typedefs, not raw m2c. Imported the 51 drafts that are still GLOBAL_ASM, plus REPORT.md. Skipped the worker's build/diff logs, attempt.py and the json files. Added 51 T2 rows.
- Low yield. Remaining diffs are mostly regalloc/scheduling; func_801BF720 and func_801BF914 need jump tables (rodata owned by asm). These are candidates for a later focused pass, not for re-assignment as T1.
- M1 = M2 = 9,588 / 319,544 B (3.00%).

## 2026-10-19 — T-024 vetted (main 0x80028000–0x80030000)
- Worker reported 19/78 matched and 59 DRAFT, with all 78 attempted. The diff removed exactly 19 in-range GLOBAL_ASM stubs and nothing else; no asm tricks. It adds local T024* typedefs; formatting is terse (FU-13).
- Applied to HEAD (worktree base 411befe) in a clean /tmp worktree. The build is byte-identical, T4 88 → 107.
- Imported the 59 drafts that are still GLOBAL_ASM, plus README.md → 59 T2 rows.
- Near-misses worth a later pass: func_8002AB64 (body matches, only a trailing 8-byte alignment issue), and several 2–4-word diffs (func_8002B3A8, func_8002F8F8, func_8002B95C, func_8002970C, func_8002B7E0, func_8002B1EC, func_8002B91C, func_8002B500, func_8002DCC8).
- Worker flag: the existing func_8002FFDC prototype (s16 forwarding args) outside its range needs review → FU-13.
- M1 = M2 = 10,876 / 319,544 B (3.40%).

## 2026-10-19 — T-025 vetted (ovl_7DF8 0x801ADEA0–0x801B4000)
- Worker reported 6/39 matched and 33 DRAFT, with all 39 attempted. The diff removed exactly 6 in-range GLOBAL_ASM stubs and nothing else; plain C (array indexing for IDO's 4-way unroll, `-1 ^ mask`).
- Applied to HEAD in a clean /tmp worktree. The build is byte-identical, T4 107 → 113.
- Imported the 33 drafts plus REPORT.md, skipping the worker's build/diff logs → 33 T2 rows.
- New FU-14: two drafts (func_8002AB64, func_801AFA48) match except for trailing padding, which marks original TU ends (16-byte .text alignment). Splitting src files there should make them match and exposes the original file layout.
- M1 = M2 = 11,160 / 319,544 B (3.49%).

## 2026-10-19 03:09 — T-028 paused (worker usage limit)
- T-028 stopped on the Codex usage limit (resets 07:41). A one-shot resume is scheduled for 07:44: "continue" in the same child thread, no relaunch.

- T-027 also stopped on the usage limit (same 07:41 reset). The 07:44 job resumes it too.
- T-026 also stopped on the usage limit (same 07:41 reset). All three workers are paused; the 07:44 job resumes all of them.

## 2026-10-19 14:18 — T-026/T-027/T-028 resumed
- The 07:44 auto-resume job never ran; it lived in the previous session only. I checked manually: all three were limit-stopped with no pending runs, so I sent "continue" to each child thread (new taskIds: `...thread-send%3Akig-T-02N-resume-2`, prefix `command%3Amcp%3Ade391ba9-0c69-4f89-8c2e-85b298158213`).

## 2026-10-19 — T-028 vetted (FU-14 ovl_7DF8 split)
- Worktree t3-7b4127b3. 12 new src/ovl_7DF8/ovl_7DF8_<off>.c files plus 12 yaml subsegments. Diff check: the old ovl_7DF8_2380.c content equals the new files concatenated, after normalising asm paths, apart from func_801AFA48 (now matched C). No build-tool changes.
- Clean vet in /tmp/kig-vet: the ROM and all 3 images are byte-identical. 114 T4; M1 = M2 = 11,212 B (3.51%). Removed the T2 row for func_801AFA48 and deleted its T-025 draft.
- Added docs/tu_boundaries.md and tools/analysis/tu_boundaries.py. Main has 86 definite boundaries; it is split only after T-026/T-027 land.

- T-029 launched (sol-A14): ovl_7DF8 0x801B4000–0x801BA000, 19 T1 fns, 23,828 B, base after the T-028 split.

## 2026-10-19 — T-027 vetted (polish T-024 drafts)
- Worktree t3-0356ecbe (base 7dcd581). Only the func_8002B8B0 stub was replaced, with clean C (a switch). Applied to HEAD and did a clean vet build: the ROM and all 3 images are byte-identical. 115 T4; M1 = M2 = 11,320 B (3.54%).
- Removed its T2 row and deleted T-024/func_8002B8B0.c. Imported the 5 improved T-024 drafts (A1A0, A40C, E680, F31C, F3DC; 3–16 words of diff left) and T-027/REPORT.md. Skipped T-027/probe.py, which is a scratch tool.
- Notes: func_8002AB64 is blocked on the main TU split (FU-14). func_8002FFDC needs its parameter declarations reviewed outside the range.

- T-030 launched (sol-C13): the 25 T1 functions T-021 did not attempt, in ovl_7DF8 0x801C2000–0x801C8000 (19,624 B).

## 2026-10-19 — T-026 vetted (main 0x80030000–0x80040000)
- Worktree t3-e798001a (base 8730f2e). 5 matched, all empty void stubs: func_80030218, func_80039AC0 (closes FU-11), func_80039C00, func_8003D348, and func_80037770 together with func_80037778. Applied to HEAD and did a clean vet build: the ROM and all 3 images are byte-identical. 120 T4; M1 = M2 = 11,368 B (3.56%).
- Imported the 66 drafts plus REPORT.md (spot-checked: genuine attempts, not raw m2c) and added 66 T2 rows. Low yield: most functions in this range are large.
- Notes: func_80030EF0's body matches and only lacks a 4-byte alignment gap, so it is an FU-14 TU-boundary candidate. func_800326F0 uses native 64-bit ops (dsll), so it is probably not IDO -mips2 C (an asm or -mips3 candidate).

- T-031 launched (sol-B12): split main at its definite TU boundaries (FU-14). No other worker may touch main src until it lands.

## 2026-10-19 — T-031 vetted (FU-14 main split)
- Worktree t3-1492dbe5. src/main/main.c is now split into 87 files (main.c + main_<off>.c), one per definite boundary (86), all inside .text; yaml subsegments added. Diff check: the old main.c equals the new files concatenated in yaml order, after normalising asm paths, apart from one duplicated boot_inflate extern and the 2 new matches.
- func_8002AB64 and func_80030EF0 now match, since IDO pads their TU end. Deleted both drafts and their T2 rows. Clean vet build: the ROM and all 3 images are byte-identical. 122 T4; M1 = M2 = 11,752 B (3.68%). FU-14 is closed.
