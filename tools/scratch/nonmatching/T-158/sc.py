import sys
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
fn=sys.argv[1]
for f in sys.argv[2:]:
    print(f, lib.score_src(fn, open(f).read(), prefix=(__import__('os').environ.get('PREFIX')=='1')))
