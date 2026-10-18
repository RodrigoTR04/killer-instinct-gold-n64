#!/usr/bin/env python3
"""Decode verified KIG US 1.0 graphics; ROM and inventory are read-only.
See docs/gfx_format.md for supported formats and explicit limitations.
"""
import argparse
import collections
import csv
import hashlib
import json
from pathlib import Path
import struct
import zlib

SHA1 = 'ba52e91b44450c548467044b26951353dc491e04'


def png(path, width, height, rgba):
    """Write an RGBA PNG using only the Python standard library."""
    def chunk(kind, data):
        return (struct.pack('>I', len(data)) + kind + data
                + struct.pack('>I', zlib.crc32(kind + data) & 0xffffffff))
    assert len(rgba) == width * height * 4
    rows = b''.join(b'\0' + rgba[y*width*4:(y+1)*width*4] for y in range(height))
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(b'\x89PNG\r\n\x1a\n'
                     + chunk(b'IHDR', struct.pack('>IIBBBBB', width, height, 8, 6, 0, 0, 0))
                     + chunk(b'IDAT', zlib.compress(rows, 9)) + chunk(b'IEND', b''))


def rgba5551(value, alpha=255):
    return bytes((((value >> 11) & 31)*255//31,
                  ((value >> 6) & 31)*255//31,
                  ((value >> 1) & 31)*255//31, alpha))


class Huffman:
    """Shared MSB-first bit reader; context trees and control tree are distinct."""
    def __init__(self, data, trees):
        self.data, self.trees, self.bitpos, self.context = data, trees, 64, 0

    def bit(self):
        p = self.bitpos
        self.bitpos += 1
        return (self.data[p//8] >> (7-p % 8)) & 1

    def token(self):
        p = 0x800
        for _ in range(64):
            flag = self.trees[p]
            if not flag:
                return self.trees[p+1]
            branch = self.bit()
            high = (flag & 0x1c) << 6 if branch else (flag >> 5) << 8
            p += 3 * (self.trees[p+1+branch] + high)
        raise ValueError('control tree cycle')

    def color(self):
        p = self.context * 128
        for _ in range(64):
            if not self.trees[p]:
                self.context = self.trees[p+1]
                if self.context > 15:
                    raise ValueError('color outside 16-entry palette')
                return self.context
            p += 3*self.trees[p+1+self.bit()]
        raise ValueError('color tree cycle')


def dimensions(data):
    x, y, w, h = struct.unpack_from('<hhHH', data)
    if not (0 < w <= 1024 and 0 < h <= 1024):
        raise ValueError('invalid dimensions')
    return x, y, w, h


def huffman_frame(data, trees, palette):
    """Decode logical interior, omitting the runtime's duplicated border texels."""
    x, y, w, h = dimensions(data)
    reader = Huffman(data, trees)
    out = bytearray(w*h*4)
    p = reader.token()
    if p == 0xf3:  # Initial extended offset has a different escape from later skips.
        p = 254 + reader.token()
    while p == 255 and p < w*h:
        p = w + reader.token()
    for _ in range(w*h+1):
        if p >= w*h:
            break
        coverage, count = reader.token(), reader.token()
        if count == 0 or p % w + count > w:
            raise ValueError('span outside row')
        reader.context = 0
        for _ in range(count):
            out[p*4:p*4+4] = rgba5551(palette[reader.color()])
            p += 1
        skip = reader.token()
        if skip == 254:
            skip = 254 + reader.token()
        elif skip == 255:
            # End row. Runtime also emits duplicated edge pixels with coverage.
            p = ((p+w-1)//w)*w
            if p >= w*h:
                break
            skip = reader.token()
            if skip == 254:
                skip += reader.token()
        p += skip
    else:
        raise ValueError('too many spans')
    # Alignment permits up to three pad bytes, never arbitrary unread payload.
    used = (reader.bitpos+7)//8
    if len(data)-used > 3:
        raise ValueError(f'unconsumed frame bytes: {len(data)-used}')
    return w, h, out, dict(origin=[x, y], bits=reader.bitpos,
                           rendering='opaque interior; edge coverage omitted')


def span_frame(data, palette):
    """800238C4 byte-span format, palette addressed by BYTE offset."""
    x, y, w, h = dimensions(data)
    out = bytearray(w*h*4)
    pos = 8
    def put(px, py, offset, alpha):
        if 0 <= px < w:
            value = struct.unpack_from('<H', palette, offset)[0]
            out[(py*w+px)*4:(py*w+px+1)*4] = rgba5551(value, alpha)
    for row in range(h):
        end = pos + data[pos]
        pos += 1
        px = 0
        if end < pos or end > len(data):
            raise ValueError('invalid row size')
        while pos < end:
            coverage, skip, count = data[pos:pos+3]
            pos += 3
            px += skip
            if px+count > w or pos+count > end or count == 0:
                raise ValueError('invalid byte span')
            put(px-1, row, data[pos], ((coverage & 7)*32))
            last = data[pos]
            for _ in range(count):
                last = data[pos]
                put(px, row, last, 255)
                px += 1
                pos += 1
            put(px, row, last, (coverage & 0x38)*4)
        if pos != end:
            raise ValueError('row overrun')
    if len(data)-pos > 3:
        raise ValueError('unconsumed byte-span data')
    return w, h, out, dict(origin=[x, y], bytes=pos)


def alpha_frame(data):
    """80031A38: row-bounded nibble alpha runs and signed adjacent pairs."""
    x, y, w, h = dimensions(data)
    out = bytearray(w*h*4)
    pos = 8
    for row in range(h):
        end = pos + data[pos]
        pos += 1
        if not pos <= end <= len(data):
            raise ValueError('invalid mask row')
        if pos == end:
            continue
        px = data[pos]
        pos += 1
        while pos < end:
            code = data[pos]
            pos += 1
            if not code:
                px += data[pos]
                pos += 1
                continue
            values = []
            value, low = code >> 4, code & 7
            if code & 8:
                delta = low+1 if low < 4 else -(low & 3)-1
                other = value+delta
                if not 0 <= other <= 15:
                    raise ValueError('mask pair outside nibble range')
                values = [value, other]
            else:
                count = low
                if not count:
                    count = data[pos]
                    pos += 1
                if not count:
                    raise ValueError('empty mask run')
                values = [value]*count
            if px+len(values) > w:
                raise ValueError('mask outside row')
            for alpha in values:
                out[(row*w+px)*4:(row*w+px+1)*4] = bytes((255, 255, 255, alpha*17))
                px += 1
        if pos != end:
            raise ValueError('mask row overrun')
    if len(data)-pos > 3:
        raise ValueError('unconsumed mask bytes')
    return w, h, out, dict(origin=[x, y], bytes=pos, rendering='alpha mask, white RGB')


def frames(record):
    ident, count, size = struct.unpack_from('<HHI', record)
    if size != len(record) or count > 1024 or 8+4*count > size:
        raise ValueError('bad record header')
    offsets = struct.unpack_from('<'+'I'*count, record, 8)
    valid = sorted(set(o for o in offsets if 8+4*count <= o < size))
    for i, off in enumerate(valid):
        end = valid[i+1] if i+1 < len(valid) else size
        yield ident, off, record[off:end]


def inflate(rom, start, end):
    if rom[start:start+2] != b'\x11\x72':
        raise ValueError('bad 1172 magic')
    return zlib.decompress(rom[start+2:end], -15)


def decode(rom, outdir):
    main_start, main_end = struct.unpack_from('>II', rom, 0x7df0)
    main = inflate(rom, main_start, main_end)
    overlay_start, overlay_end = struct.unpack_from('>II', rom, 0x7df8)
    overlay = inflate(rom, overlay_start, overlay_end)
    groups = []
    for i in range(14):
        vals = struct.unpack_from('>8I', main, 0x80045e50-0x8000f960+i*32)
        groups.append(vals)
    rows = list(csv.DictReader((Path(__file__).parent/'data/assets.csv').open()))
    records = [(int(r['start'], 16), rom[int(r['start'], 16):int(r['end'], 16)], False)
               for r in rows if r['classification'] == 'graphics_record']
    # Eleven compressed character containers have no raw graphics_record CSV rows.
    for r in rows:
        if r['depth'] == '1' and r['compressed'] == 'y':
            start, end = int(r['start'], 16), int(r['end'], 16)
            if 0x8e6230 <= start < 0x8f9fa0:
                blob = inflate(rom, start+4, end)
                pos = 0
                while pos+8 <= len(blob):
                    size = struct.unpack_from('<I', blob, pos+4)[0]
                    if size < 8 or pos+size > len(blob):
                        break
                    records.append((start, blob[pos:pos+size], True))
                    pos += size
    summary = collections.defaultdict(collections.Counter)
    manifest = []
    # Fixed UI palette used explicitly by callers of 800238C4.
    ui_palette = main[0x80047c38-0x8000f960:0x80047d38-0x8000f960+1]
    for ri, (start, record, compressed) in enumerate(records):
        owner = next((i for i, g in enumerate(groups) if g[0] <= start < g[1]), None)
        kind = 'character_containers' if owner is not None else 'other_containers'
        stats = summary[kind]
        stats['records_total'] += 1
        success = failures = 0
        try:
            candidates = list(frames(record))
        except (ValueError, struct.error):
            candidates = []
        for ident, off, data in candidates:
            stats['frames_total'] += 1
            try:
                image_kind = 'huffman_character'
                if owner is not None:
                    group = groups[owner]
                    trees = rom[group[2]:group[2]+0x1000]
                    palette = struct.unpack_from('>16H', rom, group[6])
                    try:
                        w, h, rgba, info = huffman_frame(data, trees, palette)
                    except (ValueError, IndexError, struct.error):
                        w, h, rgba, info = alpha_frame(data)
                        image_kind = 'alpha_masks'
                else:
                    try:
                        w, h, rgba, info = span_frame(data, ui_palette)
                        image_kind = 'byte_spans'
                    except (ValueError, IndexError, struct.error):
                        w, h, rgba, info = alpha_frame(data)
                        image_kind = 'alpha_masks'
                path = Path(image_kind)/f'{start:06X}_{ri:04d}_id{ident:03d}_{off:05X}.png'
                png(outdir/path, w, h, rgba)
                manifest.append(dict(path=str(path), source_rom=f'{start:06X}',
                                     record_id=ident, frame_offset=off, width=w, format=image_kind,
                                     height=h, group=owner, compressed=compressed, **info))
                success += 1
                stats['frames_decoded'] += 1
            except (ValueError, IndexError, struct.error) as error:
                failures += 1
                stats['frames_failed'] += 1
        if success:
            stats['records_decoded'] += 1
        if success and not failures:
            stats['records_fully_decoded'] += 1
    for i in range(10):
        start, end = struct.unpack_from('>II', overlay, 0x80291fe8-0x801abb20+i*8)
        data = inflate(rom, start, end)
        if len(data) != 0x9900:
            raise ValueError('unexpected portrait size')
        palette = [rgba5551(((data[j] & 0xf8) << 8)
                           | ((data[j+1] & 0xf8) << 3)
                           | ((data[j+2] & 0xf8) >> 2) | 1)
                   for j in range(0, 0x300, 3)]
        path = Path('portraits')/f'portrait_{i:02d}_{start:06X}.png'
        png(outdir/path, 256, 150, b''.join(palette[v] for v in data[0x300:]))
        manifest.append(dict(path=str(path), source_rom=f'{start:06X}', width=256,
                             height=150, format='CI8 with RGB888 palette'))
    summary['portraits'].update(records_total=10, records_decoded=10,
                                records_fully_decoded=10, frames_total=10, frames_decoded=10)
    summary['stage_packets'].update(records_total=13, records_decoded=0)
    outdir.mkdir(parents=True, exist_ok=True)
    (outdir/'manifest.json').write_text(json.dumps(dict(summary=dict(summary), images=manifest), indent=2)+'\n')
    for kind, stats in summary.items():
        print(f"{kind}: records {stats['records_decoded']}/{stats['records_total']} "
              f"({stats['records_fully_decoded']} complete); "
              f"frames {stats['frames_decoded']}/{stats['frames_total']}")
    print('Image classes:', dict(collections.Counter(m.get('format') for m in manifest)))
    print(f'{len(manifest)} PNGs; manifest: {outdir / "manifest.json"}')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('rom', type=Path)
    parser.add_argument('--out', type=Path, default=Path('build/gfx'))
    args = parser.parse_args()
    rom = args.rom.read_bytes()
    if hashlib.sha1(rom).hexdigest() != SHA1:
        parser.error('expected verified US V1.0 big-endian ROM')
    decode(rom, args.out)


if __name__ == '__main__':
    main()
