#!/usr/bin/env python3
"""Validate Rare 1172/raw-DEFLATE streams in memory; never writes files."""
import sys,re,zlib,hashlib,struct
b=open(sys.argv[1],'rb').read()
for m in re.finditer(b'\x11\x72',b):
 o=m.start();d=zlib.decompressobj(-15)
 try:out=d.decompress(b[o+2:],8*1024*1024)
 except zlib.error:continue
 if not d.eof:continue
 end=len(b)-len(d.unused_data)
 print(f'{o:08X}-{end:08X} packed={end-o:X} unpacked={len(out):X} sha1={hashlib.sha1(out).hexdigest()}')
 for s in re.finditer(rb'[ -~]{8,}',out):
  if re.search(rb'(Version|Copyright|ERROR|\.c\x00|libultra)',s.group()):print(f'  +{s.start():06X} {s.group()[:180]!r}')
print('ROM pair table @ 0x7DF0 (VRAM 0x800071F0):')
for o in range(0x7df0,0x7ec8,8):
 a,z=struct.unpack_from('>II',b,o);print(f'{o:06X}: {a:08X} {z:08X} size={z-a:X}')
