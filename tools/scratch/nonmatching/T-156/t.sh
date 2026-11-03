#!/bin/bash
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4122d48a
toolbox run -c kig-build bash -c ".venv/bin/python tools/scratch/nonmatching/T-156/try.py \"\$@\"" _ "$@"
