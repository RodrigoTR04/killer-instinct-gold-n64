# T-008: byte-exact KI Gold compression

Verified 2026-10-18 against US V1.0 SHA1
`ba52e91b44450c548467044b26951353dc491e04`.

## Result and usage

**Solved: all 26 unique table payloads reproduce exactly**, including every
byte of the final DEFLATE byte. The duplicate at table 7EC0 also passes, as do
non-table streams at ROM 0x121F70 and 0x1F4290: 29/29 checks total.

```sh
python3 tools/compress/rarezip.py build/segments/main.bin /tmp/kig-t008/main.1172
python3 tools/compress/verify_all.py baserom.us.z64
python3 tools/compress/verify_all.py --json /tmp/kig-t008/verification.json
python3 tools/compress/compare_candidates.py
```

Python API: `from rarezip import compress`; `compress(data)` returns `11 72`
plus raw DEFLATE, without alignment. No ROM, manifest, extracted binary, or
original compressed bytes are needed by the compressor. Verification reads
the ROM directly, decompresses each stream in memory, recompresses, and compares
its complete bytes; it does not merely compare decompressed hashes.

## Exact method and source provenance

Use GoldenEye's gzip 1.2.4 source with `-n -9 -c` on standard input, remove
the 10-byte gzip header and 8-byte CRC32/ISIZE trailer, and prepend `11 72`.
There is no length field or gzip trailer in the KI wrapper.

Pinned upstream: [n64decomp/007, commit c435646](https://github.com/n64decomp/007/tree/c4356466796c697dfd298010b9bed261f9ed8c6a/tools/gzipsrc).
The [upstream 1172 wrapper](https://github.com/n64decomp/007/blob/c4356466796c697dfd298010b9bed261f9ed8c6a/tools/1172compress.sh)
uses the same framing and best-compression invocation. Our wrapper deliberately
has no fallback to the host gzip executable.

`rarezip.py` fetches the pinned codeload archive and checks SHA256
`26bf36f41e465616ee3d5df0e4767c7215200f93cd68a27765354f62e724858e`.
Only `tools/gzipsrc/` files are extracted, under `/tmp/kig-t008/gzip-<commit>/`.
Requires Python 3, network for the first build, and a C compiler (`CC`, default
`cc`). No sudo, packages, vendored third-party tree, or repository build-tree
changes are required. `-std=gnu89` accommodates K&R definitions on modern GCC;
no source patches were needed. The tested host is Linux x86-64. The cached
binary is reused; remove that cache directory to force a fresh verified build.
`--binary` can select a previously built binary for offline verification.
The `GZIP` environment variable is removed from compressor invocations.

Banjo prior art was also inspected: n64decomp/banjo-kazooie at
`e8d31fa53645616fcac6e051543222b973a2edb0` delegates compression to
[MittenzHugg/bk_rom_compressor](https://github.com/MittenzHugg/bk_rom_compressor/tree/d0d464e2f1ffc71497299288068a6925cd530789),
whose rarezip submodule is `https://github.com/MittenzHugg/rarezip.git`.
That alternative was not needed or built after GoldenEye's tool matched.
These source checkouts and downloads stayed under `/tmp/kig-t008/`.

## Full verification results

Sizes include the two-byte 1172 prefix, exclude padding. First differing byte
is absent for every row because the complete lengths and contents match.

| Table / asset ROM | Stream bytes | Expanded bytes | Zero padding | Result |
|---|---:|---:|---:|---|
| 7DF0 | 133755 | 239824 | 5 | PASS |
| 7DF8 | 308891 | 957392 | 5 | PASS |
| 7E00 | 81133 | 153904 | 3 | PASS |
| 7E08 | 14652 | 35760 | 4 | PASS |
| 7E10 | 12960 | 31264 | 0 | PASS |
| 7E18 | 11380 | 27712 | 12 | PASS |
| 7E20 | 12843 | 31200 | 5 | PASS |
| 7E28 | 11863 | 29440 | 9 | PASS |
| 7E30 | 12047 | 30208 | 1 | PASS |
| 7E38 | 13378 | 32928 | 14 | PASS |
| 7E40 | 12249 | 29408 | 7 | PASS |
| 7E48 | 12788 | 31696 | 12 | PASS |
| 7E50 | 12231 | 29712 | 9 | PASS |
| 7E58 | 8510 | 20336 | 2 | PASS |
| 7E60 | 44152 | 55824 | 8 | PASS |
| 7E68 | 88600 | 115520 | 8 | PASS |
| 7E70 | 86735 | 110480 | 1 | PASS |
| 7E78 | 87720 | 111344 | 8 | PASS |
| 7E80 | 41944 | 55504 | 8 | PASS |
| 7E88 | 102842 | 131664 | 6 | PASS |
| 7E90 | 89713 | 116192 | 15 | PASS |
| 7E98 | 61838 | 82736 | 2 | PASS |
| 7EA0 | 88278 | 122672 | 10 | PASS |
| 7EA8 | 80233 | 104480 | 7 | PASS |
| 7EB0 | 28155 | 39344 | 5 | PASS |
| 7EB8 | 7966 | 8384 | 2 | PASS |
| 7EC0 | 89713 | 116192 | 15 | PASS |
| asset_121F70 | 127 | 360 | not asserted | PASS |
| asset_1F4290 | 9326 | 34568 | not asserted | PASS |

## Compressor fingerprints and alternatives

`deflate_info.py` decodes block boundaries, literal and distance code lengths,
and literal/match token counts. It was run on all 26 unique table streams;
expanded lengths agree with zlib. They contain 94 dynamic blocks, one fixed
block, and no stored blocks. Byte-exact compression necessarily reproduces
all original block headers, code lengths, tokens, boundaries, and terminal bits.

Main has four dynamic blocks:

| Block | Raw start bit | Raw end bit | Expanded end | Literal/match tokens |
|---|---:|---:|---:|---:|
| 0 | 0 | 349071 | 75310 | 32767 |
| 1 | 349071 | 706363 | 155229 | 32767 |
| 2 | 706363 | 1055588 | 234752 | 32767 |
| 3 | 1055588 | 1070020 | 239824 | 1524 |

The large overlay has 29 dynamic blocks: the first two end at raw bit 356657
and 727778 (expanded 84110 and 189123), each with 32767 tokens. Subsequent
blocks commonly have 4096 tokens, with some 8192/12288-token blocks. Small
data 7E08 has two dynamic blocks, 8192 and 2483 tokens. Asset 121F70 has one
dynamic block (115 tokens); asset 1F4290 has two (4096 and 2488 tokens).

These counts agree with the pinned source's `LIT_BUFSIZE=0x8000` and its
32767-token capacity flush. The heuristic evaluates estimated output cost at
every 4096 tokens, and can flush earlier when there are relatively few matches
and estimated output is less than half the input. See
[trees.c](https://github.com/n64decomp/007/blob/c4356466796c697dfd298010b9bed261f9ed8c6a/tools/gzipsrc/trees.c).

Level 9 uses lazy matching with good length 32, max lazy 258, nice length 258,
and max chain 4096. Level 8 uses max lazy 128 and chain 1024. The source also
rejects length-three matches beyond distance 4096. See
[deflate.c](https://github.com/n64decomp/007/blob/c4356466796c697dfd298010b9bed261f9ed8c6a/tools/gzipsrc/deflate.c).
These are characteristics of the successfully tested compressor; they do not
prove which workstation/tool executable Rare originally ran.

Measured first differing **raw DEFLATE byte**, zero based (`match` means exact):

| Sample | gzip 1–3 | gzip 4 | gzip 5 | gzip 6 | gzip 7 | gzip 8 | gzip 9 |
|---|---|---:|---:|---:|---:|---:|---|
| main | 1 / 1 / 1 | 1 | 1 | 10 | 1 | 73281 | match |
| 7DF8 | 4 / 2 / 2 | 1 | 4 | 16 | 78 | 44587 | match |
| 7E08 | 0 / 0 / 0 | 32 | 2 | 23 | 23 | 11376 | match |
| asset 121F70 | 0 / 0 / 0 | 3 | match | match | match | match | match |
| asset 1F4290 | 0 / 0 / 1 | 1 | 1 | 2 | 2 | 2 | match |

Also tested zlib runtime **1.3.2**, raw `wbits=-15`, levels 1–9, memLevel 1–9,
strategies 0–4: 405 configurations per sample, 2025 total.

| Sample | Exact zlib configurations | Longest matching prefix when none match |
|---|---|---|
| main | level 9, memLevel 9, default strategy | — |
| 7DF8 | none | 90456 bytes (9, 9, default); output 313786 vs original 308889 bytes |
| 7E08 | none | 41 bytes (8, 7, default); output 14647 vs original 14650 bytes |
| asset 121F70 | levels 5–9, all memLevels, default strategy | — |
| asset 1F4290 | none | 5 bytes (2, 6, default); output 10247 vs original 9324 bytes |

Thus modern zlib can match main, but is insufficient for the whole corpus.
The old gzip flush heuristic explains the distinctive block counts; alternate
match-search parameters also change token choices and therefore trees. This is
not evidence that every zlib mismatch has one exclusive cause. Pigz, 7z and
zopfli were not tested: the pinned gzip candidate already meets the full goal.
`compare_candidates.py` regenerates the above level/configuration experiment
and writes full block metadata/code lengths to `/tmp/kig-t008/experiments.json`.

## Padding and boundaries

For **all 27 table entries**, `rom_end = (stream_end + 15) & ~15` and every
byte in `[stream_end, rom_end)` is `00`. A stream already aligned gets zero
padding bytes (7E10). Pad the complete prefix-plus-DEFLATE output, not the raw
DEFLATE length alone. These are ROM layout bytes, not part of `compress()`.

Main ends at `0xAB57FB`, then five zeros reach `0xAB5800`. The separate record
`[0xAB5800,0xAB5810)` is not padding; retain it independently. The next stream
starts at `0xAB5810`. All later unique table streams are contiguous at their
aligned bounds. 7EC0 reuses 7E90's same span. Final table end is `0xBFB020`;
the ROM's subsequent `FF` fill is a separate region.

For the non-table examples, stream ends are `0x121FEF` and `0x1F66FE`.
Both have zero bytes through the next 16-byte boundary (`0x121FF0` and
`0x1F6700` respectively), but no next-payload table was established here.
Do not generalize the table's packing rule to every scanned asset group.

No ROM-derived binaries are included, no ROM was written, and no commit was
created. Files outside `tools/compress/` and this document were not edited.
