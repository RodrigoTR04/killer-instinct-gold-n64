#!/bin/bash
# usage: polish.sh in.c outprefix cycles   (runs inside toolbox)
R=/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-e98bbe33; cd $R
T=tools/scratch/nonmatching/T-157
cur=$1; pre=$2
for c in $(seq 1 ${3:-2}); do
  .venv/bin/python $T/permblocks.py func_801BCB70 $cur '^                        pos = i' 4 '^                        uls = 0' 3 '^                        div = 0x100000' 3 '^            x = left' 3 '^    dx = ' 4 '^                    x \+= cellW' 3 '^            bit <<= 1' 3 --key ${KEY:-exact} -j 8 --out ${pre}_p$c.c | tail -1
  .venv/bin/python $T/joinclimb.py func_801BCB70 ${pre}_p$c.c --from '^    dx = ' --to '^    \*dl = g' --rounds 20 -j 8 --key ${KEY:-exact} --out ${pre}_j$c.c | tail -1
  .venv/bin/python $T/dsh.py func_801BCB70 ${pre}_j$c.c --iters 40 --key ${KEY:-exact} -j 8 --seed $c --out ${pre}_d$c.c | grep final
  cur=${pre}_d$c.c
done
