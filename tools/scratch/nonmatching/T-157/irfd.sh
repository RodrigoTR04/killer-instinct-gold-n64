#!/bin/bash
# usage: irfd.sh draft_with_own_includes.c -> /tmp/t157/s/d.s (pre-as1 stream)
R=/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-e98bbe33
mkdir -p /tmp/t157/s; cp $1 /tmp/t157/s/d.c
toolbox run -c kig-build bash -c "cd /tmp/t157/s && $R/tools/ext/ido/5.3/cc -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O2 -mips2 -32 -I$R/include -S d.c 2>&1 | tail -n 3"
