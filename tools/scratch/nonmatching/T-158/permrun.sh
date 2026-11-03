#!/bin/bash
# usage: permrun.sh fn draft seconds   -> runs decomp-permuter with honest-only mutation weights; prints best scores
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-67556935
fn=$1; draft=$2; secs=${3:-480}
dir=/tmp/pm158_$fn
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
perm_randomize_internal_type = 0
perm_randomize_external_type = 0
perm_randomize_function_type = 0
perm_alias_array = 0
perm_long_chain_assignment = 0
EOT
timeout --signal=INT --kill-after=15s ${secs}s toolbox run -c kig-build bash -c ".venv/bin/python tools/ext/decomp-permuter/permuter.py $dir --stack-diffs --best-only --better-only --stop-on-zero -j 14" > $dir.log 2>&1
tr '\r' '\n' < $dir.log | grep -a "base score\|new best" | tail -3
