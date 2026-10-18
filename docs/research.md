# T-003: KI Gold research and revision comparison

Research date: 2026-10-18. Primary target: US V1.0, SHA1 `ba52e91b44450c548467044b26951353dc491e04`. Findings below distinguish source-backed build settings, local measurements, and hypotheses. No ROM contents are redistributed; generated JSON contains offsets, sizes, hashes and statistics only.

## Sources and prior art

### KI Gold project search

No public KI Gold matching decompilation, full disassembly, symbol map, splat configuration or Ghidra database was identified in this search. **Confidence: medium for discoverability, not a claim that none exists.** Searches included the exact title with decompilation/disassembly/Ghidra/symbols/splat, GitHub repository search, and the following directories:

- [GitHub exact-title repository search](https://api.github.com/search/repositories?q=%22killer+instinct+gold%22): returned zero repositories on this run. Broad unquoted searches returned unrelated repositories. Repository search does not search all code or private projects.
- [Awesome N64 Development upstream directory](https://github.com/command-tab/awesome-n64-development#game-decompilation): no KI Gold entry identified; useful links to neighboring Rare projects. [n64.dev](https://n64.dev/) is its rendered directory (direct terminal fetch returned HTTP 403; web search exposed the directory).
- [decomp.dev](https://decomp.dev/) and [its former projects URL](https://decomp.dev/projects): direct fetch currently returns a page titled “Sunsetting decomp.dev”, so its historical project database could not be used to establish absence.
- [Decompilation Wiki program reconstruction list](https://decompilation.wiki/applications/program-reconstruction/): no KI Gold project identified.
- N64 Decomp Discord is linked by [the MK64 upstream README](https://github.com/n64decomp/mk64) at [discord.gg/DuYH3Fh](https://discord.gg/DuYH3Fh). Its internal project/wiki lists were **not accessible or verified** in this session. The attempted `https://n64decomp.github.io/wiki/` endpoint failed; it is not evidence of the contents of Discord's lists. Checking the live internal lists remains an open question.

Useful KI-specific prior art **does exist in extraction tools**, especially [SubDrag/jombo23's N64-Tools](https://github.com/jombo23/N64-Tools). These tools are not a KI Gold decompilation or a substitute for a symbol map.

### Contemporary compiler sources

These are settings used by public reconstruction projects, not recovered original Rare build scripts. Links were fetched directly; branches can change.

| Game | Compiler evidence and matching-build settings | Caveats |
| --- | --- | --- |
| GoldenEye 007 (1997) | [Makefile](https://github.com/n64decomp/007/blob/master/Makefile): IDO 5.3 recomp; `-O2` with `FINAL=YES`, `-mips2 -32`, `-G 0 -non_shared -Wab,-r4300_mul -Olimit 2000 -Xcpluscomm`. | `-g` belongs to the non-final debug branch, not evidence that retail KI used `-g`. |
| Blast Corps (1997) | [inner game Makefile](https://github.com/retroplastic/blastcorps/blob/master/blastcorps/Makefile): `ido5.3_recomp/cc`, **`-O1`**, `-mips2 -o32`, `-G 0 -non_shared -Wab,-r4300_mul -signed -nostdinc -Xcpluscomm`; some C recipes also explicitly pass `-32`. | WIP reconstruction; do not generalize one default to every original object. [README](https://github.com/retroplastic/blastcorps) documents compressed code extraction and linked older research. |
| Diddy Kong Racing (1997) | [tools Makefile](https://github.com/DavidSM64/Diddy-Kong-Racing/blob/master/tools/Makefile) downloads IDO **5.3**. [game Makefile](https://github.com/DavidSM64/Diddy-Kong-Racing/blob/master/Makefile): default game `-O2 -mips1`, `-G 0 -non_shared -Wab,-r4300_mul -Xcpluscomm -nostdinc`. | `-mips2` game default is for NON_MATCHING builds. SDK objects vary: many use mips2; OS/I/O often O1, audio often O3; `audio/env.c` uses `-g -mips1`; 64-bit libc helpers use mips3/32. |
| Banjo-Kazooie (1998) | [Makefile](https://github.com/n64decomp/banjo-kazooie/blob/master/Makefile): downloads IDO **5.3**; `-O2 -mips2 -G 0 -non_shared -Wab,-r4300_mul -Xcpluscomm`. | Audio directories have `-O3` overrides. No blanket retail `-g` in inspected defaults. |
| Donkey Kong 64 (1999) | [upstream Makefile](https://gitlab.com/dk64_decomp/dk64/-/blob/main/Makefile), [raw source](https://gitlab.com/dk64_decomp/dk64/-/raw/main/Makefile): `ido/ido5.3_recomp/cc`; `-O2 -mips2 -G 0 -non_shared -Wab,-r4300_mul -signed -Xcpluscomm`. | Explicit mips3 object lists include 64-bit helpers; includes reference 2.0L. Later game, weaker chronological comparator. |

GoldenEye and Blast Corps are the closest release-year comparators (1997 versus KI Gold's 1996); DKR is also 1997. All are Rare titles, but **shared studio is not proof of a shared programming team**. No primary source establishing a shared KI Gold compiler/build engineer or direct team continuity with these projects was found. Team proximity therefore remains unverified; do not rank a game as the same-team compiler precedent without credits/interview evidence.

## Compiler conclusion

**Recommendation: start with IDO 5.3; confidence medium for KI Gold, high that the five cited projects use it.** Try `-O2 -mips2 -32 -G 0 -non_shared -Wab,-r4300_mul -Xcpluscomm` as a first experiment, then test **O1** (Blast Corps precedent) and **mips1** (DKR precedent) before changing source aggressively. Treat `-signed`, `-Olimit 2000` and per-object options as variables, not established KI settings. Test `-g` only where unoptimized instruction patterns warrant it; it is not a universal Rare flag.

No KI-specific source presently establishes the compiler or flags. Confirm using several nontrivial game functions with control flow, float conversions and register pressure, keeping SDK/handwritten assembly separate. One tiny matching function is insufficient to identify optimization or ISA settings.

## Compression and assets

**1172 + raw DEFLATE is supported by tool source and locally validated (high confidence).** [GEDecompressorDlg.cpp](https://github.com/jombo23/N64-Tools/blob/master/GEDecompressor/GEDecompressorDlg.cpp) explicitly offers “Killer Instinct”, selects `KILLERINSTINCT`, scans ROM bytes for `11 72`, and calls its decompressor. [GECompression.cpp](https://github.com/jombo23/N64-Tools/blob/master/GEDecompressor/GECompression.cpp) skips two bytes for this mode and emits `11 72` when recompressing. This is the N64 tool's KI mode; it should not be confused with the arcade KI disk format.

Local stdlib probe: `python3 tools/research/compression_probe.py > tools/research/compression_probe.json`. It found **69** candidates in US V1.0 with a complete raw-DEFLATE stream, at least 16 output bytes, and bounded input/output. First successful stream: ROM `0x121F70`, 127 bytes including header → 360 bytes; another at `0x1F4290`, 9,326 → 34,568 bytes. This validates the wrapper but does not identify the semantic purpose of every stream. Signature scanning can produce false positives and misses non-1172 containers. The probe caps input at 2 MiB and output at 8 MiB; it is not an exhaustive archive extractor. It writes no decompressed assets.

Music/audio prior art (high confidence that configurations exist; extraction not executed here):

- [N64 MIDI Tool author's release post](https://www.therwp.com/forums/archive/index.php/t-41720.html) explicitly lists KI Gold and KI Gold 1.2 among supported/believed-supported games. This is primary author evidence for sequence extraction support, not proof every asset is understood.
- [Current `gameconfigmidi.ini`](https://github.com/jombo23/N64-Tools/blob/master/N64SoundbankTool/Release/gameconfigmidi.ini) lists all four revisions: US 1.0/1.1 `00992C74,009AF482`; US 1.2 `00992C64,009AF472`; E `00992C84,009AF492`. These are tool configuration values, not independently established archive boundaries/end conventions.
- [Current `gameconfigsound.ini`](https://github.com/jombo23/N64-Tools/blob/master/N64SoundbankTool/Release/gameconfigsound.ini) lists US 1.0/1.1 pairs `8F9FA0,907580` and `9AF4B0,9B9AD0`, with `{AllSamplingRate:22050}`; US 1.2 values are 16 bytes earlier, E 16 bytes later. N64 Soundbank Tool/N64 Sound Tool are extraction leads.

Unverified: sprite/animation packing, texture and palette tables, stage model/display-list containers, exact audio sample encoding, whether all graphics use 1172, and byte-exact recompression. Do not assume RNC, MIO0, Yay0, or Banjo's six-byte 1172 wrapper merely from other N64 games. Lossless decompression does not establish a matching compressor.

## libultra

**Exact KI Gold libultra version remains unknown (low confidence in a calendar-only guess).** 2.0H/2.0I/2.0J are candidates, not a result. Include **2.0G and earlier** in identification: the later DKR [Makefile](https://github.com/DavidSM64/Diddy-Kong-Racing/blob/master/Makefile) explicitly declares `BUILD_VERSION=VERSION_G` and `BUILD_VERSION_STRING="2.0G"`. SDK adoption can lag release dates. Match several version-sensitive OS/I/O routines and revision strings before selecting a library.

[decompals/ultralib compatibility matrix](https://github.com/decompals/ultralib#compatibility), fetched on the research date:

- 2.0I and 2.0J: IDO `libultra.a` and `libultra_rom.a` supported; IDO debug library not marked supported. GCC variants are marked supported including debug.
- 2.0H: IDO columns N/A, GCC unsupported; **not a supported matching target** in that matrix.
- 2.0E/F/G and 2.0I_patch: not marked supported. 2.0K/L release/ROM libraries are supported similarly to I/J.

Thus ultralib can help if KI identifies as I/J, but does not currently promise an H/G reconstruction. DKR's embedded library and other contemporary decomps can provide comparison references if it is older. No library build or archive comparison was performed in T-003.

## Revision diff

### Method and reproducibility

Run `python3 tools/research/revdiff.py --output tools/research/revdiff.json` from the repository. Python stdlib only; reads exactly the four `[!]` files and validates big-endian magic. All six pairwise comparisons are recorded. No bad/overdump/trainer ROMs were opened. All ROMs are 12,582,912 bytes.

Offsets below are **ROM offsets, hexadecimal, end exclusive**. Regions join unequal-byte runs separated by **at most 256 equal bytes** (`--gap 256`); region size includes intervening equal bytes, whereas changed count does not. The JSON preserves every region, header byte change, exact-run count and anchor result. `--gap 0` gives exact contiguous runs if needed. Comparisons are byte comparisons, not function matching or a code-segment inventory.

A supplementary relocation check samples nonconstant unique 256-byte anchors every 16 KiB from `0x1000` through the first MiB, searching ±64 KiB. It then compares the overlapping ROM tail from source `0x8000` using each observed displacement. The `0x8000` threshold is an analysis window, **not a claimed code boundary**. It excludes the early patch area and lets us distinguish shifted assets from globally rewritten content.

### Headers

All four share magic `80371240`, clock word `0000000F`, entrypoint `80000400`, release word `00001444` and identical bytes in the header except checksums, title case, region and revision as shown. Boot area `[0x40,0x1000)` is identical across all four.

| Revision | SHA1 | CRC1 / CRC2 | Title | ID / revision |
| --- | --- | --- | --- | --- |
| us10 | `ba52e91b44450c548467044b26951353dc491e04` | `9e8fe2ba / 8b270770` | KILLER INSTINCT GOLD | `NKIE` / 0 |
| us11 | `bcc599ed0f0b8b75a8068269958a2230ec7cb34c` | `9e8fcdfa / 49f5652b` | KILLER INSTINCT GOLD | `NKIE` / 1 |
| us12 | `aaeb492b1e538af65a3544a97240675ef438a04f` | `f908ca4c / 36464327` | Killer Instinct Gold | `NKIE` / 2 |
| eu | `e0ed97c7310b012a5cf81c6f6678a75b8601b47e` | `979b263e / f8470004` | Killer Instinct Gold | `NKIP` / 0 |

### Pairwise summary

| Pair | Changed bytes, same offset | Same-offset identical | First MiB changed | Anchor displacement | Shift-adjusted changed, tail | Tail identical |
| --- | ---: | ---: | ---: | --- | ---: | ---: |
| us10_vs_us11 | 1,460,904 | 88.38978% | 111 | +0 bytes (64 anchors) | 1,460,793 | 88.36035% |
| us10_vs_us12 | 12,316,744 | 2.11531% | 1,001,262 | -16 bytes (62 anchors) | 1,494,591 | 88.09105% |
| us10_vs_eu | 12,320,856 | 2.08263% | 1,004,249 | +16 bytes (62 anchors) | 1,631,273 | 87.00194% |
| us11_vs_us12 | 12,316,807 | 2.11481% | 1,001,263 | -16 bytes (62 anchors) | 1,494,811 | 88.08929% |
| us11_vs_eu | 12,320,912 | 2.08219% | 1,004,250 | +16 bytes (62 anchors) | 1,631,131 | 87.00307% |
| us12_vs_eu | 12,346,111 | 1.88193% | 1,004,928 | +32 bytes (62 anchors) | 1,597,119 | 87.27407% |

**Interpretation (high confidence in measurements; medium in effort estimate):** US 1.0→1.1 changes only 104 bytes in `[0x1000,0x100000)`, confined to `[0x7DF7,0x7EC8)`. It preserves all 64 sampled anchors at the same offset. The large other region starts at `0xA94D83`, well beyond the early-code window. Supporting 1.1 likely requires few early-code conditionals plus revision-specific late content; the whole-ROM change is not a tiny patch.

US 1.2 and E are **not same-offset patch-only versions**: 62 anchors match at −16 and +16 bytes relative to US 1.0, respectively. After applying those shifts, the entire source window `[0x8000,0x100000)` is byte-identical for every pair. This supports very substantial reuse, not a 98% rewrite as the naive diff suggests. The early region still has real edits/address adjustments; exact executable boundaries and RAM relocation need T-002 analysis. Do not interpret arbitrary first-MiB anchors as all executable code.

Across the overlapping tail from `0x8000`, shifted comparisons retain roughly 87–88% identity, leaving 1.46–1.63 million changed bytes. A multi-version architecture is likely affordable for shared early code, with per-version addresses/layout and retained original assets. Fully matching all revisions remains nontrivial until the late differences are classified/decompressed. EU timing/localization changes are not characterized here.

### All coalesced same-offset regions

These are full-ROM regions; rows starting below `0x100000` expose the early window. A region can cross that boundary; the JSON also provides separately clipped first-MiB regions.

#### us10_vs_us11

| Start | End (exclusive) | Span bytes | Changed bytes |
| --- | --- | ---: | ---: |
| `0x000012` | `0x000040` | 46 | 7 |
| `0x007DF7` | `0x007EC8` | 209 | 104 |
| `0xA94D83` | `0xBFB020` | 1,467,037 | 1,460,793 |

#### us10_vs_us12

| Start | End (exclusive) | Span bytes | Changed bytes |
| --- | --- | ---: | ---: |
| `0x000010` | `0x000040` | 48 | 24 |
| `0x001007` | `0x001198` | 401 | 10 |
| `0x0012C3` | `0x001550` | 653 | 20 |
| `0x001873` | `0x001878` | 5 | 2 |
| `0x001C0F` | `0x001E80` | 625 | 11 |
| `0x001FCB` | `0x002100` | 309 | 12 |
| `0x0022D3` | `0x0031B0` | 3,805 | 982 |
| `0x003347` | `0x00339C` | 85 | 6 |
| `0x0034CF` | `0x003724` | 597 | 15 |
| `0x00395B` | `0x003B0C` | 433 | 20 |
| `0x003C67` | `0x003C68` | 1 | 1 |
| `0x003DF7` | `0x004264` | 1,133 | 45 |
| `0x004567` | `0x004568` | 1 | 1 |
| `0x0046F7` | `0x0048A0` | 425 | 7 |
| `0x0049B7` | `0x004A4C` | 149 | 6 |
| `0x004B6B` | `0x004C74` | 265 | 8 |
| `0x004DDF` | `0x0050DC` | 765 | 11 |
| `0x0051DF` | `0x0051E0` | 1 | 1 |
| `0x0056AB` | `0x005760` | 181 | 8 |
| `0x005A23` | `0x005A24` | 1 | 1 |
| `0x005B27` | `0x005C4C` | 293 | 17 |
| `0x005D77` | `0x0060B4` | 829 | 22 |
| `0x006397` | `0x0063AC` | 21 | 5 |
| `0x006A5F` | `0x006FE4` | 1,413 | 41 |
| `0x007264` | `0x049DCB` | 273,255 | 266,018 |
| `0x049FC0` | `0x121D6B` | 884,139 | 868,487 |
| `0x121F60` | `0x1F3FFB` | 860,315 | 850,893 |
| `0x1F41F0` | `0x2CFE9B` | 900,267 | 886,091 |
| `0x2D0090` | `0x33C7EA` | 444,250 | 437,924 |
| `0x33C8F4` | `0x39D41B` | 396,071 | 389,994 |
| `0x39D610` | `0x47118B` | 867,195 | 855,891 |
| `0x471380` | `0x54E51B` | 905,627 | 891,453 |
| `0x54E710` | `0x60B7FB` | 774,379 | 762,796 |
| `0x60B9F0` | `0x6CF58B` | 801,691 | 789,554 |
| `0x6CF780` | `0x78567B` | 745,211 | 730,158 |
| `0x785870` | `0x82EC6B` | 693,243 | 683,185 |
| `0x82EE60` | `0x8E26CB` | 735,339 | 725,089 |
| `0x8E28C0` | `0x8E602B` | 14,187 | 13,358 |
| `0x8E6220` | `0x8FA656` | 82,998 | 81,152 |
| `0x8FA7AC` | `0x8FAB04` | 856 | 69 |
| `0x8FAC9C` | `0x8FACB6` | 26 | 10 |
| `0x8FAE39` | `0x9608BF` | 416,390 | 400,618 |
| `0x9609D9` | `0xBFB020` | 2,729,543 | 2,682,728 |

#### us10_vs_eu

| Start | End (exclusive) | Span bytes | Changed bytes |
| --- | --- | ---: | ---: |
| `0x000010` | `0x00003F` | 47 | 24 |
| `0x001007` | `0x001198` | 401 | 11 |
| `0x0012C3` | `0x001550` | 653 | 19 |
| `0x001873` | `0x001878` | 5 | 2 |
| `0x001BAF` | `0x001E80` | 721 | 12 |
| `0x001FCB` | `0x002100` | 309 | 12 |
| `0x002203` | `0x0031B0` | 4,013 | 114 |
| `0x003347` | `0x00339C` | 85 | 6 |
| `0x0034CF` | `0x003724` | 597 | 15 |
| `0x00395B` | `0x003B0C` | 433 | 20 |
| `0x003C67` | `0x003C68` | 1 | 1 |
| `0x003DF7` | `0x004568` | 1,905 | 74 |
| `0x00466B` | `0x004A4C` | 993 | 19 |
| `0x004B6B` | `0x004C74` | 265 | 9 |
| `0x004DDF` | `0x0050DC` | 765 | 11 |
| `0x0051DF` | `0x00520C` | 45 | 2 |
| `0x0056AB` | `0x0057BC` | 273 | 9 |
| `0x005A23` | `0x005A24` | 1 | 1 |
| `0x005B27` | `0x005C4C` | 293 | 20 |
| `0x005D6A` | `0x049DDB` | 278,641 | 269,916 |
| `0x049FD0` | `0x121D7B` | 884,139 | 868,487 |
| `0x121F70` | `0x1F400B` | 860,315 | 850,893 |
| `0x1F4200` | `0x2CFEAB` | 900,267 | 886,091 |
| `0x2D00A0` | `0x33C7FA` | 444,250 | 437,924 |
| `0x33C904` | `0x39D42B` | 396,071 | 389,994 |
| `0x39D620` | `0x47119B` | 867,195 | 855,891 |
| `0x471390` | `0x54E52B` | 905,627 | 891,453 |
| `0x54E720` | `0x60B80B` | 774,379 | 762,796 |
| `0x60BA00` | `0x6CF59B` | 801,691 | 789,554 |
| `0x6CF790` | `0x78568B` | 745,211 | 730,158 |
| `0x785880` | `0x82EC7B` | 693,243 | 683,185 |
| `0x82EE70` | `0x8E26DB` | 735,339 | 725,089 |
| `0x8E28D0` | `0x8E603B` | 14,187 | 13,358 |
| `0x8E6230` | `0x8FA666` | 82,998 | 81,152 |
| `0x8FA7BC` | `0x8FAB14` | 856 | 69 |
| `0x8FACAC` | `0x8FACC6` | 26 | 10 |
| `0x8FAE49` | `0x9608CF` | 416,390 | 400,618 |
| `0x9609E9` | `0xBFB280` | 2,730,135 | 2,683,837 |

#### us11_vs_us12

| Start | End (exclusive) | Span bytes | Changed bytes |
| --- | --- | ---: | ---: |
| `0x000010` | `0x000040` | 48 | 24 |
| `0x001007` | `0x001198` | 401 | 10 |
| `0x0012C3` | `0x001550` | 653 | 20 |
| `0x001873` | `0x001878` | 5 | 2 |
| `0x001C0F` | `0x001E80` | 625 | 11 |
| `0x001FCB` | `0x002100` | 309 | 12 |
| `0x0022D3` | `0x0031B0` | 3,805 | 982 |
| `0x003347` | `0x00339C` | 85 | 6 |
| `0x0034CF` | `0x003724` | 597 | 15 |
| `0x00395B` | `0x003B0C` | 433 | 20 |
| `0x003C67` | `0x003C68` | 1 | 1 |
| `0x003DF7` | `0x004264` | 1,133 | 45 |
| `0x004567` | `0x004568` | 1 | 1 |
| `0x0046F7` | `0x0048A0` | 425 | 7 |
| `0x0049B7` | `0x004A4C` | 149 | 6 |
| `0x004B6B` | `0x004C74` | 265 | 8 |
| `0x004DDF` | `0x0050DC` | 765 | 11 |
| `0x0051DF` | `0x0051E0` | 1 | 1 |
| `0x0056AB` | `0x005760` | 181 | 8 |
| `0x005A23` | `0x005A24` | 1 | 1 |
| `0x005B27` | `0x005C4C` | 293 | 17 |
| `0x005D77` | `0x0060B4` | 829 | 22 |
| `0x006397` | `0x0063AC` | 21 | 5 |
| `0x006A5F` | `0x006FE4` | 1,413 | 41 |
| `0x007264` | `0x049DCB` | 273,255 | 266,019 |
| `0x049FC0` | `0x121D6B` | 884,139 | 868,487 |
| `0x121F60` | `0x1F3FFB` | 860,315 | 850,893 |
| `0x1F41F0` | `0x2CFE9B` | 900,267 | 886,091 |
| `0x2D0090` | `0x33C7EA` | 444,250 | 437,924 |
| `0x33C8F4` | `0x39D41B` | 396,071 | 389,994 |
| `0x39D610` | `0x47118B` | 867,195 | 855,891 |
| `0x471380` | `0x54E51B` | 905,627 | 891,453 |
| `0x54E710` | `0x60B7FB` | 774,379 | 762,796 |
| `0x60B9F0` | `0x6CF58B` | 801,691 | 789,554 |
| `0x6CF780` | `0x78567B` | 745,211 | 730,158 |
| `0x785870` | `0x82EC6B` | 693,243 | 683,185 |
| `0x82EE60` | `0x8E26CB` | 735,339 | 725,089 |
| `0x8E28C0` | `0x8E602B` | 14,187 | 13,358 |
| `0x8E6220` | `0x8FA656` | 82,998 | 81,152 |
| `0x8FA7AC` | `0x8FAB04` | 856 | 69 |
| `0x8FAC9C` | `0x8FACB6` | 26 | 10 |
| `0x8FAE39` | `0x9608BF` | 416,390 | 400,618 |
| `0x9609D9` | `0xBFAFD0` | 2,729,463 | 2,682,790 |

#### us11_vs_eu

| Start | End (exclusive) | Span bytes | Changed bytes |
| --- | --- | ---: | ---: |
| `0x000010` | `0x000040` | 48 | 25 |
| `0x001007` | `0x001198` | 401 | 11 |
| `0x0012C3` | `0x001550` | 653 | 19 |
| `0x001873` | `0x001878` | 5 | 2 |
| `0x001BAF` | `0x001E80` | 721 | 12 |
| `0x001FCB` | `0x002100` | 309 | 12 |
| `0x002203` | `0x0031B0` | 4,013 | 114 |
| `0x003347` | `0x00339C` | 85 | 6 |
| `0x0034CF` | `0x003724` | 597 | 15 |
| `0x00395B` | `0x003B0C` | 433 | 20 |
| `0x003C67` | `0x003C68` | 1 | 1 |
| `0x003DF7` | `0x004568` | 1,905 | 74 |
| `0x00466B` | `0x004A4C` | 993 | 19 |
| `0x004B6B` | `0x004C74` | 265 | 9 |
| `0x004DDF` | `0x0050DC` | 765 | 11 |
| `0x0051DF` | `0x00520C` | 45 | 2 |
| `0x0056AB` | `0x0057BC` | 273 | 9 |
| `0x005A23` | `0x005A24` | 1 | 1 |
| `0x005B27` | `0x005C4C` | 293 | 20 |
| `0x005D6A` | `0x049DDB` | 278,641 | 269,916 |
| `0x049FD0` | `0x121D7B` | 884,139 | 868,487 |
| `0x121F70` | `0x1F400B` | 860,315 | 850,893 |
| `0x1F4200` | `0x2CFEAB` | 900,267 | 886,091 |
| `0x2D00A0` | `0x33C7FA` | 444,250 | 437,924 |
| `0x33C904` | `0x39D42B` | 396,071 | 389,994 |
| `0x39D620` | `0x47119B` | 867,195 | 855,891 |
| `0x471390` | `0x54E52B` | 905,627 | 891,453 |
| `0x54E720` | `0x60B80B` | 774,379 | 762,796 |
| `0x60BA00` | `0x6CF59B` | 801,691 | 789,554 |
| `0x6CF790` | `0x78568B` | 745,211 | 730,158 |
| `0x785880` | `0x82EC7B` | 693,243 | 683,185 |
| `0x82EE70` | `0x8E26DB` | 735,339 | 725,089 |
| `0x8E28D0` | `0x8E603B` | 14,187 | 13,358 |
| `0x8E6230` | `0x8FA666` | 82,998 | 81,152 |
| `0x8FA7BC` | `0x8FAB14` | 856 | 69 |
| `0x8FACAC` | `0x8FACC6` | 26 | 10 |
| `0x8FAE49` | `0x9608CF` | 416,390 | 400,618 |
| `0x9609E9` | `0xBFB280` | 2,730,135 | 2,683,892 |

#### us12_vs_eu

| Start | End (exclusive) | Span bytes | Changed bytes |
| --- | --- | ---: | ---: |
| `0x000010` | `0x000040` | 48 | 10 |
| `0x001007` | `0x001198` | 401 | 11 |
| `0x0012C3` | `0x001550` | 653 | 21 |
| `0x001873` | `0x001878` | 5 | 2 |
| `0x001BAF` | `0x001E80` | 721 | 12 |
| `0x001FCB` | `0x002100` | 309 | 12 |
| `0x002203` | `0x0031B0` | 4,013 | 995 |
| `0x003347` | `0x00339C` | 85 | 6 |
| `0x0034CF` | `0x003724` | 597 | 15 |
| `0x00395B` | `0x003B0C` | 433 | 20 |
| `0x003C67` | `0x003C68` | 1 | 1 |
| `0x003DF7` | `0x004568` | 1,905 | 74 |
| `0x00466B` | `0x004A4C` | 993 | 19 |
| `0x004B6B` | `0x004C74` | 265 | 9 |
| `0x004DDF` | `0x0050DC` | 765 | 11 |
| `0x0051DF` | `0x00520C` | 45 | 2 |
| `0x0056AB` | `0x0057BC` | 273 | 9 |
| `0x005A23` | `0x005A24` | 1 | 1 |
| `0x005B27` | `0x005C4C` | 293 | 20 |
| `0x005D6A` | `0x049DDB` | 278,641 | 269,228 |
| `0x049FC0` | `0x121D7B` | 884,155 | 869,801 |
| `0x121F60` | `0x1F400B` | 860,331 | 853,086 |
| `0x1F41F0` | `0x2CFEAB` | 900,283 | 888,277 |
| `0x2D0090` | `0x39D42B` | 840,603 | 830,411 |
| `0x39D610` | `0x47119B` | 867,211 | 857,701 |
| `0x471380` | `0x54E52B` | 905,643 | 892,983 |
| `0x54E710` | `0x60B80B` | 774,395 | 762,801 |
| `0x60B9F0` | `0x6CF59B` | 801,707 | 791,780 |
| `0x6CF780` | `0x78568B` | 745,227 | 731,541 |
| `0x785870` | `0x82EC7B` | 693,259 | 685,269 |
| `0x82EE60` | `0x8E26DB` | 735,355 | 726,490 |
| `0x8E28C0` | `0x8E603B` | 14,203 | 13,718 |
| `0x8E6220` | `0x8FA666` | 83,014 | 81,191 |
| `0x8FA7AC` | `0x8FAB14` | 872 | 82 |
| `0x8FAC9C` | `0x8FACC6` | 42 | 10 |
| `0x8FAE39` | `0x9608CF` | 416,406 | 402,064 |
| `0x9609D9` | `0xBFB280` | 2,730,151 | 2,688,428 |

### Shift-adjusted residual regions

Offsets refer to the source ROM in each pair; target offset = source + displacement. Header and `[0x1000,0x8000)` are excluded from this supplemental comparison.

| Pair | Delta | Start | End (exclusive) | Span bytes | Changed bytes |
| --- | ---: | --- | --- | ---: | ---: |
| us10_vs_us11 | +0 | `0xA94D83` | `0xBFB020` | 1,467,037 | 1,460,793 |
| us10_vs_us12 | -16 | `0xA6B3FE` | `0xA7397A` | 34,172 | 33,963 |
| us10_vs_us12 | -16 | `0xA94D87` | `0xBFB020` | 1,467,033 | 1,460,628 |
| us10_vs_eu | +16 | `0xA6B3FE` | `0xBFB270` | 1,638,002 | 1,631,273 |
| us11_vs_us12 | -16 | `0xA6B3FE` | `0xA7397A` | 34,172 | 33,963 |
| us11_vs_us12 | -16 | `0xA94D83` | `0xBFAFE0` | 1,466,973 | 1,460,848 |
| us11_vs_eu | +16 | `0xA6B3FE` | `0xBFB270` | 1,638,002 | 1,631,131 |
| us12_vs_eu | +32 | `0xA73973` | `0xBFB260` | 1,603,821 | 1,597,119 |

## Open questions and handoff

1. Confirm KI compiler flags with multiple byte-matched game functions; distinguish game objects from SDK and assembly.
2. Identify libultra by binary signatures; do not constrain the search to H–J.
3. Check the live N64 Decomp Discord project list and private/unindexed prior art.
4. Map early code and late changed regions; test whether the late delta is assets, compressed content, code, or a combination.
5. Decode sprite/animation/stage structures and establish byte-exact 1172 recompression.

Validation: completed all six comparisons on the four good dumps; SHA1s match the tracking prefixes/full primary hash. Confirmed all pairwise boot-area equality, zero shifted differences in `[0x8000,0x100000)`, and successfully decoded the 69 bounded probe candidates. No changes to TRACKING, no commits, and no use of `.venv` or `tools/ext`.
