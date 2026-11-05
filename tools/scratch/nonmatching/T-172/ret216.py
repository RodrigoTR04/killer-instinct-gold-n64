"""Express func_800216D4's return without a zero-initialised `loaded` local.

Target facts (from the splat):
  * no `loaded = 0` store in the prologue,
  * the found-length is stored at sp+0x5c (2 uses) and the return reads sp+0x5c,
  * the header size (s5) is a separate register, and sp+0x60 holds the rounded
    start offset.
So the original's "loaded" is a value produced only in the found branch and
otherwise read from the same slot; model that with a variable assigned in the
branch and returned directly.
"""
import sys

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_800216D4.c').read()
assert 'loaded = 0' in BASE

v = {'base226': BASE}

# return inside the found branch, zero after the loop (honest: both paths defined)
RET = BASE.replace('''            loaded = size + offset;
            loaded += loaded & 7;
            boot_dma((s32)start, (s32)destination, loaded);
            if (offset) memcpy(destination, header, loaded - offset);''',
                   '''            loaded = size + offset;
            loaded += loaded & 7;
            boot_dma((s32)start, (s32)destination, loaded);
            if (offset) memcpy(destination, header, loaded - offset);
            done = loaded;''')
assert RET != BASE
v['done_temp'] = RET.replace('    s32 offset, size, loaded = 0;',
                             '    s32 offset, size, loaded;\n    s32 done = 0;').replace(
    '    return loaded - offset;', '    return done - offset;')

# guard style: return early from inside the loop when found
v['early_return'] = BASE.replace('''        if (wanted == id) {
            loaded = size + offset;
            loaded += loaded & 7;
            boot_dma((s32)start, (s32)destination, loaded);
            if (offset) memcpy(destination, header, loaded - offset);
        }
        scan += size;
    } while (wanted != id && (u32)scan < (u32)end);''',
                                 '''        if (wanted == id) {
            loaded = size + offset;
            loaded += loaded & 7;
            boot_dma((s32)start, (s32)destination, loaded);
            if (offset) memcpy(destination, header, loaded - offset);
            break;
        }
        scan += size;
    } while ((u32)scan < (u32)end);''')
v['early_return'] = v['early_return']  # keep base's loaded = 0 for now
print(len(v), 'variants', flush=True)
detail.run('func_800216D4', v, jobs=2)
