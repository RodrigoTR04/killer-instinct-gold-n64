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

## 2026-10-20 — T-061 vetted (ovl_7DF8 stuck near-misses)
- Worktree t3-19016f2e. func_801C71FC matches (a u64 argument plus the correct global array). Improved: func_801C6A80 30→8 and func_801C2D34 95→6. 13 unchanged (the glyph functions, func_801C51F8 and both clone families are still stuck).
- Clean vet build: the ROM and all 3 images are byte-identical. 274 T4; M1 = M2 = 62,548 / 319,100 B (19.60%).
- T-065 launched (sol-C25): ovl_7DF8 near-misses and mid drafts, angle: argument widths.

## 2026-10-20 — T-062 vetted (ovl_7DF8 finishing)
- Worktree t3-ef166d85. func_801BFB40 matches (200 B). Improved: func_801C35D8 5→4, func_801B446C 34→31, func_801C7CD0 63→34. func_801C4E38 (2) and func_801B6528 (3) are unchanged.
- Clean vet build: the ROM and all 3 images are byte-identical. 275 T4; M1 = M2 = 62,748 / 319,100 B (19.66%).
- T-066 launched (sol-A23): ovl_7DF8 stuck near-misses with the argument-width angle.

## 2026-10-20 — T-064 vetted (main TU split for func_8001CBCC)
- Worktree t3-c7be63b5. The old main_2FF0 (0x2FF0–0x15380) is now three TUs: main_2FF0, main_CA10 [0xCA10,0xD3F0) and main_D3F0 (the tail). main_CA10 owns rodata 0x362A0 (its one-float block); main_D3F0 owns rodata from 0x390A0. func_8001CBCC matches with the literal 0.017453292f. func_80017378 improved 41→8 words.
- Clean vet build: the ROM and all 3 images are byte-identical. 276 T4; M1 = M2 = 63,068 / 319,100 B (19.76%).
- T-067 launched (sol-B22): main near-misses plus the per-TU -mips1 flag hypothesis.

## 2026-10-20 — T-065 vetted (ovl_7DF8 argument widths)
- Worktree t3-69854cd4. All 11 attempted: 0 matched, 3 improved (func_801C7998 55→6, func_801C5064 93→6, func_801B1210 39→38). Scratch-only changes; I imported the drafts and REPORT.md.
- T-068 launched (sol-C26): ovl_7DF8 6-8-word near-misses plus the flag hypothesis.

## 2026-10-20 — T-066 vetted (ovl_7DF8 stuck near-misses, type angle)
- Worktree t3-f34be619. func_801B6A68 matches (512-byte palette rows); func_801C7CD0 improved 34→6. 8 unchanged (the glyph functions, func_801C4E38, func_801B6528, func_801C35D8, func_801C51F8, func_801B695C, func_801B446C).
- Clean vet build: the ROM and all 3 images are byte-identical. 277 T4; M1 = M2 = 63,436 / 319,100 B (19.88%).
- T-069 launched (sol-A24): 10 large main drafts (1.3–1.9 KB), a list disjoint from T-067.

## 2026-10-20 — T-068 vetted (ovl_7DF8 near-misses + flags)
- Worktree t3-b15c058b. func_801C7998, func_801C5064, func_801C2D34 and func_801C6A80 are unchanged (6/6/6/8 words). Flag hypothesis rejected for these TUs: -mips1 and -O1 break existing TU matches, and dropping -Xcpluscomm has no effect. Report only.
- T-070 launched (sol-B23): ovl_7DF8 mid-large drafts, structure-first.

## 2026-10-20 — T-067 vetted (main near-misses; 20% passed)
- Worktree t3-f91372f3. 7 functions match (1,508 B): func_8002DF98, func_8002B95C, func_8002B7E0, func_8002B57C, func_8002B91C, func_8002DCC8 and func_8002A300. The key was source line placement: IDO -O2 scheduling depends on which statements share a source line, the known IDO quirk. No flag changes (-mips1 etc. rejected). 3 drafts improved, 5 unchanged. The code style is compact and gets tidied in FU-13.
- Clean vet build: the ROM and all 3 images are byte-identical. 284 T4; M1 = M2 = 64,944 / 319,100 B (20.35%). Main is at 22.96%.
- T-071 launched (sol-C27): IDO line-placement technique on the stuck ovl_7DF8 near-misses.

## 2026-10-20 — T-071 vetted (ovl_7DF8 line placement)
- Worktree t3-3f489538. 3 functions match with multiline layouts (1,096 B): func_801C51F8, func_801C35D8 and func_801C2D34. 8 drafts improved, 8 unchanged.
- Clean vet build: the ROM and all 3 images are byte-identical. 287 T4; M1 = M2 = 66,040 / 319,100 B (20.70%).
- T-072 launched (sol-A25): main line placement on mid drafts never tried with it.

## 2026-10-20 — T-069 vetted (main large drafts)
- Worktree t3-93331984. func_8001C5AC matches (1,568 B, in main_CA10). func_800330B0 has an exact masked body but is blocked on rodata ownership (follow-up). 8 drafts improved, 1 unchanged.
- Clean vet build: the ROM and all 3 images are byte-identical. 288 T4; M1 = M2 = 67,608 / 319,100 B (21.19%).
- T-073 launched (sol-B24): land guLookAtHiliteF (func_800330B0) by giving main_23750 its rodata.

## 2026-10-20 — T-070 vetted (ovl_7DF8 mid-large drafts)
- Worktree t3-a5d29587. All 10 attempted: 0 matched, 9 improved (func_801C4240 326→167, func_801B0CDC 301→209, func_801B0668 231→159), 1 unchanged. Signedness fixes to globals in ovl_7DF8_18520.c and _1B790.c (s8→u8, s16→u16); the build still matches.
- Clean vet build: the ROM and all 3 images are byte-identical. Metrics unchanged (288 T4, 21.19%).
- T-074 launched (sol-C28): ovl_7DF8 mid drafts with declaration-first fixes plus line placement.

## 2026-10-20 — T-073 vetted (guLookAtHiliteF)
- Worktree t3-1fffe101. main_23750 now owns .rodata 0x396A0–0x396C0 (0.1, 0.1, 127.0 + padding), and the rest is main_after_23750 asm data. func_800330B0 = SDK guLookAtHiliteF (libreultra lookathil.c) matches (1,900 B). FU-15: an SDK name to apply later.
- Clean vet build: the ROM and all 3 images are byte-identical. 289 T4; M1 = M2 = 69,508 / 319,100 B (21.78%). Main is at 24.96%.
- T-075 launched (sol-B25): SDK identification sweep over the remaining main drafts.

## 2026-10-20 — T-072 vetted (main line placement on mid drafts)
- Worktree t3-9be005ec. All 16 attempted: 0 matched, 5 drafts improved, 11 unchanged. Scratch-only changes; I imported the drafts and REPORT.md. Line placement mostly helps when only a few scheduling differences remain.
- T-076 launched (sol-A26): ovl_7DF8 structure-first round 2 on T-070's drafts.

## 2026-10-20 — T-074 vetted (ovl_7DF8 mid drafts, declarations + line placement)
- Worktree t3-ea890a10. All 17 attempted: 0 matched, 10 drafts improved, 7 unchanged. Scratch-only changes; I imported the drafts and REPORT.md.
- T-077 launched (sol-C29): ovl_7DF8 clone families deep dive.

## 2026-10-20 — T-075 vetted (main SDK sweep)
- Worktree t3-4e2e0daf. All 127 main drafts screened. func_8003EF90 = SDK alFxNew matches (1,048 B); main_2F2A0 now owns rodata 0x39C50–0x39C80. _bnkfPatchInst improved. The shortlist and names (for FU-15) are in T-075/REPORT.md.
- Clean vet build: the ROM and all 3 images are byte-identical. 290 T4; M1 = M2 = 70,556 / 319,100 B (22.11%). Main is at 25.57%.

## 2026-10-20 — T-076 and T-077 vetted (ovl_7DF8, drafts only)
- T-076 (t3-7415a74e): 10 large drafts, 9 improved by small amounts (e.g. func_801B3DB0 277→255, func_801C1C34 262→242), 0 matched.
- T-077 (t3-1da7ab54): instruction-level analysis of clone family A, now 14 words per copy (from 16-17); family B is still 65. 0 matched. The analysis is in T-077/REPORT.md.
- Scratch-only changes, so I imported the drafts and reports. The low-effort Sol rounds on ovl_7DF8 are giving clearly diminishing returns.
- Launched T-078 (sol-A27: libaudio at -O3), T-079 (sol-B26: untouched big ovl_7DF8 drafts) and T-080 (sol-C30: FU-12 libultra integration, starting with boot).

## 2026-10-20 — T-079 vetted (untouched large ovl_7DF8 drafts)
- Worktree t3-d89c7443. 0 matched; all 4 improved: func_801C23C0 362→222, func_801BDF94 406→353, func_801BCB70 416→391, func_801C08F8 565→561. Scratch-only changes; I imported the drafts and REPORT.md.
- T-081 launched (sol-B27): 5 huge main drafts, structure-first.

## 2026-10-20 — T-081 vetted (huge main drafts)
- Worktree t3-10b1f013. 0 matched; 4 improved slightly (e.g. func_8002E724 699→660, func_8001E33C 602→571), func_800142E0 unchanged. It reports an audio jump-table ownership blocker. Scratch-only changes; I imported the drafts and REPORT.md. Huge drafts are not productive for Sol low.
- T-082 launched (sol-A28): install decomp-permuter and run it on the 25 near-misses.

## 2026-10-20 — T-080 vetted (FU-12: libultra SDK C integrated)
- Worktree t3-b88fd56c. 117 of the excluded SDK functions are now built from SM64-US libultra C (pinned commit) across 71 objects: src/boot/libultra (44 files) and src/main/libultra (27). The boot TUs holding them were split, with two boot_sdk_gap_*.c files for the leftovers. Per-object SDK_CFLAGS follow SM64's US flags: O1 -mips2 default, O3 for gu*, O2 for string, O1 -mips3 for llmuldiv. tools/build/ido_o32.py only sets the ELF o32 header flags for the -mips3 object, as SM64's patch_elf_32bit does. Headers are in include/sdk/libultra.h, plus SDK symbol tables in linker_scripts/libultra.*_symbols.txt. osAiSetFrequency stays asm (its object padding overlaps audio).
- They stay tier "excluded", so M2 is unchanged (290 T4, 22.11%), but these 117 functions are no longer assembly. Clean vet build: the ROM and all 3 images are byte-identical.
- T-083 launched (sol-C31): address-based inventory, then FU-15 renames for pfs and guLookAtHiliteF.

## 2026-10-20 — T-078 vet: structural conflict with T-080 (sent back)
- Worktree t3-a5f157f5 (base bbdd23e). Libaudio at IDO -O3 (interprocedural) solved the "private register ABI": all 19 targeted eligible functions match (11,476 B; main would go to ~32%), and 111 GLOBAL_ASM stubs were replaced in total. Per-object -O3 CFLAGS + ASMPROC -O2, include/libaudio/.
- On master (after T-080) it conflicts in kig.main.us.yaml (0x2A830 and 0x319D0 boundaries, plus rodata ranges given to libultra objects), the Makefile, main_2A160.c and main_319D0.c. Sent back to rebase onto T-080's layout.

## 2026-10-20 — T-083 vetted (address-based inventory + FU-15 renames)
- Worktree t3-c949349c. inventory.py now accepts a function's original name OR any symbol_addrs/linked-src name at its address, and keeps every safety check (unit tests pass). 33 SDK renames: 32 pfs functions (osPfs*/__osPfs*/__osContRam*...) and guLookAtHiliteF, including name-only caller edits in ovl_7DF8_200C0.c. Tiers and counts are unchanged (290 T4, 22.11%). The ROM is byte-identical.
- T-083 recommends classifying these 33 (16,700 B) as SDK (excluded), consistent with the libultra convention.
- T-084 launched (sol-B28): FU-13 readability cleanup of boot plus docs/boot.md. SDK reclassification (pfs + gu + libaudio) is pending until T-078 lands.

## 2026-10-20 — T-078 vetted after rework (libaudio at IDO -O3)
- Rebased onto T-080's libultra layout. Libaudio TUs are built at IDO -O3 (interprocedural; asm-processor uses its -O2 placeholder model via per-object ASMPROC), with headers in include/libaudio/. This explains the old "private register ABI". 19 eligible functions match (11,476 B): func_80037780 (_bnkfPatchInst), func_80038DE0 (__getTrackByte), func_80039C08 (alAudioFrame), func_80042198 (alFxParamHdl), plus the 15 T-035/T-045 private-ABI functions. 111 GLOBAL_ASM stubs were replaced in total (the rest are already-excluded SDK).
- Clean vet build: the ROM and all 3 images are byte-identical. 309 T4; M1 = M2 = 82,032 / 319,100 B (25.71%). Main is at 32.20%.

## 2026-10-20 — T-086 SDK reclassification (user decision)
- The user chose to exclude identified SDK code from the progress % (consistent with the libultra convention). Added 53 `excluded` rows in status.csv: 32 pfs (osPfs*/__osPfs*/__osContRam*), guLookAtHiliteF, alFxNew and the 19 libaudio functions from T-078 (_bnkfPatchInst, __getTrackByte, alAudioFrame, alFxParamHdl + 15 more). The code is unchanged and stays C.
- New baseline: eligible 289,876 B; M1 = M2 = 52,808 B (18.22%); 256 T4. Main is at 18.43% of game code. The ROM is still byte-identical. TRACKING now has an "SDK decompiled" line (~262 SDK functions are C).
- T-085 launched (sol-C32): finish the remaining drafts in mostly-matched main TUs.

## 2026-10-20 — T-084 vetted (boot readability, FU-13 boot)
- Worktree t3-cba8d4ed. include/boot.h holds shared types and declarations. Boot functions and state are named after gzip inflate.c and their roles (boot_start, boot_load_main, huft_build, inflate_codes/stored/fixed/dynamic/block, boot_scheduler_thread, ...), with struct member access and boot-flow comments. docs/boot.md is new. Name-only caller edits in main.c. No readability change needed reverting.
- Clean vet build: the ROM and all 3 images are byte-identical; boot is 21/21 T4.
- T-087 launched (sol-A29): finish the remaining drafts in mostly-matched ovl_7DF8 TUs.

## 2026-10-20 — T-082 vetted (decomp-permuter)
- Worktree t3-7d9a7f68. decomp-permuter is installed in the shared tools/ext; tools/permuter/ has the import helper and README. 4 matches (1,096 B): func_8002AEE4 (u16 quit flag + 8-byte client object), func_8002B1EC (named zero temporary, documented), func_8002B9B4 (line layout) and func_801C7CD0 (inline replay-byte read). Improved: func_8002AA98/AAEC 10→2, func_8002F45C 20→13. The permuter output was cleaned into readable C.
- The lead fixed one name-only conflict: func_80001EF4 → boot_subscribe_retrace (T-084 rename) in main_1B230.c.
- Clean vet build: the ROM and all 3 images are byte-identical. 260 T4; M1 = M2 = 53,904 / 289,876 B (18.60%).
- T-088 launched (sol-B29): permuter round 2 on the remaining near-misses.

## 2026-10-20 — T-085 vetted (main finish-the-TU)
- Worktree t3-594a799d. All 23 attempted: func_8002A1E0 and func_8003037C match (304 B), 11 drafts improved, 10 unchanged.
- Clean vet build: the ROM and all 3 images are byte-identical. 262 T4; M1 = M2 = 54,208 / 289,876 B (18.70%).
- T-089 launched (sol-C33): permuter on 7 equal-size main drafts.

## 2026-10-20 — T-087 vetted (ovl_7DF8 finish-the-TU)
- Worktree t3-ee1658a8. 8 functions match (1,716 B): func_801AD568, func_801C4780, func_801C4D28, func_801C4D6C, func_801C780C, func_801CBBE0, func_801CC0CC and func_801CC1A4. 5 improved, 8 unchanged. func_801C67CC has an exact body but needs its TU (ovl_7DF8_190B0) to own its rodata (yaml); that is the follow-up.
- Clean vet build: the ROM and all 3 images are byte-identical. 270 T4; M1 = M2 = 55,924 / 289,876 B (19.29%).
- T-090 launched (sol-A30): ovl_7DF8_190B0 rodata ownership to land func_801C67CC.

## 2026-10-20 — T-090 vetted (ovl_7DF8_190B0 rodata, func_801C67CC)
- Worktree t3-7a435a7f. ovl_7DF8_190B0 now owns .rodata 0xE7D10–0xE8DA0, and func_801C67CC matches (692 B).
- Clean vet build: the ROM and all 3 images are byte-identical. 271 T4; M1 = M2 = 56,616 / 289,876 B (19.53%).
- T-091 launched (sol-B30): rodata-ownership sweep across all main and ovl_7DF8 TUs.

## 2026-10-20 — T-089 vetted (permuter on equal-size main drafts)
- Worktree t3-386c77c3. func_80015F6C and func_8001256C match (624 B); 4 drafts improved, 1 unchanged.
- Clean vet build: the ROM and all 3 images are byte-identical. 273 T4; M1 = M2 = 57,240 / 289,876 B (19.75%).
- T-092 launched (sol-C34): permuter round 3 plus an equal-size screen of all drafts.

## 2026-10-20 — T-088 vetted (permuter round 2)
- Worktree t3-c3e99abb. 14 functions × 45-minute searches on 16 workers: 0 matches. func_8002F45C improved 13→11 (declaration order). Scratch-only changes; I imported the draft and report. These 14 (the glyph functions, func_801C4E38, func_801B6528, func_801B695C, func_801C5064, func_801C7998, func_801C6A80, family A, func_8002AA98/AAEC, func_80017378, func_8002A900) are the hardest residue.
- T-093 launched (sol-A31): finish the remaining stubs in main_2FF0 and main_D3F0.

## 2026-10-20 — T-091 vetted (rodata-ownership sweep)
- Worktree t3-d4515633. 10 more TUs own .rodata. Main: 1BE80, 1E7F0, 1EB40, 27490, 2B780. ovl_7DF8: 2380, 3F60, 116E0, 17E70, 1B790. Constants used by asm functions are kept via new function_owner hints (func_8002BBD0, func_8002E150, ...). 3 migrations were reverted because they didn't stay byte-identical. No additional draft became exact. Metrics unchanged. Clean vet build: the ROM and all 3 images are byte-identical.
- T-093 stopped on the Codex usage limit (resets 17:03). Cron 35ad101c resumes it at 17:06.

## 2026-10-20 — T-092 vetted (permuter round 3 + screen)
- Worktree t3-57500b83. tools/permuter/screen.py compiles every remaining T2 draft in TU context; the ranked table is in T-092/screen.md (all 230 compile). 6 matches (1,156 B): func_8002E4A0, func_800244F0, func_801C3580, func_801C35AC, func_801BF850 and func_801BFA40. 5 improved, 8 unchanged.
- Clean vet build: the ROM and all 3 images are byte-identical. 279 T4; M1 = M2 = 58,396 / 289,876 B (20.15%). Note: func_800244F0 was on paused T-093's list, so T-093 must drop it on resume.

## 2026-10-20 — T-093 vetted (main finish-the-TU round 2)
- Worktree t3-2bc90ca6 (resumed automatically after the limit). Its only match, func_800244F0, had already landed via T-092 (0acaa37), so its src change was dropped. 11 drafts improved and 22 unchanged in main_2FF0/main_D3F0; I imported the improved drafts and REPORT.md. The 17:06 resume cron was cancelled because it is no longer needed.
- Launched T-094 (permuter: never-permuted near-misses), T-095 (screen tier 20-49) and T-096 (the hard residue, instruction-level analysis).

## 2026-10-20 — T-096 vetted (hard residue, fresh eyes)
- Worktree t3-dbe9ade7. 3 of the residue match (572 B): func_8002AA98 and func_8002AAEC (reusing the incoming volume argument fixes the mflo a2/v0 register) and func_801C5064 (zero and depth go to the right FP registers via argument/value order). 16 unchanged, with instruction-level diagnoses in T-096/REPORT.md.
- Clean vet build: the ROM and all 3 images are byte-identical. 282 T4; M1 = M2 = 58,968 / 289,876 B (20.34%).
- T-097 launched (sol-C36): hard residue round 2 from T-096's diagnoses.

## 2026-10-20 — T-097 vetted (hard residue round 2): clone family A solved
- Worktree t3-540121f1. All 7 family-A functions match (func_801B2010/21B4/2358/24FC/26A0/2844/29E8, 420 B each), plus func_801C6A80: 3,232 B in total. The fix uses an explicit local pointer to each counter, `arg1++ < 1`, and `*counter = arg1` as the lerp's third argument (that recovers the jal delay-slot store), with token-preserving line grouping for the last two setup instructions. Honest C, commented. 8 residue functions remain.
- Clean vet build: the ROM and all 3 images are byte-identical. 290 T4; M1 = M2 = 62,200 / 289,876 B (21.46%). ovl_7DF8 is at 17.98%.
- T-095 stopped on the Codex usage limit (resets 21:15). Cron 94277b83 resumes it at 21:18.

## 2026-10-20 — T-094 vetted (permuter on never-permuted near-misses)
- Worktree t3-47b9f108. func_800281C4 and func_801C8F28 match (536 B). 4 drafts improved, 7 unchanged.
- Clean vet build: the ROM and all 3 images are byte-identical. 292 T4; M1 = M2 = 62,736 / 289,876 B (21.64%).

## 2026-10-20 — T-095 vetted (screen tier 20-49)
- Worktree t3-28bf0f96 (auto-resumed after the limit; cron 94277b83 cancelled). func_801B17BC and func_8002B034 match (696 B). 7 improved, 7 unchanged.
- Clean vet build: the ROM and all 3 images are byte-identical. 294 T4; M1 = M2 = 63,432 / 289,876 B (21.88%).
- Launched T-098 (family B), T-099 (screen refresh + closest drafts) and T-100 (screen tier 50-90).

## 2026-10-20 — T-098 vetted (clone family B)
- Worktree t3-334eee02. Family B is unsolved: all 6 drafts improved 65→57 words at the correct 536 B. The A-vs-B analysis and diagnosis are in T-098/REPORT.md. Drafts only; I imported them.
- T-101 launched (sol-A34): family B round 2 from T-098's diagnosis.

## 2026-10-20 — T-100 vetted (screen tier 50-90)
- Worktree t3-8db54426. 5 functions match (1,596 B): func_8002F5F0, func_80029AB0, func_801C0610, func_801C6D40 and func_801BED0C. 6 improved, 9 unchanged. Scratch trimmed to files under 40 KB.
- Clean vet build: the ROM and all 3 images are byte-identical. 299 T4; M1 = M2 = 65,028 / 289,876 B (22.43%).
- T-102 launched (sol-C38): screen tier 88-111.
- T-102 stopped on the Codex usage limit (resets 22:03). T3 usually resumes these itself; backup cron c1612fb1 at 22:06 resumes only workers still stopped.
- T-099 was interrupted near completion (limit). The 22:06 backup cron covers resuming it.
- T-101 was interrupted near completion (limit). Family B is at 19 words in its worktree. The 22:06 backup cron covers resuming it.

## 2026-10-20 — T-099 vetted (screen refresh + closest)
- Worktree t3-8ac95672 (resumed after the limit). The screen is refreshed in T-099/screen.md. func_801C3524, func_801C3990 and func_801BF988 match (548 B); 4 improved, 3 unchanged.
- Clean vet build: the ROM and all 3 images are byte-identical. 302 T4; M1 = M2 = 65,576 / 289,876 B (22.62%).

## 2026-10-20 — T-101 vetted (family B round 2)
- Worktree t3-6778d103. Family B is now 19 words per copy (from 57), at the correct 536 B; drafts only, so I imported the drafts and REPORT.md (region diagnoses). T-102 was resumed after the 22:03 reset.
- Launched T-103 (family B round 3) and T-104 (the closest drafts from the refreshed screen).

## 2026-10-20 — T-102 vetted (screen tier 88-111)
- Worktree t3-d2a0291f. func_801BE910 and func_80024B0C match (820 B). 5 improved, 13 unchanged.
- Clean vet build: the ROM and all 3 images are byte-identical. 304 T4; M1 = M2 = 66,396 / 289,876 B (22.90%).
- T-105 launched (sol-C39): the next untouched band of the screen.

## 2026-10-20 — T-104 vetted (refreshed-screen closest)
- Worktree t3-56794d05. func_801CCD74 matches (116 B); 5 improved, 15 unchanged (all 21 are diagnosed in T-104/REPORT.md).
- Clean vet build: the ROM and all 3 images are byte-identical. 305 T4; M1 = M2 = 66,512 / 289,876 B (22.94%).
- T-106 launched (sol-B34): clone family C (drafts consistently 32-36 B too long).

## 2026-10-20 — T-103 vetted (family B round 3)
- Worktree t3-c4895570. No change: family B is still 19 words ×6 after a region analysis and a 30-minute permuter run. Report only.
- T-107 launched (sol-A36): read-only docs/overview.md architecture map.

## 2026-10-20 — T-107 vetted (docs/overview.md)
- Worktree t3-51bd01e6. New 507-line architecture map: image lifetimes and load sequence; subsystems (scheduler, audio manager + sound player, input/pfs, rendering, frontend in ovl_7DF8, likely gameplay in ovl_7E00 at medium confidence); all 117 C TUs with roles and counts; open questions. Docs only.
- T-108 launched (sol-C40): subsystem pass on the game audio manager + sound player in main.

## 2026-10-20 — T-105 vetted (next screen band)
- Worktree t3-3ee1d324. 0 matched; 8 drafts improved (func_801CB998 36→2), 8 unchanged. Scratch-only changes; I imported the drafts and REPORT.md.
- T-109 launched (sol-A37): near-miss round on drafts at 11 words or fewer, from the T-104/T-105 diagnoses.

## 2026-10-20 — T-108 vetted (audio subsystem pass)
- Worktree t3-e9e242cf. include/audio_game.h (199 lines) holds the shared game-audio structs and prototypes. It is adopted in main_1AB90, main_1B230 and main_1EB40, replacing about 190 lines of duplicated per-function declarations, and all 29 existing matches are preserved. 0 new matches, 3 drafts improved.
- Clean vet build: the ROM and all 3 images are byte-identical. Metrics unchanged.
- T-110 launched (sol-B35): frontend subsystem pass (ovl_7DF8_13FF0 + 1BD90) with include/frontend.h.

## 2026-10-20 — T-106 vetted (clone family C)
- Worktree t3-f0ea162d. The shared structural cause of the uniform 32-36 B excess: the original caches scale values in locals; without them IDO recomputes coordinates across draw calls. 6 functions match (3,152 B): func_801BA088, func_801BA280, func_801BA470, func_801BA674, func_801BB024 and func_801BB594. Improved: func_801BB258 → 20 words, func_801BADEC → 118.
- Clean vet build: the ROM and all 3 images are byte-identical. 311 T4; M1 = M2 = 69,664 / 289,876 B (24.03%). ovl_7DF8 is at 22.30%.
- T-111 launched (sol-A38): clone-cluster finder over all drafts, then solve the largest clusters.

## 2026-10-21 — T-109 vetted (near-miss round)
- Worktree t3-272da6fb. func_801CB998, func_801BF678 and func_8001E0B4 match (964 B). func_8001BDE0 improved 9→8, 6 unchanged.
- Clean vet build: the ROM and all 3 images are byte-identical. 314 T4; M1 = M2 = 70,628 / 289,876 B (24.36%).
- T-112 launched (sol-C41): main rendering subsystem pass with include/render.h.

## 2026-10-21 — T-110 vetted (frontend subsystem pass)
- Worktree t3-ee5cdddd. include/frontend.h (219 lines) is adopted in ovl_7DF8_13FF0.c and _1BD90.c, and all 30 existing matches are preserved. It merged cleanly over T-109. 0 new matches; all 24 drafts now compile in full TUs, and func_801C8004 improved 110→47.
- Clean vet build: the ROM and all 3 images are byte-identical. Metrics unchanged (314 T4, 24.36%).
- T-113 launched (sol-B36): screen refresh #3 plus a diagnosis round on the closest 15.
- T-111 stopped on the Codex usage limit (resets 04:08). T3 auto-resume, or backup cron at 04:11.
- T-113 stopped on the Codex usage limit (resets 03:25). Backup cron at 03:28.
- T-112 stopped on the Codex usage limit (resets 03:25). The 03:28 cron covers it.
- 03:28: T-112 and T-113 were still stopped after the limit reset, so I resumed both by hand with 'continue'. T-111 waits for its 04:08 reset (cron 04:11).

## 2026-10-21 — T-112 vetted (main rendering subsystem pass)
- Worktree t3-b44de690. include/render.h (136 lines: camera, matrix, Gfx, stage-command and glyph types) is adopted in main_1BE80, main_1E7F0, main_20220 and main_20AE0, and all 17 existing matches are preserved. 0 new matches, 5 drafts improved.
- Clean vet build: the ROM and all 3 images are byte-identical. Metrics unchanged.
- Note: the subsystem-header passes (T-108, T-110, T-112) improve code quality and types but produced no direct matches; I am returning to diagnosis/clone/permuter tasks for matches.
- T-114 launched (sol-C42): hard residue round 3 with consolidated diagnoses.

## 2026-10-21 — T-113 vetted (screen refresh #3)
- Worktree t3-d83b2eba. 195 drafts screened (T-113/screen.md); 15 permuter searches. 0 matched. func_801C7998 has an exact body (its real input is one u64) but is blocked on rodata ownership of ovl_7DF8_1BD90, so I launched T-115. func_80017378 improved 8→6. I imported the drafts and screen.
- 04:11: T-111 was still stopped after the limit reset, so I resumed it by hand. T-112/T-113 were already done and vetted.

## 2026-10-21 — T-115 vetted (ovl_7DF8_1BD90 rodata, func_801C7998)
- Worktree t3-64192662. ovl_7DF8_1BD90 owns .rodata 0xE93F0–0xE9A10 (plus symbol hints), and func_801C7998 matches (256 B, a u64 input).
- Clean vet build: the ROM and all 3 images are byte-identical. 315 T4; M1 = M2 = 70,884 / 289,876 B (24.45%).
- T-116 launched (sol-B37): the least-attempted mid-distance drafts.

## 2026-10-21 — T-111 vetted (clone-cluster finder)
- Worktree t3-45905623. tools/analysis/clones.py writes docs/clones.md. Only 4 T2 clusters were found among 509 functions at threshold 0.85, so the remaining drafts are mostly unique. 0 new matches; func_801BADEC 118→106, func_801B5650/5DCC slight. Tool, docs and drafts only.
- T-117 launched (sol-C43): template-driven clones from docs/clones.md.

## 2026-10-21 — T-114 vetted (hard residue round 3)
- Worktree t3-25c065ff. func_8002F6F4 matches (516 B): swapping the `key` and `step` declarations fixed the sp+64/sp+74 slot. 9 unchanged after 30-minute searches; the consolidated per-function histories are in T-114/REPORT.md.
- Clean vet build: the ROM and all 3 images are byte-identical. 316 T4; M1 = M2 = 71,400 / 289,876 B (24.63%).
- T-118 launched (sol-A40): automated declaration-order and line-layout search over all drafts at 40 words or fewer.

## 2026-10-21 — T-117 vetted (template-driven clones)
- Worktree t3-773134aa. func_801BB258 (from the matched func_801BA674 template) and func_8001AD04 match (1,596 B). func_8001B134 has an exact code draft pending constant-pool integration (follow-up). Improved: func_801B3B84 → 16 words, func_801BADEC → 102.
- Clean vet build: the ROM and all 3 images are byte-identical. 318 T4; M1 = M2 = 72,996 / 289,876 B (25.18%). We pass 25% of game code.
- T-119 launched (sol-B38): land func_8001B134 by resolving its constant-pool ownership.

## 2026-10-21 — T-116 vetted (least-attempted mid drafts)
- Worktree t3-e7e76605. func_801C8C24 matches (408 B); 5 improved, 9 unchanged.
- Clean vet build: the ROM and all 3 images are byte-identical. 319 T4; M1 = M2 = 73,404 / 289,876 B (25.32%).
- T-120 launched (sol-C44): family B together with func_801B3B84.

## 2026-10-21 — T-118 vetted (declaration/layout search tool)
- Worktree t3-f9058a6f. tools/permuter/declorder.py (plus a README section) enumerates local-declaration orders, grouping and line joins/splits in TU context. 28 drafts at 40 words or fewer searched: 0 matched, func_8002A4F0 31→27. So the remaining near-misses are not bound by layout or declaration order; the cheap dimensions are exhausted. Tool and drafts only.
- T-121 launched (sol-A41): screen band 128-176, structure-first.

## 2026-10-21 — T-119 vetted (func_8001B134)
- Worktree t3-fd2df655. func_8001B134 matches (984 B). func_8001B50C now uses double literals and B134's 4 function_owner hints are removed; the undefined_syms files were regenerated.
- Clean vet build: the ROM and all 3 images are byte-identical. 320 T4; M1 = M2 = 74,388 / 289,876 B (25.66%).
- T-122 launched (sol-B39): screen band 176-219, structure-first.

## 2026-10-21 — T-121 vetted (screen band 128-176)
- Worktree t3-a7b7cc1a. func_801BEA74 matches (664 B). func_801B0A40 has exact text (668 B) but is blocked on constant-pool ownership (follow-up). 8 drafts improved.
- Clean vet build: the ROM and all 3 images are byte-identical. 321 T4; M1 = M2 = 75,052 / 289,876 B (25.89%).
- T-123 launched (sol-C45): constant placement for func_801B0A40.

## 2026-10-21 — T-120 and T-122 vetted
- T-120 (worktree t3-c15d80f7): func_801B3B84 matches (556 B). A shared mask/constant/alpha/store construct brings all six family-B copies from 19 to 7 words. The only zero for the residual was an artificial `if (counter) {}`, which was rejected.
- T-122 (worktree t3-3c530a29): 0 matched, 9 drafts improved. func_800131A4 went 178→41, func_801C3AA0 206→119 (exact size), func_801C1434 176→132 and func_801BBE88 184→150 (exact size).
- Clean vet build of both together: the ROM and all 3 images are byte-identical. 322 T4; M1 = M2 = 75,608 / 289,876 B (26.08%).
- New per-worker goal (user, 2026-10-21): at least 0.70% M2 per task (≥2,030 B). Fresh full screen: tools/scratch/nonmatching/screen-2026-10-21.md. Batches are now sized at 5–9 KB of candidates each.
- T-123 widened to the near-miss sweep (≤6 words, 5,948 B). T-124 (7–15-word band including family B, about 5.3 KB) and T-125 (high-byte mid band, about 9 KB) launched.
