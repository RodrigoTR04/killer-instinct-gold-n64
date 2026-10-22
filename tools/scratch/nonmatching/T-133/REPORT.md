# T-133 — sol-C48

No functions promoted: **0 B (0.00%)** newly matched; the 2,030 B target is unmet. A bounded pass over all seven fresh near misses and a fresh reconstruction of one large function produced three improved drafts.

## Results

Scores below are relocation-masked differing words, including missing/extra words, not permuter weighted scores.

| Function | Before → final words | Final/original bytes | Context | Result |
|---|---:|---:|---|---|
| func_801BE540 | 8 → 8 | 288/288 | full | Unchanged |
| func_8002FB80 | 20 → 20 | 544/544 | full | Unchanged |
| func_801C8004 | 27 → 24 | 232/236 | full | Improved draft in T-021 |
| func_801B0520 | 22 → 22 | 328/328 | full | Unchanged |
| func_801B446C | 28 → 28 | 292/292 | full | Unchanged |
| func_801C3758 | 30 → 30 | 564/564 | full | Kept T-125 body |
| func_8001373C | 34 → 28 | 256/256 | prefix | Improved draft in T-020 |
| func_80020E98 | 512 → 497 | 2076/2108 | prefix | Fresh draft in T-032 |

## Searches and diagnosis

All permuter searches used tools/ext/decomp-permuter with `--stack-diffs --stop-on-zero --best-only --better-only`, disposable directories under /tmp/sol-C48-*, and bounded wall times. No shared toolchain files were modified. The seven near misses also received declorder.py searches (seed 133, 90–120 seconds each).

- **801BE540:** 240-second permuter search and 120-second declorder search (442 compilations) retained 8 words. Additional focused probes covered byte/integer character types, pointer signedness, cached loop tests, glyph-pointer scope/direct indexing, 240 declaration/initializer-order combinations, argument-pointer roles, and meaningful do/while branch structure. No valid improvement. Cursor a3/a0 and character a0/v1 allocation remain.
- **8002FB80:** 240-second permuter search, 120-second declorder search (704 compilations), and 70 targeted tail/index/load/pointer-advance variants retained 20 words. A weighted-score 775 permuter candidate is 21 actual words and was not kept. Explicit texture index/pointer and input-byte temporaries do not recover the 0x40 scheduling; pointer-increment forms did not recover the 0xC0 store/shift order.
- **801C8004:** 180-second permuter search and 90-second declorder search. Declaration order/line joins improved 27 to 24 words, retained verbatim with a new explanatory draft comment. A 12-word candidate contained a dummy goto and was rejected. Additional structured-loop, full-width/byte mask, old-mask, and fresh m2c/bit-temporary probes did not beat 24. Still one instruction short; first scan allocation and old-mask moves remain.
- **801B0520:** 180-second permuter and 90-second declorder searches. The weighted-score 140 candidate introduces a shared floating zero but measures 23 words in the full TU, worse than the original 22. Kept the original draft.
- **801B446C:** 180-second permuter and 90-second declorder searches. Lower weighted scores redirect flag accesses into the queue cursor (one also reads an uninitialized cursor, another adds an empty if); rejected. Kept the original 28-word draft.
- **801C3758:** 180-second permuter and 120-second declorder searches. A weighted-score 255 candidate merges frame/next and measures 134 actual words, 560 bytes. Kept the T-125 body, including its separate next-frame value. Address retention and dual wrapped-frame zero remain.
- **8001373C:** 180-second permuter (3,231 iterations) and 90-second declorder searches. A valid permuter candidate computes the Y impulse in a signed-halfword temporary before the component stores, improving 34 to 28 words. Cleaned `new_var`/`short` to `impulseY`/`s16` and independently re-screened at 28. The impulse is bounded: byte strength times 30,000 divided by distance squared clamped to at least 50,000 is at most 153, so the temporary introduces no narrowing loss. Candidates that mask a velocity to eight bits were rejected. Existing literal/rodata-owner treatment is unchanged.

## Large-band triage and fresh reconstruction

Inspected original asm for all seven large-band functions. 80025FC4 has extensive texture-rectangle packing; 800306B8 has glyph flipping, clipping and divisions; 801C5E74 combines palette/DMA/rendering and strings; 801C08F8 combines u64 division and many text/render calls; 8001178C has many state/action calls; 8001E33C combines player state and rendering. Selected **80020E98**, whose DMA/frame/cache traversal has the clearest structure.

Ran fresh m2c both without context and with the imported typed context, then resolved the byte-stream accesses and cache views. The ROM-entry stride is 32 bytes (the old draft type had 28), and loop counters explicitly wrap to 16 bits. Preserved byte order, count reloads after decoding, the original table-pointer lifetimes, separate input/output stream cursors, and the decoder's return value through the existing compatible cast. The fresh draft improved the independently remeasured original 512 words / 2104 B to 501 words / 2076 B, then to 497 words through declaration order/line layout (888 compilations, 120 seconds). Eight structure/type/pointer variants did not improve it. It also received a bounded 180-second permuter run and a declaration/layout pass. Lower permuter word counts (494/495) were rejected: one moves the loop increment before its counter is initialized, and another replaces constant byte shifts with a live counter.

The draft still falls back to prefix compilation because a later matched function declares a different view of D_8004D278. No production declaration was changed to force integration. It needs further structure/allocation work before reconciling those views.

## Scope and validation

Only T-020/func_8001373C.c, T-021/func_801C8004.c, T-032/func_80020E98.c and this report are retained. No src, hints, YAML, symbol, ROM, or toolchain changes. No artificial matching constructs were promoted. All three improved drafts were re-screened with screen.py after cleanup.



Clean verification command: `toolbox run -c kig-build bash -c 'make clean && make extract && make -j8 && make progress'` completed successfully. All three images passed. Relevant final output:

```text
OK: rebuilt ROM is byte-identical to baserom.us.z64
| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
| Total | 289,876 | 82,572 (28.49%) | 82,572 (28.49%) | 0 | 175 | 0 | 334 | 490 (167,316) |
```

Generated progress files have no net changes. No README changes remain.

Follow-ups: pursue 8001373C's remaining FP/general register scheduling from the new 28-word body; 801C8004 still needs a real extra instruction/old-mask flow; 80020E98 needs substantial allocation/structure work and eventual reconciliation with the later D_8004D278 view. No near-miss is ready for production promotion.
