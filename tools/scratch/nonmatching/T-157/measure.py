#!/usr/bin/env python3
"""Score specific (function, draft) pairs with the screen.py compiler path.

screen.py only globs T-0*/ drafts; this driver lets T-153 score its own
drafts (and T-149's) in the owning TU, with the same relocation masks.
"""
import argparse
import importlib.util
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('function')
    ap.add_argument('draft')
    ap.add_argument('--full', action='store_true', help='require the full owning TU')
    args = ap.parse_args()
    draft = Path(args.draft)
    if not draft.is_absolute():
        draft = ROOT / draft
    attempts = ((False, False), (True, False), (True, True))
    errors = []
    for prefix, declarations in attempts:
        if args.full and prefix:
            break
        try:
            out = screen.measure(args.function, draft, prefix, declarations)
            print(f"{args.function} words={out['words']} compiled={out['compiled']} "
                  f"original={out['original']} context={out['context']}")
            return 0
        except Exception as error:
            errors.append(str(error))
    print(f'{args.function}: FAILED', file=sys.stderr)
    for error in errors:
        print(screen.diagnostic(error), file=sys.stderr)
    return 1


if __name__ == '__main__':
    sys.exit(main())
