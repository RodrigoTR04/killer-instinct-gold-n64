#!/bin/bash
# usage: lab.sh file.c  -> ugen stream (-S) to stdout. file must be self-contained (typedefs included)
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-a52eff74
b=$(basename $1 .c)
toolbox run -c kig-build bash -c "cd /tmp && /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-a52eff74/tools/ext/ido/5.3/cc -S -G 0 -non_shared -Xcpluscomm -O2 -mips2 -32 -I/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-a52eff74/include /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-a52eff74/$1 && cat /tmp/$b.s"
