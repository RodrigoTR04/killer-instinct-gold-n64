#!/usr/bin/env python3
"""Audit T-080 source provenance, C ownership, and linked byte equality.

Run after the normal clean build. The optional fetched SM64 input is used only
for the provenance check; the build itself never depends on that tree.
"""
import json
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[4]
BASE = Path(__file__).resolve().parent
SM = ROOT / 'tools/scratch/libultra/sm64'


def main():
    count = 0
    for segment in ('boot', 'main'):
        placements = json.loads((BASE / f'{segment}.json').read_text())
        map_path = ROOT / ('build/kig.us.map' if segment == 'boot' else 'build/main.map')
        owners = {}
        owner = ''
        for line in map_path.read_text().splitlines():
            obj = re.search(r'\s(\S+\.o)\s*$', line)
            if obj:
                owner = obj[1]
            symbol = re.fullmatch(r'\s*0x([0-9a-fA-F]+)\s+(\w+)\s*', line)
            if symbol:
                owners[symbol[2]] = (int(symbol[1], 16), owner)
        original = (ROOT / ('baserom.us.z64' if segment == 'boot' else 'build/segments/main.bin')).read_bytes()
        linked = (ROOT / ('build/kig.us.z64' if segment == 'boot' else 'build/main.bin')).read_bytes()
        image_base = 0x7FFFF400 if segment == 'boot' else 0x8000F960
        for placement in placements:
            source = ROOT / f'src/{segment}/{placement["name"]}.c'
            expected_owner = f'build/src/{segment}/{placement["name"]}.c.o'
            assert 'GLOBAL_ASM' not in source.read_text()
            assert not re.search(r'\b(?:__asm__|asm)\s*\(', source.read_text())
            if SM.exists():
                expected = (SM / placement['source']).read_text()
                expected = re.sub(r'^#include[^\n]*\n', '', expected, flags=re.M)
                if segment == 'main' and placement['source'] == 'lib/src/string.c':
                    expected = re.sub(r'\b(memcpy|strlen|strchr)\b', lambda m: 'main_' + m[1], expected)
                actual = source.read_text().split('#include "sdk/libultra.h"\n', 1)[1]
                assert actual == expected, f'non-verbatim source: {source}'
            start, end = placement['base'] - image_base, placement['end'] - image_base
            assert linked[start:end] == original[start:end], placement['name']
            for row in placement['rows']:
                name = row['name']
                if segment == 'main' and placement['source'] == 'lib/src/string.c':
                    name = 'main_' + name
                address, owner = owners[name]
                assert address == int(row['vram'], 16), (name, hex(address), row['vram'])
                assert owner == expected_owner, (name, owner, expected_owner)
                count += 1
        # Section start addresses matter even for NOLOAD BSS, which ROM checks
        # alone cannot validate. Check the actual input-section placement in ld's map.
        for section in json.loads((BASE / f'{segment}-sections.json').read_text()):
            obj = f'build/src/{segment}/{section["name"]}.c.o'
            pattern = (r'^\s*' + re.escape(section['section']) + r'\s+(?:\n\s*)?'
                       + r'0x([0-9a-fA-F]+)\s+0x([0-9a-fA-F]+)\s+' + re.escape(obj) + r'$')
            found = re.search(pattern, map_path.read_text(), re.M)
            assert found, (obj, section['section'])
            assert int(found[1], 16) == section['base'], (obj, found[1], hex(section['base']))
            assert int(found[2], 16) == section['bytes'], (obj, found[2], section['bytes'])
        print(f'{segment}: {len(placements)} SDK C objects; text/data/BSS placement verified')
    print(f'{count} excluded SDK functions: C-owned and linked-exact; verbatim source verified when fetched')


if __name__ == '__main__':
    main()
