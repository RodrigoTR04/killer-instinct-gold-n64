# Function searches with decomp-permuter

Run from the repository root after `make extract`. Install locally (never add
this checkout or generated search directories to git):

```sh
git clone https://github.com/simonlindholm/decomp-permuter tools/ext/decomp-permuter
.venv/bin/python -m pip install pynacl toml Levenshtein
.venv/bin/python tools/permuter/import_fn.py func_801BF720 /tmp/kig-glyph
.venv/bin/python tools/ext/decomp-permuter/permuter.py /tmp/kig-glyph \
    --stack-diffs --stop-on-zero --best-only --better-only -j 2
```

If `tools/ext` is the shared symlink, clone into its shared destination instead.
T-082 used revision `8556c81d80d1c1af98a858c8f4dc951357f29139`, toml 0.10.2,
PyNaCl 1.6.2, cffi 2.1.1 and existing Levenshtein 0.27.5. No network worker
or permuter@home service is needed. Stop a search with Ctrl-C; for a bounded
run use `timeout --signal=INT --kill-after=15s 900s` before the command.

The helper finds the function's unique GLOBAL_ASM and draft (override draft
selection with `--draft path.c`). It preprocesses the preceding TU context
and draft using `gcc -E -P`, then uses upstream `strip_other_fns` to replace
other definitions with declarations. `base.c`, original splat `target.s` and
assembled `target.o`, executable `compile.sh`, `settings.toml`, `origin.json`
and a smoke-compiled `base.o` go into a **new** output directory. This uses
manual import rather than upstream `import.py`: scratch drafts have no Make
object rule and the TU body must be replaced first. The original function's
late rodata/jump tables are retained; asm-processor's metadata-only
`.late_rodata_alignment` annotation is removed for GNU as. The F45C draft uses
a compatible typed view of its TU's existing list global.

`compile.sh` uses the exact game rule: IDO 5.3 through asm-processor, with
`-c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O2 -mips2 -32 -Iinclude`,
and GNU as `-EB -mips3 -32 -G 0 -I include`. Absolute paths bind the search to
this worktree. This helper is for ordinary game functions; it does not infer
SDK/per-object flag overrides. Do not use it for those without adapting flags.

Permuter scores are weighted assembly differences, **not differing word
counts**. Always pass `--stack-diffs`: by default stack offsets are ignored.
Zero still needs independent relocation-aware byte comparison, honest C
review and integration into the complete owning TU. Randomization can alter
types or remove expressions; an improved score alone proves no equivalence.
The parser also reformats the initial C before scoring: IDO line boundaries
can make even the initial normalized candidate better or worse than the draft.
Use `--debug` from the disposable directory to save that normalized candidate
as `debug_source.c`. Preserve useful line joins when simplifying a result.

Promote only readable, honest C: no inline asm, `#line` or `register`.
Validate all images and the ROM with
`make clean && make extract && make all && make progress`. Do not commit ROMs,
objects or generated permuter output. T-082 changes are left uncommitted for
lead review.

Screen all current T2 drafts (including equal-size and size-mismatched bodies):

```sh
.venv/bin/python tools/permuter/screen.py -j 6 --json /tmp/kig-screen.json
```

The default report is `tools/scratch/nonmatching/T-092/screen.md`. Full TU
compilation is preferred. Legacy declaration conflicts fall back to the TU
prefix, then to preprocessed TU declarations with the draft's explicit views
taking precedence; each row identifies its context. A few older drafts need
audited shared sprite/global declarations, supplied only in that last mode.
Errors are reported rather than treated as large scores. No draft or build
input is modified. `pycparser` (already required by decomp-permuter) is needed
for declaration fallback. The screener uses the existing ELF reader in
`tools/scratch/flagprobe/compare.py`; only actual relocation fields are masked.

## Declaration order and source lines

`declorder.py` searches the IDO dimensions that AST normalization often loses:

```sh
.venv/bin/python tools/permuter/declorder.py func_801BD270 \
    tools/scratch/nonmatching/T-023/func_801BD270.c /tmp/kig-declorder \
    --seconds 600 -j 2 --seed 118
```

Run `make extract` first. The tool reuses `screen.measure`, including the exact
IDO/asm-processor command and relocation masks. It selects a compiling context
once (full TU, prefix, then declaration fallback), and keeps that context fixed.
Use `--context full` to forbid fallback. A fallback zero must be reconciled in
the complete TU before promotion; even a full-TU zero requires the linked build.
The objective is differing words including missing/extra words, then absolute
byte-size difference. Compile failures are diagnostics, never scores.

Leading uninitialized simple local declarations are split into declarators,
permuted exhaustively for up to six locals, or sampled in 400 orders for larger
sets. Each order tries separate declarations and adjacent declarations combined
by type. Pointer stars and array extents stay with their declarators. Initialized,
qualified, static, compound and function-pointer declarations stay fixed.
Independent initializers allow unrelated uninitialized locals to cross them;
initializers mentioning local names form barriers to preserve scope and data
dependencies. The conservative scanner stops at unsupported declaration syntax
(such as multiword types or symbolic array extents). Declarations never move
across an executable statement or scope.
Combining declarations necessarily replaces repeated type/semicolon syntax with
commas; types, names, extents and executable tokens stay unchanged.

The initial sweep also tries statement/brace boundaries all split or all joined.
Hill climbing is interleaved with that sweep and combines declaration swaps
with individual/random boundary joins/splits. A bounded reservoir of equal-score
parents lets the search walk across plateaus while retaining the best source.
Parentheses protect `for` separators; comments and quoted literals remain intact. No statement reordering, AST printing, `#line`, `register`,
new expression or compiler setting is introduced. A fixed seed makes generation
reproducible; wall-clock cutoff and parallel completion can change how far it gets.
The time budget stops new submissions; the current compile batch finishes first.
Searches may finish early after 100 consecutive duplicate proposals; that does
not prove exhaustive layout coverage. A budget can interrupt declaration
enumeration too; `initial_exhausted` records whether the initial sweep finished.
`-j` controls independent compiler workers, not compiler flags.

The input draft and owning source are never overwritten. `best.c` preserves the
best source, and compact `result.json` records baseline/best words and sizes,
context, elapsed time, counts, winning label, improvement history and a bounded
sample of errors. Use a disposable output directory outside git. Review improved
C before copying it to a draft; integrate zeros readably, explain necessary layout,
delete matched drafts, then run the full clean build and progress checks.
