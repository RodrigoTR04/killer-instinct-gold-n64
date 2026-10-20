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

- T-032 launched (sol-B13): main 0x80020000–0x80028000, 29 T1 fns, 29,468 B (base after the main split).

## 2026-10-19 — T-029 vetted (ovl_7DF8 0x801B4000–0x801BA000)
- Worktree t3-84f71892. func_801B4300 and func_801B4324 matched with clean C. Applied to HEAD and did a clean vet build: the ROM and all 3 images are byte-identical. 124 T4; M1 = M2 = 11,920 B (3.73%).
- Imported the 17 drafts plus REPORT.md (skipped build/diff logs and results.json) and added 17 T2 rows. Suggested names: func_801B4324 = getSelectionUnlockTier; T029Portrait is a partial 0x8C-byte asset record.

- T-033 launched (sol-A15): the 27 T1 functions T-020 did not attempt, in main 0x8000F960–0x80018000 (31,504 B).

## 2026-10-19 — T-030 paused (worker usage limit)
- T-030 stopped on the Codex usage limit (resets 19:18). A one-shot resume is scheduled for 19:21 (cron 39ad6eb1, session-only): "continue" in the same child thread.
- T-032 also stopped on the usage limit (same 19:18 reset). The 19:21 job resumes it too.
- T-033 also stopped on the usage limit (same 19:18 reset). All three workers are paused; the 19:21 job resumes all of them.

- At the user's request, launched 2 Opus 5.5 (low) workers on work disjoint from the paused Sol workers: T-034 (opus-1, ovl_7DF8 leftovers) and T-035 (opus-2, main ≥0x80040000 + polish of T-026 drafts).

## 2026-10-19 19:30 — all 5 workers resumed
- The 19:21 cron did not run, and the Opus workers T-034/T-035 had stopped on the Claude API rate limit. At the user's request, sent "continue" to all 5 child threads (T-030, T-032, T-033: kig-T-0NN-resume-3; T-034, T-035: kig-T-03N-resume-1; prefix command%3Amcp%3A1df98f12-7c08-444b-a300-5af1814cb308%3Athread-send).

## 2026-10-19 — T-030 vetted (ovl_7DF8 0x801C2000–0x801C8000, T-021 leftovers)
- Worktree t3-49e9e79f. func_801C2110 (cubic position/velocity) and func_801C78B0 matched. func_801C78B0 needs a K&R definition with u8 params: the callers in the same file use an unprototyped extern, and an ANSI prototype changes the callers' codegen (I tried it; the build fails). The C itself is plain, with no asm tricks.
- tools/progress/inventory.py: the T4 definition regex now also accepts K&R parameter declarations, a generic fix. T4 went from 125 to 126, exactly the +1 expected.
- Clean vet build: the ROM and all 3 images are byte-identical. 126 T4; M1 = M2 = 12,468 B (3.90%). Imported the 23 drafts plus REPORT.md (skipped diff/log files) and added 23 T2 rows.

- T-036 launched (sol-C14): polish T-022's 31 drafts (main 0x80018000–0x80020000). When vetting, remove T2 rows for drafts it matches.

## 2026-10-19 — T-035 vetted (Opus: main ≥0x80040000 + T-026 polish)
- Worktree t3-bf14a84c. func_800414F0 matched (an empty stub). The big find: 19 T-026 drafts are libultra Controller Pak (pfs) code and match exactly when built -O2 -mips1. The worker supplied complete replacement files for main_24820/24B50/2BA80/2CA60/2CDF0.c (every function in each file is C; no asm or register tricks). I added per-object CFLAGS overrides in the Makefile (generic mechanism, documented on line 10). I added the missing `#include "common.h"` to main_2BA80.c.
- Clean vet build: the ROM and all 3 images are byte-identical. 146 T4; M1 = M2 = 19,460 B (6.09%). Deleted 19 T-026 drafts and their T2 rows. Imported the improved drafts func_80035DE0/func_80035F10 and T-035's 7 part-A drafts (+7 T2 rows). Logged FU-15 (name/classify these libultra functions; more -mips1 TUs likely).

- T-037 launched (opus-2): FU-15 follow-up, testing -mips1 on main_24E70/26480/265B0/26860.c.
- User rule: no new Opus workers unless the user asks. T-034 and T-037 finish normally; only Sol slots are refilled.

## 2026-10-19 — T-034 vetted (Opus: ovl_7DF8 leftovers)
- Worktree t3-a09bfd2e. 10 matched; only GLOBAL_ASM stubs were removed. The lead also landed func_801CCBCC (its draft was identical standalone) by making func_801CC350/524/600 return s32 (they return their callee's value; their codegen is unchanged) and giving func_801CC350 an s32 * first parameter.
- Clean vet build: the ROM and all 3 images are byte-identical. 157 T4; M1 = M2 = 23,328 B (7.30%). ovl_7DF8 has 0 T1 left: every function is matched or drafted. Imported the 14 drafts plus a lead-written REPORT.md (the worker wrote none) and added 14 T2 rows.
- Cleanup for FU-13: D_80127D30 should be declared u8[8], replacing the T034_D_80127D30 #define cast.

## 2026-10-19 — T-032 vetted (main 0x80020000–0x80028000)
- Worktree t3-9b528953. 7 matched (func_80021ADC, 8002365C, 80023790, 80024144, 80025354, 80026AA0, 80027DA0); only GLOBAL_ASM stubs were removed and there are no tricks (one typedef include-guard #define). Clean vet build: the ROM and all 3 images are byte-identical. 164 T4; M1 = M2 = 24,608 B (7.70%).
- Imported the 22 drafts plus REPORT.md and added 22 T2 rows. Note: boot_inflate needs a consistent s32 return declaration across files (FU-13 cleanup).

- T-038 launched (sol-A16): boot C infrastructure, then match its 21 T1 fns.

## 2026-10-19 — T-033 vetted (main 0x8000F960–0x80018000, T-020 leftovers)
- Worktree t3-9f33d227. 4 matched (func_8001383C, 80014C40, 80015B64, 80015CD0; 2,188 B); only GLOBAL_ASM stubs were removed and there are no tricks. Clean vet build: the ROM and all 3 images are byte-identical. 168 T4; M1 = M2 = 26,796 B (8.39%).
- Imported the 23 drafts plus REPORT.md and added 23 T2 rows. main now has 0 T1: every eligible function is matched or drafted.

- T-039 launched (sol-B14): polish ovl_7DF8 drafts, near-misses first. When vetting, remove T2 rows for drafts it matches.

## 2026-10-19 — T-039 paused (worker usage limit)
- T-039 stopped on the Codex usage limit (resets 2026-10-20 00:30). A one-shot resume is scheduled for 00:33 (session-only cron). If it does not run, resume by hand.

## 2026-10-19 — T-036 vetted (polish T-022 drafts)
- Worktree t3-b86aa93e (base 05f18d0). Matched func_8001D37C, func_8001C1B0, func_8001BF1C (788 B) and improved 12 drafts (func_80018E88 now 2 words, func_8001C370 4, func_8001CF1C 6). Merging onto HEAD hit a declaration conflict: D_8004CE90 is `[]` here but `[][32]` in T-032's func_80024144. I unified it to `[][32]`; the ROM is unchanged.
- Clean vet build: the ROM and all 3 images are byte-identical. 171 T4; M1 = M2 = 27,584 B (8.63%). Deleted 3 drafts and their T2 rows; imported the updated T-022 drafts/README and T-036/REPORT.md.
- T-038 also stopped on the usage limit (same 00:30 reset). The 00:33 job resumes it too.

## 2026-10-19 — T-037 vetted (Opus: FU-15 -mips1 pfs TUs)
- Worktree t3-7bfc6e48. main_24E70.c (osPfsChecker, osPfsReadWriteFile, osPfsAllocateFile, …; 8 fns), main_26480.c (osPfsNumFiles) and main_26860.c (osPfsDeleteFile, __osPfsReleasePages, __osBlockSum) are fully C. Added 3 Makefile -mips1 overrides. osPfsAllocateFile needs an unused `u8 pad[4]` local. main_265B0 (osPfsFileState) is still 2 words off (a spill slot); its candidate is saved in T-037/.
- Clean vet build: the ROM and all 3 images are byte-identical. 183 T4; M1 = M2 = 34,724 B (10.87%). Deleted 12 T-026 drafts and their T2 rows. Imported REPORT.md, the main_265B0 candidate and score.py (a fast standalone compile+compare). The suggested libultra names are in T-037/REPORT.md (FU-15 naming todo).

- T-040 launched (opus-3, user-requested): polish main drafts, near-misses first. When vetting, remove T2 rows for drafts it matches and merge the Makefile with T-038.
- Limits refreshed early: T-038 and T-039 resumed by hand ("continue"). The 00:33 cron was cancelled.
- T-041 launched (sol-C16): ovl_7E00 C infra plus its 7 uncertain T1 leaves. Disjoint from T-038 (boot), T-039 (ovl_7DF8) and T-040 (main).

## 2026-10-20 — T-038, T-039 and T-041 vetted together
- T-038 (sol-A16, boot): boot text is split into an hasm entry plus 51 C TUs. The Makefile wildcards src/boot/*.c. inventory.py's GLOBAL_ASM inclusion test now uses whole-symbol matching (boot_dma vs boot_dma_chunked). 15 of the 21 functions match at default -O2 -mips2. 6 are drafts (T2): boot_dma_chunked, func_80000960, func_80000FA0, func_80001564 (8 words off), func_800016CC, func_80001F2C.
- T-039 (sol-B14, ovl_7DF8): func_801AF424, func_801B994C, func_801C8668 and func_801CBF8C match. func_801CD174 is now 2 words off. I deleted the 4 matched drafts and their T2 rows.
- T-041 (sol-C16, ovl_7E00): none of the 7 leaves can be C. The 4 exact bodies (jr ra stubs and func_801C2508) can't fit because a 1-function TU pads to 16 B and overwrites the neighbouring code. The other 3 use non-IDO registers and scheduling. Lead decision: exclude all 7 as handwritten asm, so ovl_7E00 has no eligible bytes left.
- Clean vet build: the ROM and all 3 images are byte-identical. 202 T4; M1 = M2 = 38,508 / 319,100 B (12.07%). T1 = 0 everywhere.
- T-040 (Opus) stopped on a Claude rate limit with a turn already queued, so I left it alone. When vetting it, the Makefile now has T-038's boot wildcard.
- Launched T-042 (boot polish + FU-2), T-043 (ovl_7DF8 rodata ownership, 4 fns) and T-044 (ovl_7DF8 polish round 2). All disjoint from T-040 (main).

## 2026-10-20 — T-040 vetted (Opus opus-3: main draft polish)
- Worktree t3-b057ab66 (base 13b3eeb), applied cleanly onto 3f951c9. 23 main functions match (T-020 ×4, T-022 ×2, T-024 ×17). I deleted those drafts and their T2 rows. 5 drafts improved: func_8001CBCC and func_8002A004 are now 2 words off and blocked on rodata. Declarations were unified in main_1A880, main_1BBA0 and main_1B230. No Makefile changes. osPfsFileState is still 2 words off after an exhaustive declaration-order search.
- Clean vet build: the ROM and all 3 images are byte-identical. 225 T4; M1 = M2 = 42,300 / 319,100 B (13.26%). FU-16 opened: main rodata ownership and the boot_dma prototype.

## 2026-10-20 — T-044 vetted (ovl_7DF8 polish round 2)
- Worktree t3-2e29617f. 5 functions match: func_801BEFFC, func_801C4BD0, func_801C72B0, func_801CD100 and func_801CD174 (720 B). I deleted those drafts and their T2 rows. 7 drafts improved; func_801B695C is now 4 words off. 12 unchanged.
- Clean vet build: the ROM and all 3 images are byte-identical. 230 T4; M1 = M2 = 43,020 / 319,100 B (13.48%).
- T-045 launched (sol-C18): main polish round 2 + boot_dma prototype.

## 2026-10-20 — T-043 vetted (ovl_7DF8 rodata ownership)
- Worktree t3-d4e34849. Three TUs (ovl_7DF8, _12C70, _200C0) now own their .rodata via `[off, .rodata, <tu>]` splat subsegments; the leftover rodata stays in asm data files. Makefile: IMAGE_OBJECTS now wildcards every asm/<image>/data/*.s. func_801ADCFC and func_801CBCCC match (736 B). The glyph functions func_801BF720 and func_801BF914 are still 2 words off each. The recipe is in T-043/REPORT.md and unblocks FU-16 (main float literals).
- It merged cleanly onto T-044 (bf39222). Clean vet build: the ROM and all 3 images are byte-identical. 232 T4; M1 = M2 = 43,756 / 319,100 B (13.71%).
- T-046 launched (sol-B16): main rodata ownership (FU-16 part 1).

## 2026-10-20 — T-042 vetted (boot polish)
- Worktree t3-a418e171. 5 of 6 match (5,296 B): boot_dma_chunked, func_80000960, func_80000FA0, func_800016CC and func_80001F2C (the inflate/Huffman code was rewritten as idiomatic C with refined extern types). func_80001564 is still 8 words off. FU-2 was not needed. Boot is now at 95.75%.
- Clean vet build: the ROM and all 3 images are byte-identical. 237 T4; M1 = M2 = 49,052 / 319,100 B (15.37%).
- T-047 launched (sol-A18): ovl_7DF8 polish round 3 plus rodata ownership extension.

## 2026-10-20 — T-047 vetted (ovl_7DF8 polish round 3)
- Worktree t3-95ad912c. 3 functions match: func_801CA784, func_801CC2C8 and func_801BF0E8 (400 B). 4 drafts improved, 7 unchanged; only 14 were attempted. D_80127D30 is now declared u8[8] (FU-13 item). No new rodata splits.
- Clean vet build: the ROM and all 3 images are byte-identical. 240 T4; M1 = M2 = 49,452 / 319,100 B (15.50%).
- T-048 launched (sol-A19): ovl_7DF8 round 4 with an explicit attempt list (clone families first).

## 2026-10-20 — T-046 vetted (main rodata ownership, FU-16 part 1)
- Worktree t3-8fad5136. main_18440 and main_2FF0 now own their .rodata (kig.main.us.yaml). symbol_addrs.main gets force_migration/function_owner hints so constants used by asm functions stay in their pool slots. func_80018E88 and func_8002A004 match. func_8001CBCC is still 2 words off (an early constant needs more ownership work).
- Clean vet build: the ROM and all 3 images are byte-identical. 242 T4; M1 = M2 = 49,928 / 319,100 B (15.65%).
- T-049 launched (sol-C19): func_80001564 + FU-2 + FU-8 (boot/ROM infra).

## 2026-10-20 — T-045 vet failed (sent back)
- Worktree t3-ce4f7418. It reports 5 matches (func_80013C84, func_8001BB10, func_8002F944, func_8002FAC0, func_80030020), boot_dma unified to (s32,s32,s32), and 8 drafts improved. On top of master it fails to link: T-046 pinned the constants D_800489D0/D8/E0/E8 to func_8001BB10 via function_owner hints, and T-045 converted that function to C. Sent back to rebase on master and fix this honestly (literals or reassigned hints).

## 2026-10-20 — T-049 vetted (boot/ROM infra)
- Worktree t3-ef42faf2. FU-2: boot_49A0 owns rodata 0x7D40–0x7D70; the rest stays as boot_remaining asm data, and the Makefile wildcards asm/data/*.s. FU-8: opaque.bin is split into opaque_assets / opaque_main_gap / opaque_tail. The 3 code slots (main 0xA94D80, ovl_7DF8 0xAB5810, ovl_7E00 0xB00EB0) are extract:False bins linked straight from the rebuilt .1172 streams. splice_rom.py now only verifies them, so no baserom code bytes reach the ROM. func_80001564 is still 8 words off after 34 probes.
- Clean vet build: the ROM and all 3 images are byte-identical. Metrics unchanged (242 T4, 15.65%).
- T-050 launched (sol-B17): ovl_7DF8 round 5, a 45-function list disjoint from T-048.

## 2026-10-20 — T-045 vetted after rework (main polish round 2)
- The worker rebased onto master. func_8001BA18 and func_8001BA94 now use 0.001/0.007 double literals, and the 4 func_8001BB10 function_owner hints were dropped, which fixes the link conflict with T-046. 5 functions match: func_80013C84, func_8001BB10, func_8002F944, func_8002FAC0 and func_80030020. boot_dma is unified to (s32,s32,s32) across main (FU-16 part 2 done). 8 drafts improved; func_80014250 is 3 words off.
- Clean vet build on cd3b413: the ROM and all 3 images are byte-identical. 247 T4; M1 = M2 = 50,648 / 319,100 B (15.87%). The undefined_syms files were regenerated.
- T-051 launched (sol-C20): main rodata ownership round 2, 10 functions.

## 2026-10-20 — T-048 vetted (ovl_7DF8 polish round 4)
- Worktree t3-8a5c1cd2. All 53 listed functions were attempted. 3 match: func_801AD3BC, func_801CCDE8 and func_801C407C (1,068 B). 32 drafts improved, 18 unchanged. ovl_7DF8_18520 now owns its rodata (0xE7CC0–0xE7D10).
- Clean vet build: the ROM and all 3 images are byte-identical. 250 T4; M1 = M2 = 51,716 / 319,100 B (16.21%).
- T-052 launched (sol-A20): main round 3, 43 screened-only drafts with an explicit list.

## 2026-10-20 — T-050 vetted (ovl_7DF8 polish round 5)
- Worktree t3-a74efb12. All 45 listed functions were attempted: 0 matched, 16 drafts improved, 29 unchanged. Only scratch drafts changed; src is untouched, so no build impact. I imported the updated drafts and REPORT.md. The large ovl_7DF8 drafts (>100 words off) give diminishing returns.
- T-053 launched (sol-B18): ovl_7DF8 finishing pass on T-048 near-misses and the clone families.

## 2026-10-20 — T-051 vetted (main rodata ownership round 2)
- Worktree t3-b276eca3. New .rodata owners: main (0x38E00), main_17140 (0x393B0) and main_321A0 (0x39D30). The main bss is split so main_2FF0 owns .bss at 0x8004A730, which lets C define `u8 D_8004A730[8]` (an allow_addend hint covers the asm users). func_80016760 matches. func_800249DC improved 63→10 words and func_8001346C 170→163. 7 unchanged; the jump-table functions have other codegen diffs.
- Clean vet build: the ROM and all 3 images are byte-identical. 251 T4; M1 = M2 = 51,912 / 319,100 B (16.27%).
- T-054 launched (sol-C21): main round 4, 30 mid-size drafts disjoint from T-052.
- The user asked for two Opus 5.5 (low) workers alongside Sol, and no extras after: T-055 (opus-4, main/boot near-misses + largest main drafts) and T-056 (opus-5, ovl_7DF8 near-misses outside T-053).

## 2026-10-20 — T-053 vetted (ovl_7DF8 near-misses)
- Worktree t3-e988a6dc. func_801B18BC and func_801BF788 match (500 B). 14 drafts improved and 2 unchanged; both clone families are still unmatched.
- Clean vet build: the ROM and all 3 images are byte-identical. 253 T4; M1 = M2 = 52,412 / 319,100 B (16.42%).
- T-057 launched (sol-B19): follow-up on T-053's near-misses and clone families.

## 2026-10-20 — T-052 vet failed (sent back)
- Worktree t3-ac9efe1b. It reports func_8002A9DC and func_8001C43C matched (C43C's owner hints removed) and 15 drafts improved. Merging onto master conflicts in main_2FF0.c: T-051 defines `u8 D_8004A730[8]` and scalar `s8 D_8004A738`, while T-052 declares extern s8 arrays and `D_8004A5E0[][7]`. Sent back to rebase and reconcile the types while keeping T-051's bss ownership.
- T-057 stopped on the Codex usage limit (resets 03:30). A one-shot resume is scheduled for 03:33 (cron 199d854c, session-only). If it doesn't fire, resume by hand.

## 2026-10-20 06:09 — resumes, and T-052 vetted after rework
- The 03:33 cron didn't fire before the session idled. At 06:09 I resumed T-057 (Sol, Codex limit) and T-055/T-056 (Opus, Claude rate limit) by hand with "continue".
- T-052 rework: rebased onto 716e1db. main_2FF0.c now defines `u8 D_8004A730[8]` and `s8 D_8004A738[8]` inside T-051's bss boundary, and the declarations are consolidated. func_8002A9DC and func_8001C43C match (C43C's owner hints removed). 15 drafts improved.
- Clean vet build: the ROM and all 3 images are byte-identical. 255 T4; M1 = M2 = 52,848 / 319,100 B (16.56%).

## 2026-10-20 — T-054 vetted (main polish round 4)
- Worktree t3-9b3124fe. All 32 listed functions were attempted. func_80016910 and func_8001B620 match (1,736 B); B620's 4 owner hints were reassigned to func_8001B134. 17 drafts improved, 13 unchanged. The lead resolved a mechanical symbol_addrs conflict with T-052: kept the B134 reassignment, dropped the C43C hints T-052 removed.
- Clean vet build: the ROM and all 3 images are byte-identical. 257 T4; M1 = M2 = 54,584 / 319,100 B (17.11%).
- T-058 (sol-A21: main near-misses) and T-059 (sol-C22: main mid drafts) launched. Lists are disjoint from each other and from T-055 (Opus).

## 2026-10-20 — T-056 (Opus) and T-057 vetted
- T-056 (opus-5, worktree t3-f41c5900): 7 ovl_7DF8 functions match: func_801C8A38, func_801C7E98, func_801CC878, func_801CC668, func_801CD078, func_801B4590 and func_801C1704. Mostly declaration fixes: the TU's own structs, the right global types, string literals defined in C in an owned rodata TU. 7 drafts improved; func_801C4E38 now compiles and is 2 words off (spill slot), func_801B6528 3, func_801B695C 4. The glyph functions are still 2 each.
- T-057 (sol-B19, t3-a689d98e): 0 matched and 0 improved across the 16 listed functions (func_801C51F8 is still 2 words off; clone family A 23, family B 70). Only the report was imported.
- Clean vet build: the ROM and all 3 images are byte-identical. 264 T4; M1 = M2 = 55,844 / 319,100 B (17.50%).
- T-060 launched (sol-B20): ovl_7DF8 with T-056's declaration-first method (15 functions).

## 2026-10-20 — T-055 (Opus) vet failed on merge (sent back)
- Worktree t3-c7619f3f (base 2827f78). It reports 8 matches (6,216 B): func_80014250, osPfsFileState (verbatim ultralib, main_265B0 -mips1), func_800249DC, boot func_80001564 (verbatim gzip inflate_fixed, so boot is 100%), func_80013CD8, func_80018664, func_80016BE0 and func_80016258. func_80017378 improved 463→41 words. func_8001CBCC needs a new code subsegment around image 0xCA10–0xD3F0 that owns rodata 0x362A0 (lead follow-up).
- On master, main_2FF0.c doesn't compile: T-055 uses D_8004A5E0 as a scalar, but T-052 made it [][7]. There was also a duplicate prototype. Sent back to rebase and reconcile.

## 2026-10-20 — T-059 vetted (main mid drafts)
- Worktree t3-45b42cd9. All 12 attempted: 0 matched, 5 drafts improved, 7 unchanged. Scratch-only changes, so I imported the drafts and REPORT.md. No build impact.
- T-061 launched (sol-C23): ovl_7DF8 stuck near-misses with the declaration-first method, a list disjoint from T-060.

## 2026-10-20 — T-060 vetted (ovl_7DF8 declaration-first)
- Worktree t3-489ed93b. All 15 attempted: 0 matched, 5 drafts improved (func_801C35D8 65→5, func_801BFB40 12→8), 10 unchanged. Scratch-only changes; I imported the drafts and REPORT.md.
- T-062 launched (sol-A22): ovl_7DF8 finishing pass on the 2-8-word near-misses.

## 2026-10-20 — T-055 Opus stopped (user), rework handed to Sol T-063
- The user asked me to stop the running Opus worker and give its work to 6.1 Sol, and not to spawn more Opus without asking. Cancelled T-055. Its work is saved in tools/scratch/nonmatching/T-055/: t055-original-vs-2827f78.patch is the original verified-in-its-tree patch, t055-wip-rebased-vs-18238fb.patch is the partial rebase. T-063 (sol-C24) finishes the rebase onto master.

## 2026-10-20 — T-058 vetted (main near-misses)
- Worktree t3-d0b8576b. func_80012950 matches (316 B). 4 drafts improved, 10 unchanged after 4,336 probes. I imported REPORT.md, the candidates and the probe scripts, but not the 2.4 MB of per-round probe logs.
- Clean vet build: the ROM and all 3 images are byte-identical. 265 T4; M1 = M2 = 56,160 / 319,100 B (17.60%).

## 2026-10-20 — T-063 vetted (T-055's 8 matches landed via Sol)
- Worktree t3-e5a426dc (base bbb858d). The 8 T-055 functions are in: func_80014250, osPfsFileState (main_265B0, verbatim ultralib, -mips1 Makefile line), func_800249DC, boot func_80001564 (gzip inflate_fixed; boot is 100%), func_80013CD8, func_80018664 (D_800488CC hint dropped), func_80016BE0 and func_80016258.
- The lead resolved a merge clash with T-058 (acb6e4f): `D_8004AE88/89` were declared s8 at the top and u8 later. Unified to one `u8` declaration, and all functions still match.
- Clean vet build: the ROM and all 3 images are byte-identical. 273 T4; M1 = M2 = 62,376 / 319,100 B (19.55%). Boot 100%, main 21.91%.
- T-064 launched (sol-B21): main TU split for func_8001CBCC, plus func_80017378.
