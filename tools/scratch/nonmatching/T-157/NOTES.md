# T-157 working notes (large ovl_7DF8 drafts)

Start commit ccf7dc0 (M2 113,824 B). Clean toolbox baseline build verified (sha1 ba52e91b...).

## Status (update at the end)
Scores are "differing instruction lines" vs the original splat asm (LCS, `fast.py`): reg-masked / exact.
| Function | Bytes | Start (screen words) | Best now |
|---|---:|---:|---|
| func_801BCB70 | 1,676 | 391 | see `w/best*_cb70.c` |
| func_801BFCBC | 2,388 | 596 | `bf/best_bf.c` |
Everything else untouched (hundreds of words off).

## What the clean-room rewrite of func_801BCB70 established
* The routine is a sprite/tile drawer that emits `gDPSetPrimColor`, `gDPLoadTextureTile` (7 commands) and
  `gSPScisTextureRectangle` (3 commands) with SDK semantics: `_SHIFTL`, `MAX(x,0)/MIN(x,0)` ternaries,
  `(s - MIN((xl * dsdx) >> 7, 0))`, one block-scoped `Gfx *_g = pkt++` per command.
  The old m2c draft had the right size but 300+ words of frame/temps noise.
* Idioms that mattered (each reduced the diff a lot): `/ 1024` with an *int* literal (div.s); `u16 bit` and `bit <<= 1`
  (gives the spilled outer bit and the inner copy); `s32 x`/`s32 col` (signed `x - 1` compare, no unsigned float fixup);
  `u16 run` with `while ((mask[col + run] & bit) && run < 5) run++` (lazy `andi`); `xl/yl/xh/yh` as real s32 locals
  (frame 0x138 exactly); the loop bound recomputed as `(u32) i < bottom - top` instead of reusing `rows`;
  statement order inside the clamp block; line joins of the command statements (IDO schedules per source line).
* Remaining differences are register allocation / scheduling only (instruction count and frame match).

## Tools (this directory)
* `fast.py` standalone evaluator (compile only the draft with common.h; ~3 s): `(regmasked LCS, exact LCS, ninstr, frame)`.
* `cmp.py` canonical diff (relocs folded to absolute addresses incl. `%lo(sym+N)`), `side.sh` side-by-side, `hunks.py`.
* Search drivers: `dsh.py` (declaration order), `joinclimb.py` (line joins), `permblocks.py` (statement permutations),
  `mutclimb.py` (swap/join/decl/sign, optional annealing), `pairs.py`, `altclimb.py` (operand alternatives),
  `gen3.py` (variable-set enumeration), `prun.sh` (decomp-permuter with the dummy-construct passes disabled).
* `mini.sh` + `mini/*.c`: toy compiles used to learn IDO behaviour.

## Findings that generalise
* Permuter results that use `do {} while (0)` or `new_var = _g` copies score best but are artificial; they were discarded.
* Byte read-modify-write on a global (`D |= bit`) gets `lui/addiu` address sharing only in the entry block or when the
  global has several references in one region; a `volatile` declaration reproduces the target's shared form everywhere
  (func_801BFCBC sites D_802D3810/D_802D3828) but volatile is not allowed, so that function is parked.
* Global kept un-shared and reloaded after a store (`lui at; sh` / `lui t8; lhu`): write and reload through
  `u16 *p = &G` with a local copy for the compare (`v = *p; if (v < N) { *p = v + k; ... *p }`).
* `x ^ -1` instead of `~x` gives `xor` with -1 (target mask of the glyph store).
* A switch-like layout (`if (c != 29) { if (c != 27) { if (c < 26) A } else B }`) reproduces `beq 29; beq 27; slti`.

## Update (BC1B0 + search tooling)
* func_801BC1B0 (2,496 B) is the same tile-drawer family as BCB70 (callers pass fmt=2 only). Drafts in bc/; best so far bc/z1_p31_sw.c
  (reg-masked 178, mnemonic multiset within ~5 of the target, frame 0x1A0). Param map: dl, tex, fmt, texW, texH, stepX, cellW, top,
  left, bottom, right, fx, fy0, scale, flip. fmt 0/2 = gDPLoadTextureTile 16b/8b, fmt 1 = 16b tile + gDPLoadMultiTile_4b at tmem 0x1C0
  (uls+16/lrs+16). Rect: E4 (x1c,y1c clamps 0xA00/0x780, xl=(s32)x0f, yl=(s32)fy), B3 (S = (i-0.5+top)*32+tOff, T=(x-0.5)*32), B2.
* Layout facts: the 3-way format dispatch is `switch (fmt) { case 2: ... case 0: ... default: ... }` (switch with default reproduces the
  target's displaced default body; nested if/else does not). texW/texH are u32 (`srl`). yl/tCo are kept in FPRs with deferred mfc1.
* Tools: mset.py (mnemonic multiset diff), edit.py (LCS edit script), sd.py (side-by-side, --t by target index), lay.py (branch skeleton),
  sregs.py (saved-reg roles), sweep.py (statement position descent), gen6.py, homeclimb.py (objective = stack-home mismatch, mset, pscore/exact).
* BCB70: the whole remaining diff is (a) uls `b` (else arm exists in target; any else-arm form flips promotion of `i` into a register and
  `bit` into a saved reg), (b) bb1 filler (x0f add.s vs texW lw), (c) saved-reg numbering of mask/lrs/lrt/w0/mflo2 (same webs, permuted),
  (d) rows spill slot. Same set of webs live in saved regs in target and mc10.
* Method notes: foreground sleeps are blocked; poll with python time.sleep loops. Never `pkill -f` (kills own shell).

# FULL SESSION LOG (T-157, worker) — state at hand-off
Goal (unchanged): >= 2,030 B newly T4 in the 12 big ovl_7DF8 functions, honest C only. STATUS: 0 B landed. No src/ change. No function is T4.

## Best drafts (all under tools/scratch/nonmatching/T-157/)
* func_801BCB70 (1,676 B): w/mc10.c = 13 reg-masked / 64 exact differing lines, 418 vs 419 instr, frame 0x138 OK, pscore 1387.
  Remaining: (a) uls `b` (target has else-arm; any else-arm/ternary form flips `i` into a register and `bit` into a saved reg, homes
  0xe0/0xe6/0xf0/0xf4/0x12c must stay memory-resident), (b) bb1 filler (target add.s x0f vs ours lw texW), (c) saved-reg numbering of the SAME webs
  (target s0 mask,s1 lrs,s2 lrt,s3 uls,s4 top,s5 y1c,s6 mflo,s7 w0,fp mflo2,ra col; mc10 permutes mask/lrs/lrt and w0/mflo2), (d) rows spill 0x94 vs 0x98.
  Finding: order of the four statements uls/lrs/ult/lrt matters: with the ternary uls, only orders with `ult` FIRST keep `i` in memory (homes=0),
  but target code order is uls,lrs,ult,lrt. A climb that reached homes=0 with the right order used a redundant duplicated clamp line
  (`if (x1c > 640.0f)` before the real one) = artificial, REJECTED (w/fx_91.c, fx_92.c must not be used).
* func_801BC1B0 (2,496 B; alone enough for the goal): bc/z1_p31_sw.c = 178 reg-masked / 445 exact / 620 vs 624 instr / frame 416 OK / pscore 16373
  (first draft was 549/757/626/400/~44000). Saved-register ROLES are identical to the target (s0 uls,s1 lrt,s2 B-word FD88,s3 tex2,s4 ult,s5 y1c,
  s6 x1c,s7 next-x,fp E6 const,ra F4 const), mnemonic multiset within ~5. Remaining diffs are block scheduling/order in the row preheader
  (target ~79 instrs, same set, different order), the loop-top first block (target: y1f, presets, y1 trunc, T float chain, yl trunc, fy copy all
  BEFORE the uls branch; ours has the uls branch first), temp-register naming, spill slot numbers, i/cms/tOff stack homes (target i at 0x194 in memory).
  Source text of the best draft is climber-mangled (joined lines); line joins matter for scheduling. It contains: switch(fmt){case 2,case 0,default},
  `f32 yl` snapshot (`yl = fy; fy = y1f;`, uses `(s32) yl`), `tCo` int local, ternary/preset-if uls/ult, MIN/MAX macros, texW/texH u32.
  Constructs that exist ONLY for matching (must be disclosed if this lands): f32 `yl` snapshot (gives deferred mfc1 + hoisted E6/F4 consts; costs one extra mov.s),
  line joins, `uls = 0; if (pos != 0)` preset form, local count/decl order (frame, spill slots), `tCo`/`sCo`/`mnX`/`mnY` locals (frame 0x1A0).
* func_801BFCBC (2,388 B): bf/best_bf2.c; structure understood; needs `volatile` byte RMW (disallowed) + frame 104 vs 96; PARKED.
* Not touched beyond profiling: ABB20, C08F8, CAA00, C9B14, B47A4, C5298, ADEA0, B6E4C, B849C (all >=2,296 B; OPPORTUNITIES says hundreds of words off).

## BC1B0 facts (decoded from asm; all in bc/a0.c..)
* Callers (src/ovl_7DF8/ovl_7DF8_5ED0.c, ~15 sites with their own `extern void func_801BC1B0(s32 x11, f32, f32, s32, s32)`) always pass fmt=2.
  Param order: dl(Gfx**), tex, fmt, texW, texH, stepX, cellW, top, left, bottom, right, fx, fy0, scale, flip. For integration the existing s32 externs
  force s32 params => need casts: (u32) right/top/cellW in compares/float conversions (unsigned compare `sltu`, `(f64)(u32)top` bgez fixup), or edit the externs.
* Loop: rows=bottom-top; for(i=0;(u32)i<rows;i+=stepX){fy=fy0; for(x=left; x<(u32)right; x+=cellW){...}; accX+=step}. dx=(f32)stepX*(f32)scale/256 (int literal 256);
  flip: tOff=0x2010-(stepX<<5), stepX=-stepX, step=-dx, fx-=((f32)(-((scale<<4)>>8)) - step), cms=1; else cms=2,tOff=0,step=dx.
  Body: div=0x100000/scale; x0f=accX+fx; xl=(s32)x0f; x1=(s32)((f32)xl+dx); pos=i+top; end=i+stepX+top; cellH=(s32)(((f32)cellW*(f32)scale)/256);
  y1f=cellH+fy; y1=(s32)y1f; yl=(s32)old fy; fy=y1f; uls=MAX(pos,0); lrs=MIN(end,bottom-1); ult=MAX(x-1,0); lrt=MIN(x+cellW,right-1);
  x1c=MIN(x1,0xA00); y1c=MIN(y1,0x780); T=(s32)(((f32)((f64)(f32)x-0.5))*32.0f); S=(((s32)(f32)(((f64)(f32)i-0.5)+(f64)top)*32+tOff)&0xFFFF).
  fmt0: FD(fmt,siz2,texW-1,tex) F5(line=((lrs-uls+1)*2+7)>>3, 0x07080200) E6 F4 E7 F5(0x00080200) F2. fmt2: siz1, line=((lrs-uls+1)+7)>>3, F5 w1=_SHIFTL(cms,8,2)|0x07080070/0x00080070.
  fmt1: 16b RGBA tile load (FD10..) then gDPLoadMultiTile_4b-style: FD88xxxx (texW>>1)-1 at tex+texW*texH*2, F5 0xF58801C0|line4, F4 with (uls+16)<<1,(lrs+16)<<1, F5 0xF58001C0|line4 w1 0x01080200, F2 tile1 with <<2.
  Tail: E4(MAX(x1c,0),MAX(y1c,0) | MAX(xl,0),MAX(yl,0)), B3(S-MIN((xl*div)>>7,0), T-MIN((yl*div)>>7,0)), B2(div<<16|div).
* IDO behaviour learned: switch with default (not nested if) reproduces displaced default body; unsigned `>>` => texW u32; the E6/F4 consts are hoisted into fp/ra only
  when yl is NOT a GPR web; yl/tCo become FPR-resident (deferred mfc1) when they lose GPR allocation (mini2/sp1.c reproduces) or are CSE'd expressions of an f32 var (y_f32 trick).
  Unsigned-to-float conversions (top, cellW) create `bgez` fixup blocks that split the preheader into scheduling blocks. `.loc`/line joins influence as1 scheduling.
* Statement sweeps/permutations/decl searches on the f32-yl base plateau at pscore ~16.2k (permuter 18k from 31k base; windowed climbs only improve decl order).

## Tools added this session (tools/scratch/nonmatching/T-157/)
fast.py (score = reg-masked LCS, exact LCS, ninstr, frame, pscore), sd.py (side-by-side, --t by target idx, --diff), edit.py (LCS edit script),
mset.py (mnemonic multiset diff — best "structure equal?" test), lay.py (branch skeleton), raw.py, sregs.py (saved-reg roles), hs.py/homeclimb.py
(objective = stack-home mismatch (HOME_LO/HI), mset diff, pscore|exact; KEYMODE=p|exact; FIXLINES pins statements; WIN_START/WIN_END window; --alts),
sweep.py (coordinate descent of statement positions), gen6.py (random dependency-safe orders of the pre-switch group, prefix-LCS score),
mutclimb.py (+ 'move' op), dstack.py, joinclimb.py, permblocks.py; runners/ holds the shell/python drivers used (runmc*.sh, runhc*.sh, batch.py, perm4.py, imove.py, fyvar.py...).
targets/func_801BC1B0.o was imported via tools/permuter/import_fn.py (strip the `extern void func_801BC1B0(...)` line from base.c or compile fails).
Permuter: /tmp/p157_bc2 (restricted weights) plateaued at 18076 (its scale; base 31004).

## Environment gotchas (burned time)
* Never `pkill -f`/`ps|grep|kill` with a pattern that appears in your own command line: it kills the tool shell (exit 144). Use `ps -eo pid,args | awk '/pat/ && !/awk/ {print $1}'`.
* Foreground `sleep` is blocked; wait with `python3 -c time.sleep(<=598)` inside a command with timeout 600000. t3_background_wait returns immediately (does not block).
* After a python heredoc `cd ../../../..` lands in tools/, not the worktree root; always `cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-e98bbe33` inside toolbox commands.
* sd.py/fast.py need the draft to carry its own typedef/macros; side.sh/cmp.py (full-TU compile) fail for BC1B0 due to the extern prototype.

## Next steps if resumed
1. BC1B0: build candidates with the y/T first block BEFORE the uls branch (as target) AND keep E6/F4 hoisted (yl must not take a GPR); decl-tune each (dsh/homeclimb window) — a batch driver (runners/batch.py) over bc/h_*,c_*,k_*,m_* templates was about to be run (it did not start: queue file permission error) .
2. BCB70: find the else-arm form of uls that keeps `i` unpromoted with order uls,lrs,ult,lrt (candidate: change use counts of other webs honestly); then fix saved-reg numbering by web priority/range.
3. If neither converges, rotate to a logic-heavy function (C08F8/CAA00) using m2c skeleton + mset/edit tooling.
