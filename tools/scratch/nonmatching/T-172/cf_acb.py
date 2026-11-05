"""Control-flow shape sweep for func_801ACB1C."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()

NESTED = '''    if (*D_801CD458 != 1) {
        if (*D_801CD458 == 2) {
            D_8004A414--;
        }
    } else {
'''
assert NESTED in BASE

v = {'base_nested': BASE}

# 1. plain if / else if
v['else_if'] = BASE.replace(NESTED, '''    if (*D_801CD458 == 1) {
''').replace('''        func_801ADA04(&D_802C9F70);
    }
}''', '''        func_801ADA04(&D_802C9F70);
    } else if (*D_801CD458 == 2) {
        D_8004A414--;
    }
}''')

# 2. guard-clause early return
v['guard'] = BASE.replace(NESTED, '''    if (*D_801CD458 != 1) {
        if (*D_801CD458 == 2) {
            D_8004A414--;
        }
        return;
    }
''')

# 3. switch
v['switch'] = BASE.replace(NESTED, '''    switch (*D_801CD458) {
    case 1:
''').replace('''        func_801ADA04(&D_802C9F70);
    }
}''', '''        func_801ADA04(&D_802C9F70);
        break;
    case 2:
        D_8004A414--;
        break;
    }
}''')

# 4. local for the message, == 2 first
v['msg_local'] = BASE.replace(NESTED, '''    {
        s16 msg = *D_801CD458;
        if (msg != 1) {
            if (msg == 2) {
                D_8004A414--;
            }
        } else {
''').replace('''        func_801ADA04(&D_802C9F70);
    }
}''', '''            func_801ADA04(&D_802C9F70);
        }
    }
}''')

# 5. decrement first, big arm second
v['two_if'] = BASE.replace(NESTED, '''    if (*D_801CD458 == 2) {
        D_8004A414--;
    } else if (*D_801CD458 == 1) {
''')

# 6. != 1 nested but the == 2 test written as != 2 with empty
v['neg2'] = BASE.replace('''        if (*D_801CD458 == 2) {
            D_8004A414--;
        }''', '''        if (*D_801CD458 != 2) {
        } else {
            D_8004A414--;
        }''')

detail.run('func_801ACB1C', v, jobs=6)
