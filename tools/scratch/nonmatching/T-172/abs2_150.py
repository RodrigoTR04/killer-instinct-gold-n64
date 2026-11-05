"""Abs-form sweep at the 94-word base for func_8002E150."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_8002E150.c').read()
ABS = '''        a = x;
        if (a < 0.0) a = -x;
'''
assert ABS in BASE

FORMS = {
    'neg_a': '        a = x;\n        if (a < 0.0) a = -a;\n',
    'neg_x': '        a = x;\n        if (a < 0.0) a = -x;\n',
    'brace': '        a = x;\n        if (a < 0.0) { a = -x; }\n',
    'brace_a': '        a = x;\n        if (a < 0.0) {\n            a = -a;\n        }\n',
    'tern_x': '        a = x;\n        a = (x < 0.0) ? -x : a;\n',
    'tern2': '        a = (x < 0.0) ? -x : x;\n',
    'elsec': '        if (x < 0.0) {\n            a = -x;\n        } else {\n            a = x;\n        }\n',
    'negfirst': '        a = -x;\n        if (a > x) a = x;\n',
    'do_wrap': '        do { a = x; } while (0);\n        if (a < 0.0) a = -x;\n',
    'cmp_on_x': '        a = x;\n        if (x < 0.0) a = -x;\n',
}
v = {k: BASE.replace(ABS, s) for k, s in FORMS.items()}
detail.run('func_8002E150', v, jobs=10)
