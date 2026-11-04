# T-159 second-round notes

## func_80014D5C — matched, 1,780 bytes

Declare the two colour tables as arrays of three-byte RGB records and access
`D_8004AC98[i]` and `D_8004ACB0[i]` directly in the three-iteration loop.
IDO derives the original pointer cursors and loop end; it also places the
initial address loads and the zero stores after the division checks correctly.
The full-TU positional count is zero and the linked main image matches.

## func_801B0520 — improved draft

`func_801B0520.c` is 328 bytes and 10 positional words in the full TU, down
from 22. Read the frame after the colour command into the same `frame` variable,
use masked RGBA components, and put the two default-colour command writes on
one source line. Remaining: the initial scaled frame uses `v1` instead of `v0`,
and the later frame store is scheduled before the float setup instead of after.

## Other probes

- `func_801ADA04`: a two-field typed status structure and direct field reads,
  simple comparisons, and the sibling-style do/while/break form did not close
  the register differences. A 600-second run with the honest-weight configuration found only a candidate containing an empty conditional; it was rejected.
- `func_801B1DE4`: tried postincrement and old-frame snapshots, parameter reuse,
  a typed view of the adjacent animation globals, and display-list pointer
  sharing. The postincrement forms generally emit fewer instructions. The
  600-second permuter's lower scoring variants introduced empty logic and were
  rejected; its honest statement swap did not match.
- `func_801BAA78`: typed paired-image views and a combined counter/table record,
  sibling-style coordinates, direct indexed counters, and display-list pointer
  reuse did not close the register-only difference. The 600-second permuter
  found only source-line joins; rechecking the best retained 14 positional words.
- `func_8002FB80`: matched, 544 bytes. Masking the shifted address bytes with
  `0xFF` reproduces the vertex-command branch; in the texture-command branch,
  reading the table before emitting the bytes gives the target instruction
  order, and `(u8)(data[0] & 63)` gives IDO the original temporary registers.
- `func_800121C8`: `func_800121C8.c` is 19 positional words, 304 bytes, down
  from 22; byte-width casts and the boolean form reduce the differences. Typed
  views of adjacent output fields and source-line arrangements did not close it.
