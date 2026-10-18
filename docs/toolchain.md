# Sudo-free toolchain

Run from the repository root:

```sh
./tools/setup.sh
export PATH="$PWD/.venv/bin:$PWD/tools/ext/binutils/bin:$PATH"
```

Tested on Linux x86_64 with Python 3.14.8 and GCC 15. Requires Python 3 with
`venv`, git, curl, tar (with xz support), sha256sum, gcc, g++, and GNU make.
No sudo, apt, system package installation, or ROM input is used. Everything
installed is under the gitignored `.venv/` and `tools/ext/` directories.
Run m2c and asm-differ using `.venv/bin/python` and their script paths below.
Select IDO explicitly by path; putting both compiler versions on PATH would
make the selected version ambiguous.

The first binutils build takes several minutes. `JOBS=4` is the default;
set `JOBS=2 ./tools/setup.sh` to reduce parallelism. Build logs are in
`tools/ext/binutils-build/{configure,build,install}.log`. Later runs reuse the
completed binutils build, verify cached download checksums, reinstall the
pinned Python requirements if needed, and check out the pinned tool commits.
The script refuses to overwrite changes in tool source checkouts. Remove the
binutils `.setup-2.43.1-mips64-elf` marker to force configure/build/install again.

## Exact inputs

All Python dependencies, including transitives, are pinned in
[`requirements.txt`](../requirements.txt). Main versions:

- splat64[mips] 0.50.1, spimdisasm 1.42.4, rabbitizer 1.16.2.
- pycparser 3.11, graphviz 0.20.3, colorama 0.4.6, ansiwrap 0.8.4,
  watchdog 6.0.0, python-Levenshtein/Levenshtein 0.27.5, cxxfilt 0.3.0.
- pip 26.2. Bootstrap script pinned to pypa/get-pip commit
  `af54dfe793b24685f8dc4ebba0630d9f2d77653c` and SHA256 in setup.sh.

Source checkouts:

- [m2c](https://github.com/matt-kempster/m2c):
  `708d2d2cb2698f091a92492b328f73b24209f72d`.
- [asm-differ](https://github.com/simonlindholm/asm-differ):
  `0dd09af8f8008f1f880327cf0aca3b26d2562ea2`.
- [ido-static-recomp](https://github.com/decompals/ido-static-recomp):
  `d5aec59932034b8a20f23f471297a55c45dcbc45`.

Binary/compiler and binutils inputs (SHA256 verified by setup.sh):

- [IDO release v1.2](https://github.com/decompals/ido-static-recomp/releases/tag/v1.2),
  `ido-5.3-recomp-linux.tar.gz` and `ido-7.1-recomp-linux.tar.gz`, extracted into
  `tools/ext/ido/5.3` and `tools/ext/ido/7.1`. The source checkout is retained
  separately; setup uses the release binaries, not a build of that checkout.
- [GNU binutils 2.43.1 source](https://ftp.gnu.org/gnu/binutils/binutils-2.43.1.tar.xz),
  configured with `CFLAGS="-O2 -std=gnu17" --target=mips64-elf --disable-nls --disable-werror
  --disable-gdb --disable-gprofng --disable-sim` and a repository-local prefix.
  Installed programs include `mips64-elf-{as,ld,objdump,objcopy}` in
  `tools/ext/binutils/bin`. Use `-EB -mips2` for N64 assembly and
  `-m elf32ebmip` for linking 32-bit big-endian objects.
  `MAKEINFO=true` skips regenerating manuals, avoiding a texinfo prerequisite.

## Verification

Actual verification on 2026-10-18 (output abbreviated):

```sh
.venv/bin/python -c 'import splat, spimdisasm, rabbitizer; print("Python tool imports: OK")'
# Python tool imports: OK
.venv/bin/python -m pip check
# No broken requirements found.
.venv/bin/python tools/ext/m2c/m2c.py --help
# usage: m2c.py [-t mips-ido-c] [--context C_FILE] [-f FN ...] filename [filename ...]
# Decompile assembly to C.
.venv/bin/python tools/ext/asm-differ/diff.py --help
# usage: diff.py [-h] [-o] [-f FILE] [-F REF_FILE] ...
printf 'int f(int a){return a+1;}\n' > tools/ext/smoke.c
tools/ext/ido/5.3/cc -O2 -mips2 -c tools/ext/smoke.c -o tools/ext/smoke53.o
tools/ext/ido/7.1/cc -O2 -mips2 -c tools/ext/smoke.c -o tools/ext/smoke71.o
# Both exit 0 without diagnostics.
file tools/ext/smoke53.o tools/ext/smoke71.o
# Both: ELF 32-bit MSB relocatable, MIPS, MIPS-II version 1 (SYSV), not stripped
```

## Workarounds and limits

The initial `python3 -m venv .venv` failed because this machine lacks
`ensurepip`. Setup uses `venv --without-pip` plus the checksum-verified pinned
get-pip script; no system Python packages are changed. All pinned Python
requirements installed successfully on Python 3.14.8; `pip check`, m2c help,
and asm-differ help passed. m2c bundles its own parser; installing pycparser
alone is not a replacement for that checkout.

A decompals PS2 binutils prebuilt was inspected during investigation but is
not used by setup. GNU source was selected to provide the requested
`mips64-elf` target directly without distro shared-library dependencies.
The Python graphviz package does not install the native `dot` renderer;
m2c's optional rendered graph output requires a separately available `dot`.
No matching-ROM build or game execution is claimed by these smoke tests.

The first binutils attempt failed in `opcodes/mips-formats.h` because GCC 15
defaults to C23 (`static_assert` conflict). Setup explicitly selects GNU C17.
Changing CFLAGS in that already configured build then hit configure cache
checks; the failed build directory was moved aside and a fresh build used.
If changing build flags later, use a fresh `tools/ext/binutils-build/`.

IDO `cc -v` without an input exits 2 with `no source, object or ucode file
specified`; the actual compile smoke tests above are used instead.

Final setup completed successfully; a second `./tools/setup.sh` run also exited
0 and reused the binutils build. The first successful run log is
`tools/ext/setup-first.log`; the repeat log is `tools/ext/setup-second.log`.

```sh
tools/ext/binutils/bin/mips64-elf-objdump --version
# GNU objdump (GNU Binutils) 2.43.1
tools/ext/binutils/bin/mips64-elf-objdump -dr tools/ext/smoke53.o tools/ext/smoke71.o
# Both: file format elf32-bigmips
# 00000000 <f>:
#    0: 03e00008  jr     ra
#    4: 24820001  addiu  v0,a0,1
printf '.set noreorder\n.text\n.globl g\ng:\n jr $ra\n addiu $v0,$a0,1\n' > tools/ext/smoke.s
tools/ext/binutils/bin/mips64-elf-as -EB -mips2 -o tools/ext/smoke-as.o tools/ext/smoke.s
tools/ext/binutils/bin/mips64-elf-ld -m elf32ebmip -e g -Ttext 0x80000400 -o tools/ext/smoke.elf tools/ext/smoke-as.o
tools/ext/binutils/bin/mips64-elf-objcopy -j .text -O binary tools/ext/smoke.elf tools/ext/smoke.bin
# All exit 0. Linked g is at 0x80000400 with jr ra / addiu v0,a0,1.
```

An initial linker smoke command used `-m elf32btsmip` and failed with
`unrecognised emulation mode`; this target's supported emulation is
`elf32ebmip`, verified above. The dependent objcopy attempt consequently also
failed before being rerun successfully with the corrected link output.

Exporting every section from that minimal linked ELF produced `file truncated`
because metadata and text had widely separated addresses. The verified
objcopy command selects `.text`; a real ROM link will need a project linker
script defining all section addresses.
