# T-138 investigation

- `func_801BBE88`: 147 → 140 differing words, 808/808 B, full TU. Reordering the words of two independent display-list commands and using a structured argument view improves scheduling. Still nonmatching; do not promote.
- `func_801B5534`: type, index, offset and explicit remainder probes did not improve the existing two-word stack-slot difference.
- `func_801B1210`: argument reuse, alpha types, command order and renderer return type did not improve the 28-word baseline.
- `func_801BADEC`: scale caching, y-offset caching, inlining the first y coordinate and direct global references did not improve the 101-word baseline.
- `func_801BA884`: 86 → 85 differing words, 496/500 B, full TU. Direct x-coordinate expressions replace the shared intermediate; still nonmatching.
- `func_801BBB60`: 40 → 30 differing words, 292/292 B, full TU. A `for` loop for eight palette clears improves unrolled-store scheduling; deriving the adjacent palette from the 0x1000-byte buffer advances pointer initialization; still nonmatching.
- `func_801BAA78`: 208 → 15 differing words, 892 → 884/884 B, full TU. Read scale through the state as in the matched siblings, reuse an argument for the y-coordinate base, cache the first y offset, update the counter directly, and use an explicit command cursor; still nonmatching.
- `func_801B1DE4`: the prior draft captured D_801D3098 before calls, but the original reloads it after `func_801B19F0` and, on the threshold path, `func_801AF5EC`. `func_801B1DE4-reload.c` preserves those reloads; it scores 118 words and 564/556 B, so it remains a diagnostic alongside the improved draft.
- `func_801B1DE4`: corrected counter reloads, cursor timing, and the incremented-frame expression reduce the draft from 111 to 50 words at 556/556 B. The separate reload-only diagnostic is retained for comparison.
- `func_801B43A8`: deriving the group base from the end symbol reduces 34 → 23 differing words at 196/196 B by avoiding the shared address across `memcpy`. The saved diagnostic subtracts from a scalar extern, so its bounds need a sound array-backed representation before promotion; direct array views did not retain the improvement.
- `func_801B43A8`: an integer-address view of the same table improves 34 → 27 words at 196/196 B without subtracting from a scalar pointer. The target increments the group by three, as in this draft.
- `func_801BB464`: MATCHED, 304 B. Reading the scale and y offset directly, computing x before y, and preserving the counter pointer recover the original text. `make clean && make extract && make -j8 && make progress` passed with all images and ROM byte-identical; the inventory reports T4.
- `func_801B1DE4`: 50 → 19 differing words at 556/556 B, full TU. A separate incremented-frame local and explicit counter reload on the threshold path reproduce the original value lifetimes; reversing the second command word writes improves scheduling. Still nonmatching.
- `func_801B1DE4`: declaration and source-line search reduces 19 → 16 differing words at 556/556 B; the saved draft preserves the same behavior. Counter pointer, array/struct views, and reusing the alpha variable did not improve it further.
- `func_801B1DE4`: moving the flag store before the post-call counter reload reduces 16 → 15 differing words at 556/556 B; both remain after the call, preserving observed values.
- Further `func_801BAA78` probes: counter lifetimes, coordinate and counter structures, and branch-local float temporaries did not improve 15 words.
- Further `func_801B6528` probes: preserving the matrix while reusing arg2 for the card, alternative comparison and texture views, and per-command cursor scopes did not improve its three-word register difference.
- Further `func_801B695C` probes: offset assignments inside copy arguments and distinct offset locals did not reduce the four stack-frame differences. `func_801B5534` pointer-view probes did not improve its two spill-slot words.
- `func_801BA884`: 85 → 50 differing words at 500/500 B, full TU. Independent expressions for the two draw calls’ y coordinates and direct state-scale reads allow the compiler to preserve the integer coordinate across the first call. Both values are computed before that call, preserving the original timing. Still nonmatching; review and simplify before promotion.
- `func_801BBB60`: 30 → 29 differing words at 292/292 B, full TU, by separating the flag and buffer initialization statements. Alternate buffer-boundary expressions did not improve beyond this readable form.
- `func_801BA884`: computing the first draw’s y coordinate before the second reduces 50 → 48 differing words at 500/500 B; both still precede the first draw call.
- `func_801BA884`: declaration ordering reduces 48 → 38 differing words at 500/500 B, full TU; the declaration search continues.
- `func_801BA884`: permuter candidate reduces 38 → 6 differing words at 500/500 B, full TU. Reusing a coordinate temporary for the display-list argument and sharing the zero used by the second draw and timer reset changes allocation. It remains a draft; simplify and validate these temporaries before promotion.
- `func_801BA884`: removed the permuter’s coordinate-temp reuse; passing the original display-list argument directly remains at six words and makes the draft clearer.
- `func_801BA884`: a zero-score permuter output inserted `if (0) { }`; rejected under the task’s explicit ban. The six-word draft contains no such construct. A structure grouping the actual 12-frame table with the counter did not improve it.
- `func_801BA884`: MATCHED, 500 B. A real do-once block executes the second draw and conditionally exits before the frame reset; this preserves the ordinary wrap behavior without the forbidden dummy conditional. The full clean build and progress passed with all images and ROM byte-identical; inventory reports T4.
- Additional searches: real conditional-break blocks in `func_801BAA78` and `func_801B6528`, alternate frame/local views in `func_801B0520`, and real position-choice blocks in `func_801B1DE4` did not improve their recorded word counts. A 900-second declaration search on `func_801BAA78` remained at 15 words.
- `func_801B5DCC`: 386 → 354 differing words, 1900/1884 B, full TU. The assembly reloads D_802C8D06 after the helper-bearing paths before its final state check; the older draft incorrectly retained the pre-call byte. The corrected draft remains nonmatching and has 16 excess bytes.
- `func_801B5650`: applied the same three state reloads as its carousel sibling after confirming them in the assembly. This corrects the cached-state behavior and reduces 423 → 371 differing words, at 1940/1916 B; still nonmatching.
- `func_801B5DCC`: a separate record-recompute diagnostic scores 348 words at 1852/1884 B. It recomputes the card record on every path at the merge, unlike the assembly’s path-specific reuse; the alias and scheduling implications need resolution before promotion.
- `func_801B5DCC`: reordering the result and z declarations reduces 354 → 353 differing words at 1900/1884 B, full TU.
- `func_801B5DCC`: reusing the unused fourth argument for the result reduces 353 → 351 differing words at 1900/1884 B, full TU; the source does not use the incoming value.
- `func_801B5650`: applying the sibling’s result lifetime change reduces 371 → 368 differing words at 1940/1916 B, full TU.
- `func_801B5DCC`: reading the initial state once for its two pre-call checks and keeping it in a full-width local reduces 351 → 341 differing words and 1900 → 1896/1884 B, full TU. The later state reloads remain intact.
- `func_801B5650`: the sibling’s initial-state lifetime change reduces 368 → 361 differing words and 1940 → 1936/1916 B, full TU.
- `func_801B5DCC`: grouping the result and four float values into a carousel-frame local reduces 341 → 339 differing words at 1896/1884 B, full TU. This remains a nonmatching draft.
- `func_801B5DCC`: placing the wrap temporary before the grouped frame local reduces 339 → 330 differing words at 1896/1884 B, full TU. The grouped version also recovers the original 0x38-byte stack frame, though individual spill slots and logic still differ.
- `func_801B5DCC`: using the initial height record’s four-byte stride directly reduces 330 → 318 differing words and 1896 → 1892/1884 B, full TU. It avoids sharing the intermediate index used by the separate eight-byte rotation table.
- `func_801B5650`: the sibling height-record stride change reduces 361 → 352 differing words and 1936 → 1932/1916 B, full TU.
- `func_801B5DCC`: computing the initial height and z before loading rotation, and using the rotation table’s eight-byte stride directly, reduces 318 → 303 differing words and 1892 → 1888/1884 B, full TU.
- `func_801B5650`: the sibling height/rotation load-order and stride change reduces 352 → 323 differing words and 1932 → 1928/1916 B, full TU.
- Carousel siblings: corrected `func_801AFA48` to its existing one-integer-argument definition and passed the card pointer as that argument. The old drafts incorrectly passed four arguments. This reduces `func_801B5DCC` 303 → 157 words and 1888 → 1884/1884 B, and `func_801B5650` 323 → 272 words and 1928 → 1924/1916 B, full TU. Both remain drafts.

- `func_801BADEC`: reversing the operands of the x-coordinate addition reduces 101 → 100 differing words at 560/568 B, full TU. Direct counter globals and alternate lifetimes did not improve it. Still nonmatching.

- `func_801BB7B4`: checked `func_8002F6DC` against its definition; it takes one voice argument. The older draft passes extra arguments to force live values across the call. A one-argument diagnostic compiles to 936/940 B and 231 differing words in declaration context; saved separately because it still needs type and full-TU reconciliation and does not improve the score.

- `func_801B5DCC`: reusing the earlier wrap temporary as the 8.0f rotation divisor reduces 157 → 155 differing words, still 1884/1884 B in the full TU. The value is used for the real division; the draft remains nonmatching.
- `func_801B5650`: the same divisor temporary reduces 272 → 271 differing words, 1924/1916 B in the full TU; still nonmatching.

- `func_801B677C`: computing the remaining count directly at its uses reduces 117 → 79 differing words and 492 → 484/480 B in the full TU; it avoids extra temporary copies. The two uses occur before either argument changes. Still nonmatching.
- `func_801B677C`: expressing the negative branch as `-(remainder * 2) * 9 * 4` reduces 79 → 2 differing words and 484 → 480/480 B, full TU. Only the ordering of the final comparison and an addition remains.
- `func_801B677C`: MATCHED, 480 B. Normalized, readable statement layout gives exact full-TU code. Clean extract/build/progress passed; ROM byte-identical and inventory reports T4.

- `func_801BBC84`: retain the heat threshold across the fire loop and reload it immediately after the second random call, as the assembly does. A pointer to the same real threshold is used for the reload. This reduces 112 → 99 differing words and 508 → 512/516 B, full TU. Still nonmatching.
- `func_801BBC84`: compute the column pointer directly from the array before initializing the row cursor. This reduces 99 → 71 differing words and restores the 516-byte size in the full TU; still nonmatching.

- `func_801BBE88`: use the usual block-local command pointer for each display-list command. This reduces 140 → 73 differing words at 808/808 B in the full TU; the scopes each contain a real command. Still nonmatching.
- `func_801BBE88`: using the same word-store order for the texture commands reduces 73 → 63 differing words at 808/808 B, full TU. Still nonmatching.
- `func_801B6528`: MATCHED, 596 B. Block-local command pointers, the normal display-list macro form, recover the original card-pointer register. Clean extract/build/progress passed; ROM byte-identical and inventory reports T4.
- `func_801B43A8`: reconciled the draft’s existing 11-byte table view with the array declaration used by the matched `func_801B6528`; score remains 27 words in the full TU.

- `func_801B1210`: block-local display command pointers reduce 28 → 27 differing words at 284/284 B, full TU. Removed the old unused cursor declarations; still nonmatching.

- `func_801ADA04`: a named predicate for whether the mode needs adjustment reduces 18 → 14 differing words at 208/208 B, full TU. The predicate controls the existing adjustment; still nonmatching.

- `func_801B43A8`: express the three-entry shuffle groups as a loop that advances to the completed entry cursor. This reduces 27 → 21 differing words at 196/196 B in the full TU; each inner loop advances that cursor exactly three bytes. Still nonmatching.
- `func_801B43A8`: moving the independent random shift after the completed swap yields a 15-word, 192/196-byte diagnostic. The exact-size 21-word draft remains the primary version.
- `func_801B43A8`: retaining the independent group increment after the reordered swap reduces the exact-size draft from 21 → 5 differing words at 196/196 B, full TU. The remaining differences are the group-base setup and one addition operand order.
- `func_801B43A8`: MATCHED, 196 B. Keeping the table end address and deriving the first group as an integer address recovers the original address-load scheduling; the loop swaps the same three entries per group. Clean extract/build/progress passed with all images and ROM byte-identical; inventory reports T4.
