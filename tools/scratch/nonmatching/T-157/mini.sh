#!/bin/bash
R=/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-e98bbe33
cd $R
toolbox run -c kig-build bash -c ".venv/bin/python tools/scratch/nonmatching/T-154/mini.py $1" | grep -v "^$" | sed 's/^ *[0-9a-f]*:\t//'
