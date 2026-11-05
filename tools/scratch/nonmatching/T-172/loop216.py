"""Restructure func_800216D4's second loop to reload p+4 and keep size/offset in slots."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_800216D4.c').read()
OLD = '''    p = destination;
    while ((u32)(p + 15) < (u32)(destination + size)) {
        do { id = p[0] + (p[1] << 8); } while (0);
        entry = &T172_CACHE[id][player];
        if (id == D_80045D8C[bank][alternate]) {
            alternate++;
            entry->second = p;
        } else if (!entry->first) {
            entry->first = p;
        } else {
            entry->second = p;
        }
        p += T172_LE216(p + 4);
    }
'''
assert OLD in BASE

v = {'base': BASE}

# recompute the header size from p each iteration without caching
v['reload'] = BASE.replace(OLD, '''    p = destination;
    while ((u32)(p + 15) < (u32)(destination + size)) {
        id = p[0] + (p[1] << 8);
        entry = &T172_CACHE[id][player];
        if (id == D_80045D8C[bank][alternate]) {
            alternate++;
            entry->second = p;
        } else if (!entry->first) {
            entry->first = p;
        } else {
            entry->second = p;
        }
        p = p + p[4] + (p[5] << 8) + (p[6] << 16) + (p[7] << 24);
    }
''')

# second cache loop with the exact target test order (first then second, two bnez)
v['cache2'] = BASE.replace('''    for (i = 0; i < 256; i++) {
        entry = &T172_CACHE[i][player];
        if (!entry->first && !entry->second) {
            if (D_80045D8C[bank][0] == 0) entry->second = destination;
            else entry->first = destination;
        }
    }
''', '''    for (i = 0; i < 256; i++) {
        entry = &T172_CACHE[i][player];
        if (entry->first) continue;
        if (entry->second) continue;
        if (D_80045D8C[bank][0]) entry->first = destination;
        else entry->second = destination;
    }
''')
v['cache2b'] = BASE.replace('''        if (!entry->first && !entry->second) {
            if (D_80045D8C[bank][0] == 0) entry->second = destination;
            else entry->first = destination;
        }
''', '''        if (!entry->first) {
            if (!entry->second) {
                if (D_80045D8C[bank][0]) entry->first = destination;
                else entry->second = destination;
            }
        }
''')
v['both'] = v['reload'].replace('''        if (!entry->first && !entry->second) {
            if (D_80045D8C[bank][0] == 0) entry->second = destination;
            else entry->first = destination;
        }
''', '''        if (!entry->first) {
            if (!entry->second) {
                if (D_80045D8C[bank][0]) entry->first = destination;
                else entry->second = destination;
            }
        }
''')
detail.run('func_800216D4', v, jobs=4)
