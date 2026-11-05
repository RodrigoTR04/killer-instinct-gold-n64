# T-169

Official counts are full-TU positional words from `tools/permuter/screen.py` (`screen.measure`).

| Function | Before | After | Bytes | Lever |
|---|---:|---:|---|---|
| func_801AFFAC | 80 | 59 | 576 / 576 | The float conversion result is kept live across the first `cvt.w.d` guard: `red`/`mid` name the two `(u32)` scale results up front, but the `w1` OR chain still reads the blue channel as `((u32)(temp_f0 * D_802928B0) & 0xFF) << 16` so IDO emits the `andi` on the first product before `cfc1`. Writing the OR chain green-first (`(var_a3 & 0xFF) << 8 | ... | red << 24`) is what fixes the shift order. |
