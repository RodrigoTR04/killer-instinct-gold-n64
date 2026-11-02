#!/bin/bash
# usage: d.sh fn draft [reg]   -> unified diff (REGMASK if 3rd arg)
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-b5eddd10
toolbox run -c kig-build bash -c "PREFIX=${PREFIX:-} RONORM=${RONORM:-} ${3:+REGMASK=1} .venv/bin/python tools/scratch/nonmatching/T-154/cmp.py $1 $2"
