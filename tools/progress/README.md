# Regenerable function progress

Run from the repository root (Python standard library only):

```sh
# Only needed when asm/ is absent:
make extract
python3 tools/progress/inventory.py
python3 tools/progress/progress.py --markdown
python3 tools/progress/treemap.py
```

`docs/functions.csv` and `docs/progress.html` are generated. Never edit their
numbers. `progress.py --json` emits totals, byte and function counts for every
tier, M1/M2, and per-area statistics. `--input PATH` selects another inventory;
`treemap.py` also accepts `--output PATH`. No network or CDN is needed.

The lead maintains `status.csv` (`name_or_vram,tier,note`). Use a symbol or a
hex VRAM address (addresses survive renames), or a qualified key such as
`boot:0x80000400`. Unqualified addresses and symbols must identify exactly one
function; use `segment:0xVRAM` when overlays make a key ambiguous. Allowed manual tiers are T1, T2,
T3 and excluded. T3 requires behavior validation; explain that evidence in the
note. Exclusions must remain explicit, with a reason. Unknown and duplicate
keys fail generation. The seed contains only splat's boot handwritten-function
flags and the eleven SDK symbols specified by T-007; no additional SDK guesses.

## Original inventory and scope

`inventory.py` scans text sections in `asm/**/*.s`, uses each function's
`nonmatching` size, or its instruction-comment address span through `endlabel`
when no macro is present. It records ROM, VRAM, original bytes, image (`boot`, `main`, `ovl_7DF8`, or `ovl_7E00`)
as area, and splat's handwritten flag. It keys functions by `(area, VRAM)` and sorts by area and VRAM and writes stable hex
addresses. Data labels are not functions.

`original-functions.json` is a generated baseline, seeded from extraction and
retained across runs: deleting a function's assembly must not delete it from
the denominator. Keep this file in version control. The legacy boot-only keys are migrated automatically. New segment/address pairs are added;
changed original sizes/ROM/area fail for explicit review. Refresh names through
extraction, preferably keeping manual statuses keyed by address. To intentionally
replace the baseline for a new target, archive it first and regenerate from a
complete extraction. Do not reset it after migrating functions to C.

This inventories boot and the three decompressed CPU images. RSP code and
non-CPU payloads are excluded from the assembly function inventory. Functions
with unknown instructions are retained; text `dlabel func_*` fallback routines
are counted through their `enddlabel`, even when splat emits raw words.
Future extracted assembly areas are added automatically. The current function sum is 24,496
bytes versus boot text's 24,928 bytes (`0x7160 - 0x1000`). The difference is 432
bytes of padding (zero/nop instruction comments outside function endlabels),
not functions. Such padding does not enter either function denominator.

## Automatic T4 detection

T4 is never assigned manually. It requires all of:

1. An original function is absent from the current assembly function inventory.
2. A C source under `src/` contains its function definition, after stripping
   comments. An `INCLUDE_ASM` or `GLOBAL_ASM` invocation mentioning the symbol
   anywhere under `src/` prevents T4, even if the referenced assembly moved.
3. `make` succeeds during this inventory run, and `build/kig.us.z64` equals
   `baserom.us.z64` byte for byte. For decompressed images, `build/<area>.bin` must also
   equal `build/segments/<area>.bin`.
4. The image linker map (`build/kig.us.map` for boot, `build/<area>.map`
   otherwise) attributes the symbol at its original VRAM to an object
   under a `src/` directory. A merely unused C definition is insufficient.

Explicit exclusions take precedence. Otherwise a qualifying match supersedes
a manual T1/T2/T3. Build failures abort rather than silently trusting stale
results. No C means no T4. C and GNU linker-map recognition are deliberately
conservative: unusual macros, split map lines, different object directory
conventions, or renamed C symbols can undercount until the parser is extended.
The build must correctly depend on every C source and use the ROM's matching
configuration. Keep extraction outputs current; a stale assembly definition
will conservatively prevent credit. The current Makefile compiles assembly
only; it must gain actual C build rules before any function can qualify.

M1 = (T3 + T4 bytes) / eligible bytes; M2 = T4 bytes / eligible bytes.
Eligible excludes only explicitly excluded functions. Zero eligible bytes is
reported as n/a (JSON null), never 100%. Function counts are separate from byte
metrics. Excluded byte/function counts remain in reports and the treemap.

## Makefile snippet for the lead

Add this once the lead approves (the task does not modify the Makefile):

```make
.PHONY: progress
progress:
	@test -d asm || $(MAKE) extract
	$(PYTHON) tools/progress/inventory.py
	$(PYTHON) tools/progress/progress.py --markdown
	$(PYTHON) tools/progress/treemap.py
```

Use the same commands in CI after extraction/build and check the generated
CSV, baseline, and HTML diff. Paste the generated Markdown into TRACKING.md;
never update percentages by hand.
