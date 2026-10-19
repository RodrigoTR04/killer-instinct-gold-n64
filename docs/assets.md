# T-011: US 1.0 asset inventory

All ROM ranges are start inclusive, end exclusive. Verified against SHA1 `ba52e91b44450c548467044b26951353dc491e04`. The ROM was read only; no ROM-derived binary is included. CPU instruction addresses identify the decompressed image, never an offset inside its compressed ROM stream.

> **Correction (T-014, lead-verified 2026-10-18):** main-table +08/+0C blocks are Huffman decoding trees, not palettes; +18/+1C are arrays of 16-color RGBA5551 palettes; the 0x9900-byte 7DF8 images are 256×150 CI8 portraits with RGB888 palettes. See docs/gfx_format.md. These corrections are applied to assets.csv (T-017).

## Coverage and summary

The region `[0x007ED0,0xA94D80)` contains **11,062,960 bytes**. Referenced payload/table intervals cover **11,061,434 bytes (99.986206%)**. The remaining **1,526 bytes in 400 gaps** are explicitly unreferenced below and in the CSV. This accounts for every byte without silently extending audio samples to their next alignment boundary. Static references establish a loader path, not proof that every index executes in gameplay.

Counts below are unique top-level intervals, after merging identical references. The 825 self-sized graphics records and 17 length-prefixed compressed children are additional CSV rows and excluded from these totals. Parent containers can contain record headers and alignment bytes.

| Class | Count | ROM bytes | % region | Confidence |
|---|---:|---:|---:|---|
| audio_adpcm | 482 | 1,269,582 | 11.475970 | high |
| audio_bank | 2 | 97,280 | 0.879331 | high |
| audio_raw16 | 2 | 16,342 | 0.147718 | high |
| audio_sequence | 48 | 116,706 | 1.054926 | high |
| audio_sequence_index | 1 | 388 | 0.003507 | high |
| character_sprites | 23 | 9,231,216 | 83.442551 | high |
| huffman_tree | 13 | 53,248 | 0.481318 | high |
| metadata | 5 | 2,640 | 0.023863 | high |
| palette16 | 13 | 3,232 | 0.029215 | high |
| portrait_ci8 | 10 | 117,504 | 1.062139 | high |
| ui_sprites | 10 | 147,536 | 1.333603 | high |
| unreferenced | 400 | 1,526 | 0.013794 | unknown |
| unresolved | 12 | 5,760 | 0.052066 | unknown |

The 13 boot stage slots are also inventoried as 12 unique `stage_packet` rows (slot 12 aliases slot 6). They lie beyond this region, have depth 1 and parent `boot_stage_table`, and do not alter the depth-0 partition. Their 1172 bounds/hashes are measured in the same way.

## Reproduction and CSV contract

```sh
python3 tools/analysis/assets.py baserom.us.z64
python3 tools/analysis/assets.py baserom.us.z64 --output /tmp/assets.csv
```

The generator uses only Python standard library, validates the full source SHA1, decompresses main/7DF8 in memory, reads table fields and follows the audio pointer graph. It does not require `asm/` or extracted segment files. Analysis disassembly used `.venv/bin/python` and rabbitizer in `/tmp/kig-t011/`; source images were the verified extracted segments.

CSV fields give ROM bounds, sizes, hierarchy, classification/confidence, table slot or immediate-reference evidence, loader call instruction, compression bounds and SHA1s. Hex references without a ROM prefix are CPU addresses. `depth=0` rows (including gaps) form an exact disjoint partition; `depth=1` rows must not be added to coverage. For region containers they overlap their parent, whose ROM start is in `parent`; external stage rows use `boot_stage_table`. `compressed=n` means the entry itself is not a validated 1172 stream; it does not exclude child streams or another encoding. For a length-prefixed child, `stream_start=start+4`; its four-byte length field remains in the entry hash. `stream_end` includes the last DEFLATE byte, excludes trailing bytes. Expanded size/hash refer only to the inflated stream. Trailing size and whether all trailing bytes are zero are measured, not inferred from alignment. No payload bytes are serialized.

## Verified asset tables and consumers

| Table / location | Entries | Consumer / call site |
|---|---:|---|
| main CPU `80045E50–80046010` | 14 records, 4 ROM pairs each | indexed stride 32 at `80020F24–80020F44`, `800217B8–800217CC`; details below |
| 7DF8 CPU `80291FE8–80292038` | 10 ROM pairs | index*8 at `801C5F54–801C5F88`, DMA `801C5F84`, inflate `801C5FA4` |
| ROM `992AF0–992C74` | 48 offset/length records + 4-byte header | header DMA `8002A670`, full table DMA `8002A6BC`, relocation `8002A6D0`, sequence DMA `8002A950` / `8002AA20` |
| ROM `8F9FA0–907580`, B1 bank | 1 bank; 229 unique waves | DMA `8002A5B8`, bank relocation `8002A5C8` -> `80037874` |
| ROM `9AF4B0–9B9AD0`, B1 bank | 1 bank; 255 unique waves | DMA `8002A610`, bank relocation `8002A620` -> `80037874` |

Main record layout: +00/+04 packed-record bounds; +08/+0C two 0x800-byte Huffman tree blocks; +10/+14 small compressed data bounds; +18/+1C 16-color RGBA5551 palette arrays. The Huffman-tree reads are at `8002167C/8002169C` and `80021A78/80021A98`; palette reads at `8001D3CC/8001D414/8001D464` use base+character*32, DMA length 32. The small stream loader uses +10 at `80021B08–80021B20`, DMA `80021B1C`; its end is the adjacent table word. Semantic purpose of that expanded small data remains unresolved.

Large-record consumers `80020E98` and `800216D4` read little-endian IDs at +0 and record size at +4. The latter scans via that size (`80021824–80021860`) then fetches the selected record at `80021880`. The former can bulk load at `800213E4`, or decompress eleven BE-length-prefixed streams using `8002133C/8002136C`. Graphics packets are processed by `800238C4`, `800245B4` and rendering code. T-014 establishes the character sprite, tree, palette and portrait format classes; individual visual names remain unassigned.

| Index | CPU record | +00 packed data | +08 Huffman trees | +10 compressed data | +18 palette16 |
|---:|---|---|---|---|---|
| 0 | `80045E50` | `0566D0–120F70` | `120F70–121F70` | `121F70–121FF0` | `007F10–008030` |
| 1 | `80045E70` | `121FF0–1EB6D0` | `1F3200–1F4200` | `1F4200–1F4290` | `008030–008150` |
| 2 | `80045E90` | `1F7780–2C2280` | `2CF0A0–2D00A0` | `2D00A0–2D0130` | `008150–008270` |
| 3 | `80045EB0` | `2D0130–39C620` | `39C620–39D620` | `39D620–39D6A0` | `008270–008390` |
| 4 | `80045ED0` | `39D6A0–469660` | `470390–471390` | `471390–471440` | `008390–0084B0` |
| 5 | `80045EF0` | `472FB0–53CC40` | `54D720–54E720` | `54E720–54E7D0` | `0084B0–0085D0` |
| 6 | `80045F10` | `551E60–60AA00` | `60AA00–60BA00` | `60BA00–60BA70` | `0085D0–0086F0` |
| 7 | `80045F30` | `60BA70–6CE790` | `6CE790–6CF790` | `6CF790–6CF860` | `0086F0–008810` |
| 8 | `80045F50` | `6CF860–784880` | `784880–785880` | `785880–785910` | `008810–008930` |
| 9 | `80045F70` | `785910–82DE70` | `82DE70–82EE70` | `82EE70–82EEF0` | `008930–008A50` |
| 10 | `80045F90` | `82EEF0–8E18D0` | `8E18D0–8E28D0` | `8E28D0–8E2980` | `008A50–008B50` |
| 11 | `80045FB0` | `8E6230–8F6AE0` | `8E18D0–8E28D0` | `8E28D0–8E2980` | `008A50–008B50` |
| 12 | `80045FD0` | `02ECB0–048FD0` | `048FD0–049FD0` | `8E28D0–8E2980` | `007ED0–007F10` |
| 13 | `80045FF0` | `8E2980–8E5230` | `8E5230–8E6230` | `8E28D0–8E2980` | `008B50–008B70` |

Index 11 reuses index 10 palette/small stream/index bounds; indices 12 and 13 also reuse the small stream. Duplicate ranges retain all table-slot references in one CSV row. Index 12 supplies the first 64 bytes of the asset region.

### 7DF8 compressed graphics table

The consumer converts expanded bytes into RGBA5551-like words at `801C5FC4–801C600C`. Each expands to 0x9900 bytes: a 0x300-byte RGB888 palette followed by 256×150 CI8 pixels, verified by T-014. Character identities remain unnamed. The ROM order differs from table index order.

| Slot CPU | ROM span | Expanded bytes | Trailing zero bytes |
|---|---|---:|---:|
| `80291FE8` | `A77960–A7B330` | 39168 | 9 |
| `80291FF0` | `A7B330–A7E6F0` | 39168 | 2 |
| `80291FF8` | `A7E6F0–A814D0` | 39168 | 15 |
| `80292000` | `A814D0–A83F90` | 39168 | 2 |
| `80292010` | `A83F90–A86550` | 39168 | 15 |
| `80292008` | `A86550–A89B20` | 39168 | 15 |
| `80292020` | `A89B20–A8BC50` | 39168 | 2 |
| `80292028` | `A8BC50–A8E2B0` | 39168 | 8 |
| `80292030` | `A8E2B0–A910F0` | 39168 | 10 |
| `80292018` | `A910F0–A94460` | 39168 | 8 |

### Immediate ROM ranges

These complete the table coverage. Loader addresses are jal instruction addresses; each calls `80000740` or `800007B4`. Branch-specific immediate values were checked in the instruction windows, including both alternatives at `800281FC`.

| ROM span | Class | DMA call(s) |
|---|---|---|
| `008B70–0119F0` | ui_sprites | `800244B0;80024570` |
| `0119F0–013200` | ui_sprites | `80021594;80024428` |
| `013200–01D640` | character_sprites | `80024234` |
| `01D640–024D60` | character_sprites | `800242DC` |
| `024D60–02ECB0` | character_sprites | `8002431C` |
| `049FD0–0566D0` | character_sprites | `80021880` |
| `1EB6D0–1F3200` | character_sprites | `800247A0;80021880` |
| `1F4290–1F6700` | ui_sprites | `80014270` |
| `1F6700–1F7780` | ui_sprites | `800142AC` |
| `2C2280–2CF0A0` | character_sprites | `80024814` |
| `469660–470390` | character_sprites | `800248F0;80021880` |
| `471440–472FB0` | ui_sprites | `8002435C` |
| `53CC40–543D10` | character_sprites | `80024964` |
| `543D10–54D720` | character_sprites | `800243B4` |
| `54E7D0–551E60` | ui_sprites | `80013CA4` |
| `8F6AE0–8F9FA0` | ui_sprites | `80024D2C` |
| `8F9FA0–907580` | audio_bank | `8002A5B8` |
| `992AF0–992C74` | audio_sequence_index | `8002A670;8002A6BC` |
| `9AF4B0–9B9AD0` | audio_bank | `8002A610` |
| `A68A20–A69A20` | unresolved | `8001BB30` |
| `A69A20–A69A40` | metadata | `800281FC` |
| `A69A40–A69A70` | metadata | `800281FC` |
| `A69A70–A6A990` | ui_sprites | `800123BC` |
| `A6A990–A6AA70` | metadata | `80012484` |
| `A6AA70–A73980` | ui_sprites | `801ADF38` |
| `A73980–A77960` | ui_sprites | `801AC384` |
| `A94460–A94560` | metadata | `80020F70` |
| `A94560–A94D80` | metadata | `80020F94` |

### Audio verification

Both controls have big-endian magic 0x4231 (`B1`), one bank, and sample rate 22050. Bank traversal follows bank instrument count/+0C pointer array (plus percussion +08), instrument sound count/+0E and sound pointers/+10, sound wavetable/+08, then wavetable sample offset/+00, byte length/+04 and type/+08. `80037874` verifies B1 and relocates the bank; `80037780` follows those structures and `80037808` adds the ROM sample base. Wavetable type 0 is ADPCM, type 1 raw16. Across both banks there are **482 ADPCM and 2 raw16** unique sample spans. Every wavetable reference is retained in the CSV; these are code-referenced indirect entries, not signature guesses. Audio sample DMA ultimately issues `osPiStartDma` at `8002B37C`, reading 0x800-byte cache blocks, so transfers may also touch the gaps.

Bank 1 samples occupy named spans between `907580` and `992AEC`; bank 2 between `9B9AD0` and `A68A18`. Control ranges include their own internal offsets/padding. They are not themselves the complete audio sample banks.

Sequence header magic is 0x5331 (`S1`), count 48. `80037978` adds ROM base `992AF0` to each table offset. The first sequence starts `992C74`; the final entry is `[9AF420,9AF4A3)`, correcting the third-party config bound `9AF482`. Entries are N64 sequence data, not standard `MThd` files. Sequence DMA rounds odd lengths up to an even transfer size at `8002A724–8002A734`; CSV bounds retain the exact declared lengths. Playback decoding was not performed.

### Compression and record boundaries

All 1172-positive rows reach raw-DEFLATE EOF within their recorded entry. There are 25 top-level streams plus 17 length-prefixed child streams (42 total). The groups `[8E6230,8F6AE0)` and `[8F6AE0,8F9FA0)` contain eleven and six BE-size-prefixed streams, respectively. Each child length includes its four-byte length word plus the complete 1172 stream; child stream trailing lengths are zero. The eleven-stream path is explicitly implemented at `80021360–800213C4`; the second group is loaded by `80024D2C`. Small alignment bytes after other streams remain part of their referenced interval and are measured in CSV. Recompression is already solved by T-008; this inventory checks decompression, not byte-exact recompression of all 42 streams.

825 little-endian self-sized records were enumerated inside raw graphics containers. Residual container bytes remain accounted under their parent, without inventing new records. Container bounds do not imply every internal byte is separately referenced.

## Verified facts versus hypotheses / limits

Verified: source hash; ROM-pair values; static indexed/immediate DMA paths; exact disjoint top-level coverage; bank pointer graph and rates; sequence table/count/lengths; complete DEFLATE EOF and hashes; self-size record arithmetic. All 400 gaps lie in or beside the audio sample/sequence region.

Hypotheses: exact visual names, character/stage ordering, animation versus sprite versus font ownership, image dimensions and the purpose of the small compressed data. `character_sprites`, `ui_sprites`, `huffman_tree`, `palette16` and `portrait_ci8` apply the verified T-014 format distinctions; exact visual identities remain unnamed. `unresolved` is retained for eleven unique small compressed/table-derived spans and one raw 0x1000 block; these have verified references but no established semantic identity. No claim is made that the full graphics encoding has been decoded.

Exhaustiveness is byte accounting at the referenced container level, not recovery of every original source asset. Direct DMA call sites in all three CPU images and aligned ROM-word runs in initialized data were inspected without using `asm/`; instruction-like RSP words and packed byte data were excluded as spurious tables. Arithmetic addressing and runtime index reachability can introduce additional aliases. The generator deliberately records verified tables and paths rather than treating every integer in range as a reference.

## Complete unreferenced gap list

Unreferenced means outside named payload intervals in this inventory, not unreachable. No gap is silently promoted to a referenced asset or folded into its predecessor. Content is recorded here only as an aggregate observation: 380 of 400 gaps contain only zero bytes. The remaining bytes are preserved by their hashes. Alignment padding is a hypothesis even when all bytes are zero.

| ROM start | ROM end | Bytes |
|---|---|---:|
| `9088C4` | `9088C8` | 4 |
| `908C7A` | `908C80` | 6 |
| `9093BE` | `9093C0` | 2 |
| `9094CE` | `9094D0` | 2 |
| `909CD4` | `909CD8` | 4 |
| `90A122` | `90A128` | 6 |
| `90B274` | `90B278` | 4 |
| `90BC0A` | `90BC10` | 6 |
| `90D036` | `90D038` | 2 |
| `90D1F2` | `90D1F8` | 6 |
| `90DC84` | `90DC88` | 4 |
| `90DE42` | `90DE48` | 6 |
| `90E1FA` | `90E200` | 6 |
| `90EB1C` | `90EB20` | 4 |
| `90F3AC` | `90F3B0` | 4 |
| `9103C2` | `9103C8` | 6 |
| `910DD6` | `910DD8` | 2 |
| `911436` | `911438` | 2 |
| `91218C` | `912190` | 4 |
| `9131E2` | `9131E8` | 6 |
| `91382A` | `913830` | 6 |
| `913E8E` | `913E90` | 2 |
| `915762` | `915768` | 6 |
| `915BC4` | `915BC8` | 4 |
| `916322` | `916328` | 6 |
| `916E06` | `916E08` | 2 |
| `918104` | `918108` | 4 |
| `91C926` | `91C928` | 2 |
| `91D98A` | `91D990` | 6 |
| `91EEAA` | `91EEB0` | 6 |
| `920E94` | `920E98` | 4 |
| `921586` | `921588` | 2 |
| `9220DA` | `9220E0` | 6 |
| `92297E` | `922980` | 2 |
| `925B9A` | `925BA0` | 6 |
| `926594` | `926598` | 4 |
| `92845C` | `928460` | 4 |
| `928F8E` | `928F90` | 2 |
| `92A496` | `92A498` | 2 |
| `92DF46` | `92DF48` | 2 |
| `92F164` | `92F168` | 4 |
| `92F7A2` | `92F7A8` | 6 |
| `93054C` | `930550` | 4 |
| `93112A` | `931130` | 6 |
| `932922` | `932928` | 6 |
| `934014` | `934018` | 4 |
| `93430C` | `934310` | 4 |
| `93553E` | `935540` | 2 |
| `9358FA` | `935900` | 6 |
| `93821C` | `938220` | 4 |
| `938A52` | `938A58` | 6 |
| `939482` | `939488` | 6 |
| `93B23E` | `93B240` | 2 |
| `93BD02` | `93BD08` | 6 |
| `93C39C` | `93C3A0` | 4 |
| `93EE34` | `93EE38` | 4 |
| `9402DC` | `9402E0` | 4 |
| `942A02` | `942A08` | 6 |
| `943204` | `943208` | 4 |
| `94373C` | `943740` | 4 |
| `944AB2` | `944AB8` | 6 |
| `9456B6` | `9456B8` | 2 |
| `9460C6` | `9460C8` | 2 |
| `946AD6` | `946AD8` | 2 |
| `946FB2` | `946FB8` | 6 |
| `9471B2` | `9471B8` | 6 |
| `9473D4` | `9473D8` | 4 |
| `9478AA` | `9478B0` | 6 |
| `948172` | `948178` | 6 |
| `9485DE` | `9485E0` | 2 |
| `948A84` | `948A88` | 4 |
| `94923C` | `949240` | 4 |
| `9498D4` | `9498D8` | 4 |
| `94A27A` | `94A280` | 6 |
| `94AA6A` | `94AA70` | 6 |
| `94B8DA` | `94B8E0` | 6 |
| `94C5E2` | `94C5E8` | 6 |
| `94D384` | `94D388` | 4 |
| `94DB32` | `94DB38` | 6 |
| `94E454` | `94E458` | 4 |
| `950576` | `950578` | 2 |
| `9513BE` | `9513C0` | 2 |
| `951B1A` | `951B20` | 6 |
| `95255C` | `952560` | 4 |
| `952DB6` | `952DB8` | 2 |
| `9532F6` | `9532F8` | 2 |
| `9534C4` | `9534C8` | 4 |
| `9536A6` | `9536A8` | 2 |
| `953E1C` | `953E20` | 4 |
| `9558E2` | `9558E8` | 6 |
| `957EBC` | `957EC0` | 4 |
| `95874C` | `958750` | 4 |
| `958C06` | `958C08` | 2 |
| `95B3CC` | `95B3D0` | 4 |
| `9603BA` | `9603C0` | 6 |
| `9610CC` | `9610D0` | 4 |
| `962396` | `962398` | 2 |
| `9627DA` | `9627E0` | 6 |
| `963D6E` | `963D70` | 2 |
| `964202` | `964208` | 6 |
| `965B1C` | `965B20` | 4 |
| `96683E` | `966840` | 2 |
| `96730C` | `967310` | 4 |
| `967CCE` | `967CD0` | 2 |
| `969162` | `969168` | 6 |
| `9693C4` | `9693C8` | 4 |
| `969876` | `969878` | 2 |
| `96A796` | `96A798` | 2 |
| `96C0AA` | `96C0B0` | 6 |
| `96C176` | `96C178` | 2 |
| `96C25A` | `96C260` | 6 |
| `96C354` | `96C358` | 4 |
| `96C442` | `96C448` | 6 |
| `96C532` | `96C538` | 6 |
| `96C62C` | `96C630` | 4 |
| `96C724` | `96C728` | 4 |
| `96C7DC` | `96C7E0` | 4 |
| `96C8D4` | `96C8D8` | 4 |
| `96C9DE` | `96C9E0` | 2 |
| `96EBC6` | `96EBC8` | 2 |
| `96FCB2` | `96FCB8` | 6 |
| `96FDF4` | `96FDF8` | 4 |
| `970266` | `970268` | 2 |
| `970526` | `970528` | 2 |
| `970676` | `970678` | 2 |
| `97141C` | `971420` | 4 |
| `97174A` | `971750` | 6 |
| `971E2C` | `971E30` | 4 |
| `97234A` | `972350` | 6 |
| `973146` | `973148` | 2 |
| `973A12` | `973A18` | 6 |
| `973E86` | `973E88` | 2 |
| `9748B2` | `9748B8` | 6 |
| `975426` | `975428` | 2 |
| `97877C` | `978780` | 4 |
| `97ACC6` | `97ACC8` | 2 |
| `97B1B4` | `97B1B8` | 4 |
| `97BF3A` | `97BF40` | 6 |
| `97C1D2` | `97C1D8` | 6 |
| `97C48E` | `97C490` | 2 |
| `97CD2E` | `97CD30` | 2 |
| `97D14E` | `97D150` | 2 |
| `97D3A2` | `97D3A8` | 6 |
| `97D73E` | `97D740` | 2 |
| `97DAC4` | `97DAC8` | 4 |
| `97E7CA` | `97E7D0` | 6 |
| `97F71E` | `97F720` | 2 |
| `97F84A` | `97F850` | 6 |
| `97F95E` | `97F960` | 2 |
| `97FA8A` | `97FA90` | 6 |
| `97FBBA` | `97FBC0` | 6 |
| `97FD0E` | `97FD10` | 2 |
| `980376` | `980378` | 2 |
| `98109E` | `9810A0` | 2 |
| `9829B2` | `9829B8` | 6 |
| `985134` | `985138` | 4 |
| `986A1E` | `986A20` | 2 |
| `98773E` | `987740` | 2 |
| `988B66` | `988B68` | 2 |
| `989754` | `989758` | 4 |
| `989FA4` | `989FA8` | 4 |
| `98B8D6` | `98B8D8` | 2 |
| `98C0E6` | `98C0E8` | 2 |
| `98C5D4` | `98C5D8` | 4 |
| `98CBDC` | `98CBE0` | 4 |
| `98D22C` | `98D230` | 4 |
| `98D872` | `98D878` | 6 |
| `98DF6E` | `98DF70` | 2 |
| `98EA7A` | `98EA80` | 6 |
| `98F0DE` | `98F0E0` | 2 |
| `98FDA4` | `98FDA8` | 4 |
| `9908CE` | `9908D0` | 2 |
| `992AEC` | `992AF0` | 4 |
| `993C67` | `993C68` | 1 |
| `993DED` | `993DF0` | 3 |
| `9953BD` | `9953C0` | 3 |
| `9958F3` | `9958F4` | 1 |
| `995C31` | `995C34` | 3 |
| `9979EF` | `9979F0` | 1 |
| `997BF3` | `997BF4` | 1 |
| `99960D` | `999610` | 3 |
| `999CAD` | `999CB0` | 3 |
| `99A84A` | `99A84C` | 2 |
| `99BA3E` | `99BA40` | 2 |
| `99BE4E` | `99BE50` | 2 |
| `99C173` | `99C174` | 1 |
| `99C5E9` | `99C5EC` | 3 |
| `99D4DA` | `99D4DC` | 2 |
| `99D82A` | `99D82C` | 2 |
| `99DA3E` | `99DA40` | 2 |
| `99FB32` | `99FB34` | 2 |
| `9A0086` | `9A0088` | 2 |
| `9A053B` | `9A053C` | 1 |
| `9A1E0A` | `9A1E0C` | 2 |
| `9A221A` | `9A221C` | 2 |
| `9A2411` | `9A2414` | 3 |
| `9A4653` | `9A4654` | 1 |
| `9A5925` | `9A5928` | 3 |
| `9A5F99` | `9A5F9C` | 3 |
| `9A60FA` | `9A60FC` | 2 |
| `9A96BE` | `9A96C0` | 2 |
| `9A9B4B` | `9A9B4C` | 1 |
| `9A9E17` | `9A9E18` | 1 |
| `9AA085` | `9AA088` | 3 |
| `9AAE83` | `9AAE84` | 1 |
| `9AB0FA` | `9AB0FC` | 2 |
| `9AC5C3` | `9AC5C4` | 1 |
| `9AE947` | `9AE948` | 1 |
| `9AEA7F` | `9AEA80` | 1 |
| `9AEC09` | `9AEC0C` | 3 |
| `9AF2B7` | `9AF2B8` | 1 |
| `9AF3BA` | `9AF3BC` | 2 |
| `9AF41E` | `9AF420` | 2 |
| `9AF4A3` | `9AF4B0` | 13 |
| `9B9F12` | `9B9F18` | 6 |
| `9BAABC` | `9BAAC0` | 4 |
| `9BB262` | `9BB268` | 6 |
| `9BBEF6` | `9BBEF8` | 2 |
| `9BCA9C` | `9BCAA0` | 4 |
| `9BE9EA` | `9BE9F0` | 6 |
| `9BF00E` | `9BF010` | 2 |
| `9BF934` | `9BF938` | 4 |
| `9C05F2` | `9C05F8` | 6 |
| `9C103E` | `9C1040` | 2 |
| `9C1B66` | `9C1B68` | 2 |
| `9C22CC` | `9C22D0` | 4 |
| `9C2D0C` | `9C2D10` | 4 |
| `9C3886` | `9C3888` | 2 |
| `9C5056` | `9C5058` | 2 |
| `9C5F4A` | `9C5F50` | 6 |
| `9C6542` | `9C6548` | 6 |
| `9C79E2` | `9C79E8` | 6 |
| `9C98F4` | `9C98F8` | 4 |
| `9CAA4E` | `9CAA50` | 2 |
| `9CBFD4` | `9CBFD8` | 4 |
| `9CD1BE` | `9CD1C0` | 2 |
| `9CDE72` | `9CDE78` | 6 |
| `9CF216` | `9CF218` | 2 |
| `9D0686` | `9D0688` | 2 |
| `9D336E` | `9D3370` | 2 |
| `9D4A8A` | `9D4A90` | 6 |
| `9D60FE` | `9D6100` | 2 |
| `9D83B4` | `9D83B8` | 4 |
| `9D9B1A` | `9D9B20` | 6 |
| `9DA54A` | `9DA550` | 6 |
| `9DC266` | `9DC268` | 2 |
| `9DCBCC` | `9DCBD0` | 4 |
| `9DDBFC` | `9DDC00` | 4 |
| `9DE95C` | `9DE960` | 4 |
| `9DF4FA` | `9DF500` | 6 |
| `9E01BA` | `9E01C0` | 6 |
| `9E1D36` | `9E1D38` | 2 |
| `9E4996` | `9E4998` | 2 |
| `9E5286` | `9E5288` | 2 |
| `9E5454` | `9E5458` | 4 |
| `9E561A` | `9E5620` | 6 |
| `9E5776` | `9E5778` | 2 |
| `9E5874` | `9E5878` | 4 |
| `9E66EE` | `9E66F0` | 2 |
| `9E6A74` | `9E6A78` | 4 |
| `9E70B2` | `9E70B8` | 6 |
| `9E790E` | `9E7910` | 2 |
| `9E822C` | `9E8230` | 4 |
| `9E890C` | `9E8910` | 4 |
| `9E8DFC` | `9E8E00` | 4 |
| `9E9644` | `9E9648` | 4 |
| `9EA084` | `9EA088` | 4 |
| `9EB1C2` | `9EB1C8` | 6 |
| `9EB556` | `9EB558` | 2 |
| `9EB8E6` | `9EB8E8` | 2 |
| `9EC06E` | `9EC070` | 2 |
| `9EC812` | `9EC818` | 6 |
| `9ECC3E` | `9ECC40` | 2 |
| `9ED32E` | `9ED330` | 2 |
| `9EE412` | `9EE418` | 6 |
| `9EEF1A` | `9EEF20` | 6 |
| `9EFAFA` | `9EFB00` | 6 |
| `9F0784` | `9F0788` | 4 |
| `9F1606` | `9F1608` | 2 |
| `9F1A6E` | `9F1A70` | 2 |
| `9F20AA` | `9F20B0` | 6 |
| `9F263E` | `9F2640` | 2 |
| `9F2C5E` | `9F2C60` | 2 |
| `9F34DA` | `9F34E0` | 6 |
| `9F5234` | `9F5238` | 4 |
| `9F69F4` | `9F69F8` | 4 |
| `9F840E` | `9F8410` | 2 |
| `9F8A76` | `9F8A78` | 2 |
| `9F8FBE` | `9F8FC0` | 2 |
| `9F97F2` | `9F97F8` | 6 |
| `9F9F0A` | `9F9F10` | 6 |
| `9FAA74` | `9FAA78` | 4 |
| `9FB96A` | `9FB970` | 6 |
| `9FE9F4` | `9FE9F8` | 4 |
| `9FF1F4` | `9FF1F8` | 4 |
| `A007C4` | `A007C8` | 4 |
| `A01456` | `A01458` | 2 |
| `A01AEC` | `A01AF0` | 4 |
| `A026A6` | `A026A8` | 2 |
| `A034E6` | `A034E8` | 2 |
| `A037C2` | `A037C8` | 6 |
| `A03B16` | `A03B18` | 2 |
| `A047F6` | `A047F8` | 2 |
| `A05272` | `A05278` | 6 |
| `A063AA` | `A063B0` | 6 |
| `A06E22` | `A06E28` | 6 |
| `A08782` | `A08788` | 6 |
| `A09442` | `A09448` | 6 |
| `A0A34C` | `A0A350` | 4 |
| `A0BCFC` | `A0BD00` | 4 |
| `A0C9D6` | `A0C9D8` | 2 |
| `A0D19E` | `A0D1A0` | 2 |
| `A0D7F4` | `A0D7F8` | 4 |
| `A0E164` | `A0E168` | 4 |
| `A0E9B4` | `A0E9B8` | 4 |
| `A0F702` | `A0F708` | 6 |
| `A11D54` | `A11D58` | 4 |
| `A12916` | `A12918` | 2 |
| `A13836` | `A13838` | 2 |
| `A14142` | `A14148` | 6 |
| `A1487E` | `A14880` | 2 |
| `A1592A` | `A15930` | 6 |
| `A16FCC` | `A16FD0` | 4 |
| `A18C9C` | `A18CA0` | 4 |
| `A19C3C` | `A19C40` | 4 |
| `A1AB7A` | `A1AB80` | 6 |
| `A1B3C4` | `A1B3C8` | 4 |
| `A1BB2A` | `A1BB30` | 6 |
| `A1C266` | `A1C268` | 2 |
| `A1D00C` | `A1D010` | 4 |
| `A1D5A2` | `A1D5A8` | 6 |
| `A1E33C` | `A1E340` | 4 |
| `A1E716` | `A1E718` | 2 |
| `A1EC16` | `A1EC18` | 2 |
| `A1F1EE` | `A1F1F0` | 2 |
| `A1F60E` | `A1F610` | 2 |
| `A1FB06` | `A1FB08` | 2 |
| `A22984` | `A22988` | 4 |
| `A2317A` | `A23180` | 6 |
| `A247A6` | `A247A8` | 2 |
| `A2666C` | `A26670` | 4 |
| `A26F44` | `A26F48` | 4 |
| `A28016` | `A28018` | 2 |
| `A28D1A` | `A28D20` | 6 |
| `A29A6A` | `A29A70` | 6 |
| `A2A382` | `A2A388` | 6 |
| `A2B48C` | `A2B490` | 4 |
| `A2BAE4` | `A2BAE8` | 4 |
| `A2F52C` | `A2F530` | 4 |
| `A2FD3E` | `A2FD40` | 2 |
| `A30A0C` | `A30A10` | 4 |
| `A315EA` | `A315F0` | 6 |
| `A3210C` | `A32110` | 4 |
| `A34FDC` | `A34FE0` | 4 |
| `A3575E` | `A35760` | 2 |
| `A361EC` | `A361F0` | 4 |
| `A368C2` | `A368C8` | 6 |
| `A3757A` | `A37580` | 6 |
| `A3813E` | `A38140` | 2 |
| `A39232` | `A39238` | 6 |
| `A39512` | `A39518` | 6 |
| `A39936` | `A39938` | 2 |
| `A3AC62` | `A3AC68` | 6 |
| `A3B1DC` | `A3B1E0` | 4 |
| `A3B954` | `A3B958` | 4 |
| `A3F4CC` | `A3F4D0` | 4 |
| `A4253A` | `A42540` | 6 |
| `A437E2` | `A437E8` | 6 |
| `A4453C` | `A44540` | 4 |
| `A45AD6` | `A45AD8` | 2 |
| `A4681A` | `A46820` | 6 |
| `A4764C` | `A47650` | 4 |
| `A48136` | `A48138` | 2 |
| `A4ABFA` | `A4AC00` | 6 |
| `A4E4E2` | `A4E4E8` | 6 |
| `A4F484` | `A4F488` | 4 |
| `A4FECC` | `A4FED0` | 4 |
| `A511D6` | `A511D8` | 2 |
| `A52954` | `A52958` | 4 |
| `A53744` | `A53748` | 4 |
| `A547B4` | `A547B8` | 4 |
| `A56C5A` | `A56C60` | 6 |
| `A588DA` | `A588E0` | 6 |
| `A5BACE` | `A5BAD0` | 2 |
| `A5EEF4` | `A5EEF8` | 4 |
| `A5FBBC` | `A5FBC0` | 4 |
| `A6065E` | `A60660` | 2 |
| `A60B9E` | `A60BA0` | 2 |
| `A60F9A` | `A60FA0` | 6 |
| `A61FCC` | `A61FD0` | 4 |
| `A6230C` | `A62310` | 4 |
| `A62A2A` | `A62A30` | 6 |
| `A6307C` | `A63080` | 4 |
| `A6375C` | `A63760` | 4 |
| `A637CC` | `A637D0` | 4 |
| `A6449C` | `A644A0` | 4 |
| `A66F72` | `A66F78` | 6 |
| `A67252` | `A67258` | 6 |
| `A67866` | `A67868` | 2 |
| `A68A18` | `A68A20` | 8 |
