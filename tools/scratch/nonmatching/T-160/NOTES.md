# T-160 follow-up

`func_801C2F5C` is 7 differing instructions in the full-TU comparison, down from 24 in the prior draft, exact 544 bytes. Read the sprite scale directly again in the scaled assignment, retaining the original scale separately for restoration; update the x position with a compound assignment. Remaining differences are the temporary registers for the selector address and the later layout pointer. The 180-second honest-weight permuter run found only line-grouping changes which did not improve the full-TU result.

`func_801B0520`: parameter reuse, frame store scheduling and direct global-read variants did not improve the 10-word draft. `func_801BDA6C`: moving the alpha read before the colour command, changing its width and comparing the saved alpha did not improve the 37-instruction draft. `func_801B446C`: a casted struct view of the flag, cursor and mode did not eliminate the global-address difference.
