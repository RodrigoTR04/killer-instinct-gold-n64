#!/bin/bash
# usage: m.sh fn draft  -> screen word count (full TU)
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-e98bbe33
toolbox run -c kig-build bash -c ".venv/bin/python tools/scratch/nonmatching/T-157/measure.py $1 $2"
