# T-156 notes (main image)

Result: 5 newly T4, 2,048 B (M2 113,824 -> 115,872 B): func_800268C0 236, func_8002A900 220,
func_8002B22C 380, func_800241BC 820, func_80026738 392. Clean toolbox build, ROM sha1 ba52e91b....

Causes:
- 800268C0: no hw/hh/w/h temps; offsets read as a typed `T032Offset {u8 byte[4]}` table at +8; sum written base + b0 + b1<<8 + b2<<16 + b3<<24.
- 8002A900: `count = 0` first, local `u16 *current = &D_80048148` (keeps IDO from sharing the global's address).
- 8002B22C: it is the SDK audio-example dmaCallBack; writing it in the SDK's statement order matched at once.
- 800241BC: call-site prototype boot_dma_chunked(s32,s32,s32) with (s32) casts (as boot_dma); sums base + b4 + b5<<8 ...; one `res` pointer, no size local.
- 80026738: effect list is an s16 array walked with i += 4 (`i = 0` declared at top); sprite fields via D_8004CED0[D_8004EA78].x;
  scale is s32 loaded through (u16); width is u32; no x/y/sprite webs competing for saved registers.

Tools: cmp.py (instruction diff, REGMASK/RONORM/COUNT/K), t.sh/try.py (variant batches), perm.py (line permutations),
slots.py (term-order search), runlist.sh. Lesson: remove temps that steal saved registers, then check regmask=0 before exact.
Unmatched drafts: 306B8 (best draft in func_800306B8.c: structure close, 127 words regmask; IDO sinks w-1/h-1 and spills `text`),
80012390 (i1.c ~35 words), 8002FDA0, 8002FB80, 800241BC done, 800300DC, 80024028, 8001BDE0, 80023EF0.
