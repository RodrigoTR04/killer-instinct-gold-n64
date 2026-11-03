#!/bin/bash
# usage: c.sh fn draft  -> full cmp output (env passes through: COUNT, REGMASK, RONORM, PREFIX, STACK)
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-b7e0fb3a
toolbox run -c kig-build bash -c "PREFIX=${PREFIX:-} COUNT=${COUNT:-} REGMASK=${REGMASK:-} RONORM=${RONORM:-1} STACK=${STACK:-} .venv/bin/python tools/scratch/nonmatching/T-155/cmp.py $1 $2"
