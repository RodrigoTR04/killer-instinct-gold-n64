#!/bin/bash
# usage: d.sh fn draft [env...] -> diff
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4122d48a
fn=$1; shift; d=$1; shift
toolbox run -c kig-build bash -c "RONORM=1 $* .venv/bin/python tools/scratch/nonmatching/T-156/cmp.py $fn $d"
