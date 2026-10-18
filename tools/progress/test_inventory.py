"""Regression coverage for overlapping executable address spaces."""
import csv
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

INVENTORY = Path(__file__).with_name('inventory.py')


class SegmentInventoryTests(unittest.TestCase):
    def test_overlap_migration_and_qualified_overrides(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            folder = root / 'tools/progress'
            folder.mkdir(parents=True)
            (root / 'docs').mkdir()
            for area in ('boot', 'ovl_7DF8', 'ovl_7E00'):
                path = root / 'asm' / area / 'text.s'
                path.parent.mkdir(parents=True)
                path.write_text('.section .text\nglabel func_80000400\n'
                                '/* 0 80000400 03E00008 */ jr $ra\n'
                                '/* 4 80000404 00000000 */ nop\n'
                                'endlabel func_80000400\n')
            fallback = root / 'asm/ovl_7E00/text.s'
            fallback.write_text(fallback.read_text().replace('glabel ', 'dlabel ').replace('endlabel ', 'enddlabel '))
            legacy = {'0x80000400': dict(area='asm/boot.s', function='func_80000400',
                        vram='0x80000400', rom='0x0', bytes=8, handwritten=False)}
            (folder / 'original-functions.json').write_text(json.dumps(legacy))
            status = folder / 'status.csv'
            status.write_text('name_or_vram,tier,note\nboot:0x80000400,excluded,legacy\n'
                              'ovl_7E00:0x80000400,T2,working\n')
            subprocess.run([sys.executable, str(INVENTORY), '--root', str(root)], check=True, capture_output=True)
            rows = list(csv.DictReader((root / 'docs/functions.csv').read_text().splitlines()))
            self.assertEqual({row['area']: row['tier'] for row in rows},
                             {'boot': 'excluded', 'ovl_7DF8': 'T1', 'ovl_7E00': 'T2'})
            self.assertEqual(len(json.loads((folder / 'original-functions.json').read_text())), 3)
            status.write_text('name_or_vram,tier,note\n0x80000400,T2,ambiguous\n')
            result = subprocess.run([sys.executable, str(INVENTORY), '--root', str(root)], capture_output=True, text=True)
            self.assertNotEqual(result.returncode, 0)
            self.assertIn('unknown/ambiguous override', result.stderr)


if __name__ == '__main__':
    unittest.main()
