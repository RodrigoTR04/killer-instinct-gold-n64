# T-115 — sol-A39: C7998 and complete 1BD90 rodata ownership

Promoted `func_801C7998` using T-113's honest C, with one packed `u64`
input. No commits. Reserved functions, main/boot/7E00 source, Makefile,
status.csv, TRACKING and WORKLOG are unchanged.

## Original range and ownership evidence

The complete original 1BD90 pool is **image offsets 0xE93F0–0xE9A10,
VRAM 0x80294F10–0x80295530**, end exclusive, size **0x620**. Both TU
boundaries are 16-byte aligned. `pool-evidence.md` inventories every migrated
symbol against original-image bytes; it is supporting evidence, not build input.

| Original VRAM | Contents and owner/reference evidence |
|---|---|
| 80294F10–802952C4 | Indirect menu strings. Original pointer tables at 802923F8–802926F4 contain their original addresses; C7A98 edits menu text, C80F0 loads button-name pointers from 802925CC, C9B14 loads options pointers from 802926E0. |
| 802952C4 / 52D0 / 52D8 | LUDICROUS / SLOW / SLOW, directly loaded by C7A98 at 801C7C8C onward. Duplicate strings are separate original objects. |
| 802952E0 / 52FC | BACK TO CHARACTER SELECT / MAIN OPTIONS, existing matched C7CD0 extern users. |
| 8029530C / 5310 | P1 / P2, C80F0. |
| 80295314 / 5318 | YES / NO, C90D4. |
| 8029531C | WON 00, LOST 00, existing matched C9584 memcpy source. |
| 8029532C–8029538C | Name-entry/help strings, C9698 and C9B14. |
| 802953A0–80295428 | Free-pages message and other C9B14 strings, then CAAA00's final string at 5428. |
| 80295430–802954B4 | C7998's 33-entry jump table; original loads at 801C7A20/801C7A28. Four bytes align the following double. |
| 802954B8–802954C8 | C80F0: double at 54B8, floats at 54C0/54C4. |
| 802954C8–802954E0 | C90D4: float at 54C8, alignment word, doubles at 54D0/54D8. |
| 802954E0–802954E8 | C9698: floats -550 and 0.8. |
| 802954E8–80295530 | C9B14: floats, alignment, doubles at 54F0/5518, last floats at 5520/5524 and eight bytes TU tail alignment. |

The preceding credits TU ends at 80294F10. Crucially, T-091's provisional
end 0xE9A40 includes **two strings belonging to the following save TU**:
80295530/80295548 (CONTROLLER PAK 1 FULL / CONTROLLER PAK 2 FULL).
Original pointer words at 802927A4/802927A8 point to these strings;
`func_801CC908` (TU 200C0) loads D_802927A4 at 801CCA08/801CCA10 and
801CCA7C/801CCA84. They remain in their own data fragment at E9A10–E9A40.
Thus the C-owned range ends at the actual 16-byte boundary before them.

## Configuration and C changes

Replaced the E93F0 remaining-data subsegment with:

```yaml
      - [0xE93F0, .rodata, ovl_7DF8_1BD90]
      - {start: 0xE9A10, type: data, name: t115_after_ovl_7DF8_1BD90, linker_section_order: .rodata}
```

Existing E9A40 save-TU ownership is unchanged. Added 90
`force_migration:True function_owner:func_801C7A98` symbol hints for the
complete regular string pool 80294F10–80295430. This keeps indirect strings,
duplicate strings, and matched C's extern sources assembly-defined, in their
original order, inside the C object's regular rodata. Floating constants migrate
naturally to their existing GLOBAL_ASM owners as late rodata. C7998 emits its
own original jump table. Existing matched function bodies require no edits.
When promoting C7A98 later, retain or reassign its reserved string pool.

No inline assembly, register bindings, artificial padding objects, compiler
changes or binary rewriting. C7998 retains all button cases, including 8000
and 4000, and the low-16-bit mask. The caller passes its packed word in a0/a1.

## Other draft re-tests

`retest.jsonl` records production-context measurements with IDO 5.3 -O2
-mips2 through asm-processor; only actual ELF relocation fields are masked.
No additional exact draft emerged. C85C0 is reserved to T-114 and excluded.

| Draft | Differing words | Compiled / original bytes |
|---|---:|---:|
| C7A98 | 14 | 568 / 568 |
| C7F90 | 16 | 116 / 116 |
| C8004 | 47 | 228 / 236 |
| C80F0 | 284 | 1228 / 1232 |
| C8AE0 | 21 | 324 / 324 |
| C8C24 | 22 | 396 / 408 |
| C90D4 | 219 | 1192 / 1200 |
| C9698 | 135 | 1148 / 1148 |
| C9B14 | 629 | 3140 / 3184 |
| CAA00, temporary corrected packed-input call | 993 | 3924 / 3992 |

The first nine rows are full-TU. CAA00's checked-in draft declares the old
`s32 func_801C7998(s32,s32)` guess; its raw screen records the resulting
full-TU diagnostic and a declaration fallback, not an integration result.
A temporary copy changes only that prototype to `u8 (u64)` and passes
`((u64)(u32)hi << 32) | (u32)buttons`; `caller-retest.json` records its full-TU
result above. The checked-in caller draft is unchanged. Other drafts retain
instruction/size differences independently of rodata ownership.

## Final validation

`make clean && make extract && make all` passed (exit 0), followed serially
by `make progress` (exit 0). All required clean/extract/build/progress stages
completed. The linked map places 1BD90.c.o(.rodata) at **80294F10, size 620**;
the following data fragment starts at **80295530, size 30**, and the existing
200C0 pool still begins at **80295560**. Direct comparison confirms both the
256-byte C7998 body and the complete original pool are identical.

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

Deleted the promoted T-030/func_801C7998.c draft. No other draft or function
body changes. `git diff --check` passes. Regenerated progress documents are
restored after recording the table; status.csv is untouched. Local setup
symlinks point to the authorized checkout. ROMs were never copied or staged.
No commits. Matched game code increases **256 bytes**, T4 **314 → 315**.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 70,884 (24.45%) | 70,884 (24.45%) | 0 | 194 | 0 | 315 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 31,204 (21.67%) | 31,204 (21.67%) | 0 | 90 | 0 | 147 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 31,212 (22.71%) | 31,212 (22.71%) | 0 | 104 | 0 | 147 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
