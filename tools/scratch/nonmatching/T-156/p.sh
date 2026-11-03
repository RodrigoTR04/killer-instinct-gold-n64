#!/bin/bash
# usage: p.sh fn draft K [ENV=..]  -> diff of first K instructions only (raw regs unless REGMASK=1)
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4122d48a
fn=$1; shift; d=$1; shift; k=$1; shift
toolbox run -c kig-build bash -c "K=$k RONORM=1 $* .venv/bin/python tools/scratch/nonmatching/T-156/cmp.py $fn $d"
