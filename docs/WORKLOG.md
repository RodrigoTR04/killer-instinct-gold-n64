# Work log (append-only, newest at bottom)

Format: `YYYY-MM-DD | task ID | who | what changed | verification`

2026-10-18 | T-000 | lead | git init, .gitignore (ROMs excluded), baserom symlink to US V1.0, TRACKING.md | sha1 verified ba52e91b…
2026-10-18 | T-002 | sol-B → lead | docs/rom_layout.md + tools/analysis/{inspect_rom,compressed_blocks}.py | lead re-verified: IPL3 md5 (6102), entry words, all 27 table entries inflate to EOF, main sha1 81736d32…, RSP 2.0D string, 0xFF padding
2026-10-18 | T-003 | sol-C → lead | docs/research.md + tools/research/{revdiff,compression_probe}.py(+json) | lead re-verified: US1.0 vs 1.1 differ in [0x1000,0x100000) only at 0x7DF7–0x7EC7 (104 B, the segment table); US1.2 (−16) and EU (+16) shifted [0x8000,0x100000) byte-identical; IPL3 identical across all four. Web sources not re-fetched (marked as cited).
