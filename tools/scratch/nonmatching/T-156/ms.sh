#!/bin/bash
# usage: ms.sh file.c  -> show lines with D_8004EA78 relocs (standalone compile)
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4122d48a
toolbox run -c kig-build bash -c ".venv/bin/python tools/scratch/nonmatching/T-154/mini.py $1" | grep -B1 "D_8004EA78" | grep -v "^--"
