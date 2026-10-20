# T-047 — ovl_7DF8 polish round 3

Worker: sol-A18. Changes are uncommitted for lead review.

## Results

14 functions attempted: **3 MATCHED (400 bytes), 4 improved drafts, 7 unchanged**.
The first group below consists of drafts that T-039 screened but did not further
iterate and T-044 did not attempt, in ascending T-039 screen-count order.
T-039 screened every draft, so there are no drafts absent from its initial
screen. The three explicitly requested retries follow that group.

Counts are differing aligned instruction words with actual ELF relocations
masked, using IDO 5.3 `-O2 -mips2`. Sizes are reported separately. Counts for
retained drafts were rechecked with T-044/compare.py after formatting; a zero
screening count alone is not proof of matching. Integrated matches require the
complete linked image and ROM checks below. The original CC2C8 draft now
screens at 28 words rather than T-039's original 25.

| Function | Draft directory | Result | Attempts / retained change |
|---|---|---|---|
| func_801BF678 | T-023 | IMPROVED 8 | Was 19. Initialize signed counter before the output cursor; divide before decrementing the counter. Tried indexed and cursor loops, declaration/initialization/update order, and signed widths. Retained draft is 164/168 bytes; eight differing aligned words plus a missing word, not a match. |
| func_801BD270 | T-023 | UNCHANGED | 21 words, 396/396 bytes. Tried signed axis widths and signed/unsigned 64-bit intermediate/cast forms; return packing and spill scheduling remain. |
| func_801CA784 | T-021 | MATCHED | Was 22. Plain indexed search with early return, followed by an indexed append. 96 bytes. Declare the queue as its actual u8[8] type; adjust its existing first-element caller accordingly. |
| func_801CC1A4 | T-021 | UNCHANGED | 22 words, 192/192 bytes. Tried checksum widths, CRC return widths, local declaration order, explicit inner-loop increments/masking, and for/while/do forms. Saved-register allocation and prologue scheduling remain. |
| func_801CBBE0 | T-021 | UNCHANGED | 23 words, 236/236 bytes. Query-buffer element types and layouts did not reproduce the original frame/buffer location. No padding changes retained. |
| func_801CC2C8 | T-021 | MATCHED | Was 25 in T-039, 28 on a fresh compile. Move the checksum test after the EEPROM-presence if/else; use a checksum local and test the byte-minus-checksum difference. This preserves the original branch operand order. Tried probe return/local widths, global-address declarations, prototypes, and equality/control-flow forms. 136 bytes. |
| func_801B17BC | T-025 | IMPROVED 20 | Was 26. Signed 16-bit loop counter and cursor initialization before counter initialization. Tried indexed loads, counter/color widths and callee argument types. 256/256 bytes. |
| func_801C0800 | T-023 | UNCHANGED | 29 words, 248/248 bytes. Tried color argument widths, display-list pointer update forms and command-word store order. |
| func_801C780C | T-021 | IMPROVED 26 | Was 30. Indexed global-array tests/stores replace the merged pointer assignment condition. Tried counter widths, pointer setup and callee return types. 160/160 bytes. |
| func_801B5534 | T-029 | IMPROVED 19 | Was 32. Signed 32-bit player parameter removes unnecessary byte narrowing. Tried indexed stores, index lifetime and random return signedness. 168/168 bytes. |
| func_801BF0E8 | T-023 | MATCHED | Was 32. Declare the score-key global as an array and search with `while (j < used && value != D_802D36D0[j])`. Tried for/while search forms, declaration order and direct score stores. 168 bytes. |
| func_801BF720 | T-023 | UNCHANGED | 2 words, 104/104 bytes. Retried input/result/return signedness and widths, return conversion/masking, and conditional returns. Original default still uses v1 followed by a return-delay-slot move. Existing TU rodata ownership retained. |
| func_801BF914 | T-023 | UNCHANGED | 2 words, 116/116 bytes. Same type/return-form retries; original default-result register and return move remain. Existing TU rodata ownership retained. |
| func_801B695C | T-029 | UNCHANGED | 4 words, 268/268 bytes. Retried parameter/offset widths, memcpy return type, shorter local scopes, stride expressions and separate destination index. Original frame is 0x28 versus C's 0x30; other instructions and spill locations already agree. |

## Source and rodata ownership

No new rodata subsegments were needed: neither new indexed-loop match nor the
EEPROM reader introduces rodata, and the glyph TU already owns its tables.
`kig.ovl_7DF8.us.yaml` and the Makefile are unchanged. No inline assembly,
register variables, compiler flag changes, or artificial padding was retained.

The queue declaration change also makes the following legacy queue-alias
comment accurate. The existing first-element caller still matches. CC2C8's
later declaration is reconciled to `u8 *` to agree with its definition.

Deleted drafts:

- tools/scratch/nonmatching/T-021/func_801CA784.c
- tools/scratch/nonmatching/T-021/func_801CC2C8.c
- tools/scratch/nonmatching/T-023/func_801BF0E8.c

Improved drafts are updated in their original directories. `probe.py` is a
standalone compile/relocation-mask inspection helper, not a replacement for the
full build verification.

Local prerequisites (baserom.us.z64, ROMs, .venv and tools/ext) are symlinks to
`/home/rodri/Projects/killer-instinct-gold-n64`. No ROM was copied into tracked
files. No main, boot, ovl_7E00, status.csv, tracking or worklog edits were made.

## Final validation

`make clean && make extract && make all && make progress` passed on the final
source. The rebuilt ROM is byte-identical to baserom.us.z64, SHA1
`ba52e91b44450c548467044b26951353dc491e04`. Image verification printed:

- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

All three new functions are checked as exact code at their original addresses
by progress inventory after the linked image comparison. Total T4 increases
237 → 240; ovl_7DF8 T4 increases 84 → 87, with 400 additional matched bytes.
`git diff --check` passed. Generated docs/functions.csv and docs/progress.html
were restored after capturing the final table; status.csv is untouched.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 49,452 (15.50%) | 49,452 (15.50%) | 0 | 322 | 0 | 240 | 437 (138,092) |
| boot | 8,468 | 8,108 (95.75%) | 8,108 (95.75%) | 0 | 1 | 0 | 20 | 99 (16,028) |
| main | 173,204 | 28,208 (16.29%) | 28,208 (16.29%) | 0 | 157 | 0 | 133 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 13,136 (9.56%) | 13,136 (9.56%) | 0 | 164 | 0 | 87 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
