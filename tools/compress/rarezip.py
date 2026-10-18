#!/usr/bin/env python3
"""Byte-exact KI Gold 1172 compressor using pinned GoldenEye gzip 1.2.4."""
import argparse
import hashlib
import io
import os
from pathlib import Path
import subprocess
import tarfile
import urllib.request

REVISION = 'c4356466796c697dfd298010b9bed261f9ed8c6a'
URL = f'https://codeload.github.com/n64decomp/007/tar.gz/{REVISION}'
SHA256 = '26bf36f41e465616ee3d5df0e4767c7215200f93cd68a27765354f62e724858e'
DEFAULT_CACHE = Path('/tmp/kig-t008') / ('gzip-' + REVISION)


def build(cache=DEFAULT_CACHE):
    """Fetch hash-verified source and build outside the repository (requires cc)."""
    cache = Path(cache)
    binary = cache / 'gzip'
    if binary.is_file():
        return binary
    cache.mkdir(parents=True, exist_ok=True)
    archive = urllib.request.urlopen(URL).read()
    if hashlib.sha256(archive).hexdigest() != SHA256:
        raise RuntimeError('gzip source archive SHA256 mismatch')
    prefix = f'007-{REVISION}/tools/gzipsrc/'
    with tarfile.open(fileobj=io.BytesIO(archive), mode='r:gz') as tar:
        for member in tar.getmembers():
            if member.name.startswith(prefix) and member.isfile():
                name = member.name[len(prefix):]
                if '/' not in name and name:
                    (cache / name).write_bytes(tar.extractfile(member).read())
    # GNU89 keeps this 1993 K&R source buildable on modern GCC (including GCC 15).
    sources = sorted(str(p) for p in cache.glob('*.c'))
    subprocess.run([os.environ.get('CC', 'cc'), '-std=gnu89', '-O2',
                    '-DSTDC_HEADERS=1', '-DHAVE_UNISTD_H=1', '-DDIRENT=1',
                    *sources, '-o', str(binary)], check=True)
    return binary


def compress(data: bytes, *, binary=None) -> bytes:
    """Return 1172 + raw DEFLATE, with no ROM alignment padding."""
    executable = Path(binary) if binary else build()
    env = dict(os.environ)
    env.pop('GZIP', None)  # User defaults must not alter the reproducible invocation.
    result = subprocess.run([str(executable), '-n', '-9', '-c'], input=data,
                            stdout=subprocess.PIPE, check=True, env=env).stdout
    if result[:4] != b'\x1f\x8b\x08\x00':
        raise RuntimeError('unexpected gzip header')
    return b'\x11\x72' + result[10:-8]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('input', type=Path)
    parser.add_argument('output', type=Path)
    parser.add_argument('--binary', type=Path)
    args = parser.parse_args()
    args.output.write_bytes(compress(args.input.read_bytes(), binary=args.binary))


if __name__ == '__main__':
    main()
