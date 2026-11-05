# T-164

Official counts are full-TU positional words from `tools/permuter/screen.py` unless noted.

| Function | Before | After | Bytes | Lever |
|---|---:|---:|---|---|
| func_801B01EC | 191 | 120 | 820 / 820 | The sample record is a 4-byte struct, so the index scales by 4, and the elapsed tick is written back through `arg3`. Colour still lives in a saved register (`s1`) instead of the stack slot at 0x64; declaration order only reached 120. |
