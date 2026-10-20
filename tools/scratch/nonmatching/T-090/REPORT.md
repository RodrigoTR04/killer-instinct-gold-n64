# T-090 — sol-A30: 190B0 rodata ownership / func_801C67CC

Promoted func_801C67CC (692 bytes) from T-030's T-087-improved draft.
No commits. Only this function, its TU's rodata definitions, the overlay YAML,
and the matched draft deletion are changed.

## Complete range evidence

Original decompressed ovl_7DF8 base: 0x801ABB20. The complete TU rodata is
**image offsets 0xE7D10–0xE8DA0, VRAM 0x80293830–0x802948C0**, end exclusive,
size 0x1090. Both boundaries are 16-byte aligned.

| Original VRAM | Contents | Owner/reference evidence |
|---|---|---|
| 0x80293830–0x8029484C | 115 ending-text strings, each padded to four bytes | Original data pointer lists beginning at D_80291920; selector tables D_80291B74 and D_80291BA0 are loaded by func_801C4E38 |
| 0x8029484C | COMBO FOR | func_801C5298 at 0x801C5848/0x801C5860 |
| 0x80294858 | PRESIDENT | func_801C5298 at 0x801C5954/0x801C5960 |
| 0x80294864 | PLAYER ONE | func_801C5E74 at 0x801C6328/0x801C6334 |
| 0x80294870 | PLAYER TWO | func_801C5E74 at 0x801C6348/0x801C634C |
| 0x8029487C | WINNING TEAM | func_801C5E74 at 0x801C642C/0x801C6430 |
| 0x8029488C | float 0.6700000167 (3F2B851F) | func_801C5064 at 0x801C5070 |
| 0x80294890 | float -1950 (C4F3C000), then zero word at 0x80294894 | func_801C5064 at 0x801C5120; next double is 8-byte aligned |
| 0x80294898 | double pi (400921FB54442D18) | func_801C5298 at 0x801C5698 |
| 0x802948A0 | double 360 (4076800000000000) | func_801C67CC at 0x801C67E8 |
| 0x802948A8 | second double 360, same bits | func_801C67CC at 0x801C6844 |
| 0x802948B0 | double 372 (4077400000000000) | func_801C67CC at 0x801C69D8 |
| 0x802948B8 | double 0.6 (3FE3333333333333) | func_801C6D40 at 0x801C6DE0 |

The first original pointer-list words at 0x80291920 are 0x80293830,
0x8029385C, 0x80293888, zero, 0x802938B8, 0x802938E4. The first selector
words at 0x80291B74 are 0x80291920, 0x80291968, 0x80291A4C, 0x80291A74,
0x80291A24, 0x80291944. Thus ownership includes the preceding indirectly
referenced strings, not merely the late constant pool. The final preceding
string at 0x80294838 is THANKS FOR PLAYING. All 115 strings were read from
the original image and restored as exact const u8 array literals; splat does
not migrate these indirectly referenced strings into a GLOBAL_ASM body.

The prior TU (18CC0) has no rodata references. The preceding 18520 pool ends
at 0x80293830. The next pool begins at 0x802948C0 with tGAME DEVELOPMENT;
its data pointer table D_802921E0 is used by func_801C7310 in TU 1B790.
Scanning all 190B0 asm references and original bytes finds no jump tables in
this range. Other 8029xxxx references are mutable data, vectors and pointer
tables outside this rodata interval, and remain unchanged.

## YAML and C

Replaced the start of remaining_2 with:

```yaml
      - [0xE7D10, .rodata, ovl_7DF8_190B0]
      - {start: 0xE8DA0, type: data, name: ovl_7DF8_remaining_2, linker_section_order: .rodata}
```

The remaining fragment still ends at existing 0xE9A40 save-TU rodata.
Splat migrates the five directly referenced strings, 5064's floats, 5298's pi,
and 6D40's double into their unchanged GLOBAL_ASM files. Existing matched C
functions require no literal changes. The promoted C67CC emits the three
original double literals in order. No assembly, padding arrays, register
bindings, compiler changes or output rewriting are used. Deleted draft:
`tools/scratch/nonmatching/T-030/func_801C67CC.c`.

Prerequisites baserom.us.z64, ROMs, .venv and tools/ext are symlinks to the
user-authorized main checkout. No ROM was copied or committed. T-088's
func_801C4E38, func_801C5064 and func_801C6A80 bodies remain unchanged.

## Final validation

`make clean && make extract && make all && make progress` passed (exit 0)
on the finalized source, serially. The linker map places 190B0.c.o(.rodata)
at 0x80293830, size 0x1090. ROM and all executable images are byte-identical:

- ROM: ba52e91b44450c548467044b26951353dc491e04
- main: 81736d32e8cda8f399b319a49250dff972b81af8
- ovl_7DF8: ea830aae50ff1422da60d4b7fdbfc29f03b1be39
- ovl_7E00: 2b01138a290212b9d886981e1196f7b6fb45ecdb

An earlier validation attempt overlapped an inventory-triggered rebuild and
failed with an empty linker input list; its process tree was stopped. The
final serial clean run above passed in full.

`git diff --check` passed. Generated docs/functions.csv and docs/progress.html
were restored after recording the table; status.csv, TRACKING and WORKLOG
are unchanged. No main/boot/ovl_7E00, Makefile, symbol or linker-file changes.
Matched game bytes increase 55,924 → 56,616 (+692), T4 270 → 271.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 56,616 (19.53%) | 56,616 (19.53%) | 0 | 238 | 0 | 271 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 27,560 (19.14%) | 27,560 (19.14%) | 0 | 102 | 0 | 135 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 20,588 (14.98%) | 20,588 (14.98%) | 0 | 136 | 0 | 115 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
