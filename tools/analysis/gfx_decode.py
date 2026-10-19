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
    row_start = 0
    while p == 255:
        row_start += w
        if row_start >= w*h:
            p = row_start
            break
        p = reader.token()
    else:
        p += row_start
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
            while skip == 255:
                p += w
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



# Callback arguments verified in main; arrays are read from the ROM's main image.
# (call instruction, geometry arguments, texture arguments), in boot-table order.
STAGE_CALLS = [(2147585592,
  [2147769024, 2147769060, 2147769080, 2147769116, 2150495264, 2147769136, 2147769172, 9],
  [2150495324, 2150495264, 2150495384, 15]),
 (2147565612,
  [2147767156, 2147767208, 2147767236, 2147767288, 2150542328, 2147767316, 2147767368, 13],
  [2150542484, 2150542328, 2150542640, 39]),
 (2147583508,
  [2147768944, 2147768960, 2147768968, 2147768984, 2150557928, 2147768992, 2147769008, 4],
  [2150558092, 2150557928, 2150558256, 41]),
 (2147573556,
  [2147767528, 2147767584, 2147767612, 2147767668, 2150530676, 2147767696, 2147767752, 15],
  [2150530796, 2150530676, 2150530916, 30]),
 (2147586464,
  [2147769208, 2147769220, 2147769228, 2147769240, 2150493872, 2147769248, 2147769260, 3],
  [2150493944, 2150493872, 2150494016, 18]),
 (2147564320,
  [2147766816, 2147766880, 2147766912, 2147766976, 2150564512, 2147767008, 2147767072, 16],
  [2150564728, 2150564512, 2150564944, 54]),
 (2147575592,
  [2147767856, 2147767940, 2147767984, 2147768068, 2150534816, 2147768112, 2147768196, 21],
  [2150534952, 2150534816, 2150535088, 34]),
 (2147577528,
  [2147768280, 2147768316, 2147768336, 2147768372, 2150515944, 2147768392, 2147768428, 9],
  [2150516044, 2150515944, 2150516144, 25]),
 (2147580296,
  [2147768464, 2147768512, 2147768536, 2147768584, 2150547372, 2147768608, 2147768656, 12],
  [2150547576, 2150547372, 2150547780, 51]),
 (2147582844,
  [2147768704, 2147768752, 2147768776, 2147768824, 2150535548, 2147768848, 2147768896, 12],
  [2150535688, 2150535548, 2150535828, 35]),
 (2147587788,
  [2147769272, 2147769284, 2147769292, 2147769304, 2150483780, 2147769312, 2147769324, 3],
  [2150483828, 2150483780, 2150483876, 12]),
 (2147588144,
  [2150449152, 84, 2150449496, 116, 2150457496, 2149013648, 2149012976, None],
  [2150457508, 2150457496, 2150457520, 3]),
 (2147575592,
  [2147767856, 2147767940, 2147767984, 2147768068, 2150534816, 2147768112, 2147768196, 21],
  [2150534952, 2150534816, 2150535088, 34])]


def stage_packets(rom, main, outdir, manifest):
    def read(addr, fmt, data=main, base=0x8000f960):
        return struct.unpack_from(fmt, data, addr-base)[0]
    reports = []
    for stage, (call, args, texargs) in enumerate(STAGE_CALLS):
        start, end = struct.unpack_from('>II', rom, 0x7e60+stage*8)
        data = inflate(rom, start, end)
        def packet(addr, fmt):
            return read(addr, fmt, data, 0x802d4000)
        srcarray, dstarray, sizearray, nt = texargs
        textures = []
        for i in range(nt):
            source = packet(srcarray+i*4, '>I')-0x802d4000
            size = packet(sizearray+i*2, '>H')
            textures.append(dict(source=source, type=size>>13, count=size&8191))
        if args[7] is None:
            batches = [args[:7]]
        else:
            batches = [[read(args[0]+i*4, '>I'), read(args[1]+i*2, '>H'),
                        read(args[2]+i*4, '>I'), read(args[3]+i*2, '>H'), args[4],
                        read(args[5]+i*4, '>I'), read(args[6]+i*4, '>I')]
                       for i in range(args[7])]
        vertices, faces, dimensions_by_slot = [], [], {}
        invalid_batches = []
        seed = list(struct.unpack_from('>8h', main, 0x80048290-0x8000f960))
        for source, count, vs, nv, _, _, _ in batches:
            if not (0x802d4000 <= source < 0x802d4000+len(data) and
                    0x802d4000 <= vs < 0x802d4000+len(data)):
                invalid_batches.append([source, count, vs, nv])
                continue
            # 8002FDA0: two-bit XYZ deltas, followed by optional ST/RGBA fields.
            pos = vs-0x802d4000
            previous = seed[:]
            local = []
            for _ in range(nv):
                flags = struct.unpack_from('>H', data, pos)[0]; pos += 2
                v = previous[:]
                for axis in range(3):
                    mode = flags & 3; flags >>= 2
                    if mode in (1, 2):
                        v[axis] -= struct.unpack_from('>b', data, pos)[0]; pos += 1
                    elif mode == 3:
                        delta = struct.unpack_from('>H', data, pos)[0]; pos += 2
                        v[axis] -= delta
                    v[axis] = (v[axis]+32768)%65536-32768
                # Modes 1/2 share the signed-byte branch; mode 3 uses a halfword.
                for field in (4, 5):
                    if flags & 1: v[field] = struct.unpack_from('>h', data, pos)[0]; pos += 2
                    flags >>= 1
                # RGBA bytes do not affect exported positions.
                for field in range(4):
                    if flags & 1: pos += 1
                    flags >>= 1
                local.append(tuple(v[:3])); previous = v
            first = len(vertices); vertices.extend(local)
            pos = source-0x802d4000; cache = 0; slot = None
            for _ in range(count):
                tag = data[pos]; kind = tag & 0xc0
                if kind == 0:
                    w0,w1 = struct.unpack_from('>II', data, pos+1); pos += 9
                    if w0>>24 == 0xf2 and slot is not None:
                        w = ((w1>>12 & 4095)-(w0>>12 & 4095))//4+1
                        h = ((w1 & 4095)-(w0 & 4095))//4+1
                        dimensions_by_slot.setdefault(slot, set()).add((w,h))
                elif kind == 0x40:
                    slot = tag & 63; pos += 4
                elif kind == 0xc0:
                    cache = (tag & 63)*256+data[pos+1]; pos += 3
                else:
                    indices = (tag&15, data[pos+1]>>4, data[pos+1]&15)
                    face = tuple(first+cache+j+1 for j in indices)
                    if all(first < j <= first+nv for j in face): faces.append(face)
                    else: raise ValueError('stage triangle outside vertex batch')
                    pos += 2
        stage_dir = Path('stages')/f'stage_{stage:02d}'
        obj = outdir/stage_dir/'geometry.obj'; obj.parent.mkdir(parents=True, exist_ok=True)
        obj.write_text('# Static local geometry; runtime transforms omitted.\n'+
                       ''.join('v %d %d %d\n'%v for v in vertices)+
                       ''.join('f %d %d %d\n'%f for f in faces))
        for i,t in enumerate(textures):
            dims = sorted(dimensions_by_slot.get(i, []))
            t['tile_dimensions'] = dims
            if t['type'] != 0:
                t['skipped'] = 'context-coded byte texture (8002A40C); not RGBA16'
                continue
            pos = t['source']; values = []
            while len(values) < t['count']:
                a = data[pos]; pos += 1
                if a & 1:
                    distance = ((a>>1)&63)+1
                    if distance > len(values): raise ValueError('texture backreference before start')
                    for _ in range(2 if a&128 else 1): values.append(values[-distance])
                else:
                    c = data[pos]; pos += 1
                    values.append((a<<8)+((c&192)<<1)+(c&63))
            matches = [(w,h) for w,h in dims if w*h == len(values)]
            if not matches:
                t['skipped'] = 'tile dimensions do not match decoded texel count'
                continue
            w,h = matches[0]
            path = stage_dir/f'texture_{i:02d}.png'
            png(outdir/path,w,h,b''.join(rgba5551(v,255 if v&1 else 0) for v in values))
            manifest.append(dict(path=str(path),width=w,height=h,format='stage_rgba16',stage=stage))
            t['path'] = str(path)
        reports.append(dict(stage=stage,table=f'{0x7e60+stage*8:04X}',callback_call=f'{call:08X}',
                            vertices=len(vertices),triangles=len(faces),textures=textures, invalid_batches=invalid_batches))
    return reports


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
    rejected = []
    # Fixed UI palette used explicitly by callers of 800238C4.
    ui_palette = main[0x80047c38-0x8000f960:0x80047d38-0x8000f960+1]
    for ri, (start, record, compressed) in enumerate(records):
        owner = next((i for i, g in enumerate(groups) if g[0] <= start < g[1]), None)
        # Immediate auxiliary containers share their character's Huffman trees.
        # Identified by unique full-frame decode; see T-017 documentation.
        auxiliary = ((0x13200,0x1d640,2),(0x1d640,0x24d60,3),
                     (0x24d60,0x2ecb0,4),(0x49fd0,0x566d0,0),
                     (0x1eb6d0,0x1f3200,1),(0x2c2280,0x2cf0a0,2),
                     (0x469660,0x470390,4),(0x53cc40,0x54d720,5))
        if owner is None:
            owner = next((i for a,b,i in auxiliary if a <= start < b), None)
        if 0x49fd0 <= start < 0x566d0:
            owner = struct.unpack_from('<H', record)[0]  # one record per character
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
                first_error = None
                image_kind = 'huffman_character'
                if owner is not None:
                    group = groups[owner]
                    trees = rom[group[2]:group[2]+0x1000]
                    palette = struct.unpack_from('>16H', rom, group[6])
                    try:
                        w, h, rgba, info = huffman_frame(data, trees, palette)
                    except (ValueError, IndexError, struct.error) as primary:
                        first_error = str(primary)
                        w, h, rgba, info = alpha_frame(data)
                        image_kind = 'alpha_masks'
                else:
                    try:
                        w, h, rgba, info = span_frame(data, ui_palette)
                        image_kind = 'byte_spans'
                    except (ValueError, IndexError, struct.error) as primary:
                        first_error = str(primary)
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
                rejected.append(dict(source_rom=f'{start:06X}', record_id=ident, frame_offset=off, bytes=len(data), primary_reason=first_error, reason=str(error)))
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
    stages = stage_packets(rom, main, outdir, manifest)
    summary['stage_packets'].update(records_total=13, records_decoded=13,
        records_fully_decoded=sum(all('path' in t for t in s['textures']) for s in stages),
        frames_total=sum(len(s['textures']) for s in stages),
        frames_decoded=sum('path' in t for s in stages for t in s['textures']))
    outdir.mkdir(parents=True, exist_ok=True)
    (outdir/'manifest.json').write_text(json.dumps(dict(summary=dict(summary), images=manifest, stages=stages, rejected_frames=rejected), indent=2)+'\n')
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
