#!/bin/bash
# usage: ra.sh fn draft pattern
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-b5eddd10
toolbox run -c kig-build bash -c ".venv/bin/python tools/scratch/nonmatching/T-154/asm.py $1 $2 | grep -B3 -A2 '$3'"
