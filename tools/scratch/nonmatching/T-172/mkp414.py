import sys
sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
BASE = open('tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
text = BASE.replace('''    s32 sp48;
''', '''    s32 *a414;
    s32 sp48;
''').replace('''    osRecvMesg(D_8004A298, &D_801CD458, 1);''',
                 '''    osRecvMesg(D_8004A298, &D_801CD458, 1);
    a414 = &D_8004A414;''').replace(
    'D_8004A414--;', '(*a414)--;').replace(
    'D_8004A414 < 2', '(*a414) < 2')
assert 'a414' in text
open('/tmp/p414.c', 'w').write(text)
print('wrote', len(text))
