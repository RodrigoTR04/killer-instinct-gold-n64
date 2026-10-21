"""Regression coverage for overlapping executable address spaces."""
import csv
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parent))
import progress

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

    def test_renamed_function_safety(self):
        for symbol_table in (True, False):
            for case in ('match', 'asm_old', 'asm_new', 'wrong_address', 'asm_owner', 'unused', 'bad_rom', 'bad_image'):
                with self.subTest(symbol_table=symbol_table, case=case), tempfile.TemporaryDirectory() as directory:
                    root = Path(directory)
                    for folder in ('tools/progress', 'docs', 'src/main', 'build/segments'):
                        (root / folder).mkdir(parents=True, exist_ok=True)
                    row = dict(area='main', function='func_80001000', vram='0x80001000', rom='0x0', bytes=8, handwritten=False)
                    (root / 'tools/progress/original-functions.json').write_text(json.dumps({'main:0x80001000': row}))
                    (root / 'tools/progress/status.csv').write_text('name_or_vram,tier,note\n')
                    if symbol_table:
                        (root / 'symbol_addrs.main.us.txt').write_text('osRenamed = 0x80001000; // type:func\n')
                    source = 'int osRenamed(void) { return 0; }\n'
                    if case.startswith('asm_') and case != 'asm_owner':
                        source += 'GLOBAL_ASM("' + ('func_80001000' if case == 'asm_old' else 'osRenamed') + '.s")\n'
                    (root / 'src/main/test.c').write_text(source)
                    owner = 'build/asm/test.o' if case == 'asm_owner' else 'build/src/main/test.c.o'
                    address = '80001004' if case == 'wrong_address' else '80001000'
                    symbol = 'unusedSymbol' if case == 'unused' else 'osRenamed'
                    (root / 'build/main.map').write_text(f' .text 0x80001000 0x8 {owner}\n 0x{address} {symbol}\n')
                    for path in ('baserom.us.z64', 'build/kig.us.z64', 'build/main.bin', 'build/segments/main.bin'):
                        (root / path).write_bytes(b'match')
                    if case in ('bad_rom', 'bad_image'):
                        (root / ('build/kig.us.z64' if case == 'bad_rom' else 'build/main.bin')).write_bytes(b'bad')
                    (root / 'Makefile').write_text('all:\n\t@true\n')
                    result = subprocess.run([sys.executable, str(INVENTORY), '--root', str(root)], capture_output=True, text=True)
                    if case in ('bad_rom', 'bad_image'):
                        self.assertNotEqual(result.returncode, 0)
                        self.assertIn('does not match', result.stderr)
                    else:
                        self.assertEqual(result.returncode, 0, result.stderr)
                        rows = list(csv.DictReader((root / 'docs/functions.csv').read_text().splitlines()))
                        self.assertEqual(rows[0]['tier'], 'T4' if case == 'match' else 'T1')


class ReadmeProgressTests(unittest.TestCase):
    def test_bar_and_readme_splice(self):
        self.assertEqual(progress.bar(0, 10), '░' * 10)
        self.assertEqual(progress.bar(100, 10), '█' * 10)
        self.assertEqual(progress.bar(50, 10), '█████░░░░░')
        self.assertEqual(progress.bar(None, 4), '░░░░')
        empty = {'bytes': 0, 'functions': 0}
        data = {
            'M1': {'bytes': 50, 'percent': 50.0},
            'M2': {'bytes': 25, 'percent': 25.0},
            'eligible_bytes': 100,
            'eligible_functions': 4,
            'tiers': {'T1': empty, 'T2': {'bytes': 50, 'functions': 2},
                      'T3': {'bytes': 25, 'functions': 1}, 'T4': {'bytes': 25, 'functions': 1},
                      'excluded': empty},
            'areas': {
                'boot': {
                    'M1': {'bytes': 50, 'percent': 50.0},
                    'M2': {'bytes': 25, 'percent': 25.0},
                    'eligible_bytes': 100,
                    'eligible_functions': 4,
                    'tiers': {'T1': empty, 'T2': empty, 'T3': {'bytes': 25, 'functions': 1},
                              'T4': {'bytes': 25, 'functions': 1}, 'excluded': empty},
                },
            },
        }
        block = progress.readme_block(data, '2026-10-21')
        self.assertIn('_Snapshot 2026-10-21._', block)
        self.assertIn('50.0%', block)
        self.assertIn('**boot**', block)
        text = 'before\n<!-- progress-begin -->\nold\n<!-- progress-end -->\nafter\n'
        spliced = progress.splice_readme(text, block)
        self.assertTrue(spliced.startswith('before\n<!-- progress-begin -->\n'))
        self.assertTrue(spliced.endswith('<!-- progress-end -->\nafter\n'))
        self.assertIn('M1  Contract-valid (T3 + T4)', spliced)


if __name__ == '__main__':
    unittest.main()
