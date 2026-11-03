#!/bin/bash
# usage: c.sh fn draft [reg]  -> diffwords count (REGMASK if 3rd arg)
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-e98bbe33
toolbox run -c kig-build bash -c "COUNT=1 ${3:+REGMASK=1} .venv/bin/python tools/scratch/nonmatching/T-157/cmp.py $1 $2"
