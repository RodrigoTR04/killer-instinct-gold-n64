#!/bin/bash
# usage: runlist.sh fn listfile  (names in v/)
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4122d48a
toolbox run -c kig-build bash -c "for n in \$(cat tools/scratch/nonmatching/T-156/$2); do f=tools/scratch/nonmatching/T-156/v/\$n.c; e=\$(COUNT=1 RONORM=1 .venv/bin/python tools/scratch/nonmatching/T-156/cmp.py $1 \$f 2>&1 | tail -1 | sed 's/.*diffwords=//'); r=\$(COUNT=1 RONORM=1 REGMASK=1 .venv/bin/python tools/scratch/nonmatching/T-156/cmp.py $1 \$f 2>&1 | tail -1 | sed 's/.*diffwords=//'); echo \$n \$e \$r; done"
