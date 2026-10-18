#!/usr/bin/env python3
"""Check rebuilt decompressed CPU images against the extraction manifest."""
import hashlib
import json
from pathlib import Path


def main():
    manifest = {row['name']: row for row in json.loads(Path('build/segments/manifest.json').read_text())}
    failed = False
    for name in ('main', 'ovl_7DF8', 'ovl_7E00'):
        data = Path(f'build/{name}.bin').read_bytes()
        digest = hashlib.sha1(data).hexdigest()
        ok = digest == manifest[name]['sha1'] and len(data) == manifest[name]['size']
        print(f'{"OK" if ok else "FAIL"}: {name} {digest} ({len(data)} bytes)')
        failed |= not ok
    raise SystemExit(int(failed))


if __name__ == '__main__':
    main()
