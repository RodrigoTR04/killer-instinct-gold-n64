#!/usr/bin/env python3
"""Probe 1172 + raw DEFLATE streams without writing extracted ROM assets."""
import hashlib
import json
from pathlib import Path
import zlib

rom = Path(__file__).resolve().parents[2] / 'baserom.us.z64'
data = rom.read_bytes()
results = []
pos = 0
while True:
    pos = data.find(b'\x11\x72', pos)
    if pos < 0:
        break
    decoder = zlib.decompressobj(-15)
    try:
        # Limit input/output to avoid accidental matches allocating unbounded data.
        source = data[pos + 2:pos + 2 + 0x200000]
        output = decoder.decompress(source, 0x800000)
        if decoder.eof and len(output) >= 16:
            results.append(dict(offset=pos, compressed_size=2 + len(source) - len(decoder.unused_data),
                                decompressed_size=len(output), sha1=hashlib.sha1(output).hexdigest()))
    except zlib.error:
        pass
    pos += 2
print(json.dumps(dict(rom_sha1=hashlib.sha1(data).hexdigest(), streams=results), indent=2))
