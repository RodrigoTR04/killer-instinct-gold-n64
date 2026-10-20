# T-049 — sol-C19: boot polish, FU-2 and FU-8

No commits made. Changes are left in the worktree for lead review. No status.csv,
main/overlay source, image YAML, symbol file, tracking or worklog edits. Local
prerequisites are symlinks to `/home/rodri/Projects/killer-instinct-gold-n64`;
ROM contents are not added to git.

## 1. func_80001564

Still unmatched: the original T-038 draft and built GLOBAL_ASM are unchanged.
The best result remains 360/360 bytes, with eight differing words at +0x18,
+0x1C, +0x20, +0x28, +0xF0, +0xF4, +0xF8 and +0x100. These are the two
unrolled loops' store ordering/offsets described by T-042.

`sweep.py` and `sweep-results.json` retain 34 additional production-flag probes:
one-word struct/array destination elements; four-word records with forward,
rotated and reverse field stores; equivalent index expressions; `<`, `<=`, `!=`
bounds with for/do loops and one/two/four stores per iteration; and a union of
u64 pairs/u32 words with pair filling. One-word aggregate types and equivalent
index expressions retain the eight-word result. Other shapes change instruction
count or allocation and do not match (316–508 bytes). No register bindings,
inline assembly, instruction encoding, or artificial padding was used.

Reproduce: `.venv/bin/python tools/scratch/nonmatching/T-049/sweep.py`.
Diagnostics mask only actual ELF relocation fields, as in T-042; the final
linked build, rather than these probes, establishes matching status.

## 2. FU-2 boot rodata ownership

`kig.us.yaml` assigns ROM 0x7D40–0x7D70 to
`[0x7D40, .rodata, boot_49A0]`. This is the complete aligned exception jump
table, including its trailing zero words. Splat migrates `jtbl_80007140` into
`__osException.s` as late rodata, with local label references, and asm-processor
owns it in the existing boot C TU's object. No symbol hint is necessary.

The rest stays assembly: 0x7160–0x7D40 in boot.data.s and 0x7D70–0x7ED0 in
boot_remaining.data.s, the latter ordered as rodata after the owning C object.
In particular, D_80007170 is shared by __osDispatchThread and osSetIntMask;
it is deliberately not assigned speculative exclusive TU ownership. Trying to
include it in the migrated range leaves it unmigrated and undefined, so the
final range ends at 0x7D70. Earlier inflate tables and mutable SDK globals stay
in data. No additional boot C TU has proven rodata requiring migration here.
The Makefile collects all boot data assembly objects, including BSS, and tracks
the new fragment as an extraction output. ROM and boot layout remain exact.

## 3. FU-8 compressed code slot ownership

The baserom-backed opaque region is now three bins: assets through 0xA94D80,
the 16-byte gap at 0xAB5800, and the tail from 0xB14BA0. The three intervening
code slots are YAML bins with `extract: False`. The Makefile builds their
objects directly from build/{main,ovl_7DF8,ovl_7E00}.1172 and zero-aligns each
stream to 16 bytes. No slot asset file is extracted from the baserom.

The historically named splice_rom.py now validates the linked slots rather
than replacing them. It verifies fixed YAML/boot-table bounds, decompression
against rebuilt images, exact padded lengths, and linked stream/padding bytes.
The previous opportunistic recompression inside the validation script is
removed; Make owns compression prerequisites. docs/segments.md records all six
ranges and ownership. Non-matching relocation is still unsupported.

A top-level splat `pad` experiment was discarded: splat 0.50.1's normal section
ordering omits that entry and fails to reserve its size. Non-extracted bin
segments use the existing linker pipeline and make the built bytes the sole
source of every compressed code slot instead.

## Validation

Passed the required `make clean && make extract && make all && make progress`
(`make all` used `-j4`). ROM SHA1:
`ba52e91b44450c548467044b26951353dc491e04`. Main, ovl_7DF8 and ovl_7E00 all
verify byte-identical. `git diff --check` passes. Additional in-memory negative
checks reject a changed code byte and a changed boot-table bound. Confirmed
assets/opaque.bin and all three assets/code_*.bin files are absent after the
clean build. Generated progress files have no diff; status.csv is untouched.

## Final make progress

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 49,928 (15.65%) | 49,928 (15.65%) | 0 | 320 | 0 | 242 | 437 (138,092) |
| boot | 8,468 | 8,108 (95.75%) | 8,108 (95.75%) | 0 | 1 | 0 | 20 | 99 (16,028) |
| main | 173,204 | 28,684 (16.56%) | 28,684 (16.56%) | 0 | 155 | 0 | 135 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 13,136 (9.56%) | 13,136 (9.56%) | 0 | 164 | 0 | 87 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
