#!/bin/bash
# usage: hoist.sh file.c -> prints first 45 asm lines of the function (to see loop-1 hoists)
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4122d48a
toolbox run -c kig-build bash -c ".venv/bin/python tools/scratch/nonmatching/T-156/asm.py func_800306B8 $1" | sed -n 1,${2:-45}p | awk '{printf "%s %s %s;  ", $2,$3,$4} END{print ""}'
