#!/bin/bash
# usage: c.sh fn draft  -> cmp output (env: COUNT, REGMASK, RONORM, PREFIX, STACK)
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-2ff97d91
toolbox run -c kig-build bash -c "PREFIX=${PREFIX:-} COUNT=${COUNT:-} REGMASK=${REGMASK:-} RONORM=${RONORM:-1} STACK=${STACK:-} .venv/bin/python tools/scratch/nonmatching/T-158/cmp.py $1 $2"
