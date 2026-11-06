#!/bin/bash
# usage: permrun.sh fn draft seconds [seed-tag]
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-a52eff74
fn=$1; draft=$2; secs=${3:-480}; tag=${4:-a}
dir=/tmp/pm173_${fn}_$tag
rm -rf $dir
toolbox run -c kig-build bash -c ".venv/bin/python tools/permuter/import_fn.py $fn $dir --draft $draft" >/dev/null 2>&1
cat >> $dir/settings.toml <<'EOT'

[weight_overrides]
perm_empty_stmt = 0
perm_ins_block = 0
perm_add_self_assignment = 0
perm_dummy_comma_expr = 0
perm_xor_zero = 0
perm_mult_zero = 0
perm_pad_var_decl = 0
perm_duplicate_assignment = 0
perm_var_cond_block = 0
perm_add_mask = 0
perm_float_literal = 0
perm_remove_var = 0
perm_long_chain_assignment = 0
EOT
timeout --signal=INT --kill-after=15s ${secs}s toolbox run -c kig-build bash -c ".venv/bin/python tools/ext/decomp-permuter/permuter.py $dir --stack-diffs --best-only --better-only --stop-on-zero -j ${JOBS:-12}" > $dir.log 2>&1
tr '\r' '\n' < $dir.log | grep -a "base score\|new best\|Found" | tail -5
ls $dir/output-* 2>/dev/null | head
