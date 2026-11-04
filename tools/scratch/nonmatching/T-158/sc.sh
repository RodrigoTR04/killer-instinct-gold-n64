#!/bin/bash
# usage: sc.sh fn draft...   -> (masked, exact, frame, ninstr)
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-67556935
fn=$1; shift
toolbox run -c kig-build bash -c "PREFIX=${PREFIX:-} .venv/bin/python tools/scratch/nonmatching/T-158/sc.py $fn $*"
