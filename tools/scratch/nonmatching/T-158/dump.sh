#!/bin/bash
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-67556935
toolbox run -c kig-build bash -c ".venv/bin/python tools/scratch/nonmatching/T-158/dump.py $1 $2"
