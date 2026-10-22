#!/usr/bin/env bash
set -euo pipefail
ROOT=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)
cd "$ROOT"
EXT="$ROOT/tools/ext"
mkdir -p "$EXT"
[[ $(uname -s) == Linux && $(uname -m) == x86_64 ]] || { echo 'Requires Linux x86_64' >&2; exit 1; }
for tool in python3 git curl tar sha256sum gcc g++ make; do
    command -v "$tool" >/dev/null || { echo "Missing prerequisite: $tool" >&2; exit 1; }
done

# Cache only complete, checksum-verified downloads; never run an unverified payload.
download() {
    local url=$1 file=$2 digest=$3
    if [[ ! -f $file ]] || ! echo "$digest  $file" | sha256sum -c - >/dev/null 2>&1; then
        curl --fail --location --retry 3 "$url" -o "$file.part"
        echo "$digest  $file.part" | sha256sum -c -
        mv -- "$file.part" "$file"
    fi
}

# --without-pip also works on Ubuntu installations lacking python3.14-venv/ensurepip.
python3 -m venv --without-pip .venv
if ! .venv/bin/python -m pip --version >/dev/null 2>&1; then
    download https://raw.githubusercontent.com/pypa/get-pip/af54dfe793b24685f8dc4ebba0630d9f2d77653c/public/get-pip.py "$EXT/get-pip.py" fb24e693bab954209a063d90953621412ccad4a500905a726286e038f508ddf6
    .venv/bin/python "$EXT/get-pip.py" 'pip==26.2'
fi
.venv/bin/python -m pip install 'pip==26.2'
.venv/bin/python -m pip install -r requirements.txt
.venv/bin/python -m pip check

checkout() {
    local name=$1 url=$2 revision=$3
    local fresh=
    if [[ ! -d $EXT/$name ]]; then
        git clone --no-checkout "$url" "$EXT/$name"
        fresh=1
    fi
    # A --no-checkout clone reports every file as deleted; only guard existing checkouts.
    if [[ -z $fresh && -n $(git -C "$EXT/$name" status --porcelain) ]]; then
        echo "Refusing to overwrite local changes in $EXT/$name" >&2; exit 1
    fi
    if ! git -C "$EXT/$name" cat-file -e "$revision^{commit}" 2>/dev/null; then
        git -C "$EXT/$name" fetch origin "$revision"
    fi
    git -C "$EXT/$name" checkout --detach "$revision"
}
checkout m2c https://github.com/matt-kempster/m2c 708d2d2cb2698f091a92492b328f73b24209f72d
checkout asm-differ https://github.com/simonlindholm/asm-differ 0dd09af8f8008f1f880327cf0aca3b26d2562ea2
checkout ido-static-recomp https://github.com/decompals/ido-static-recomp d5aec59932034b8a20f23f471297a55c45dcbc45

for version in 5.3 7.1; do
    case $version in
        5.3) digest=ab5c741561f80913d58c8b074771f23941a3edd312505a8ebed6d1dfeb65e506; archive="$EXT/ido53.tar.gz" ;;
        7.1) digest=0d411696e178fcca34c31c3bf02011b928d7fd9c1fa7f8bf45070e0781b58e15; archive="$EXT/ido71.tar.gz" ;;
    esac
    download "https://github.com/decompals/ido-static-recomp/releases/download/v1.2/ido-$version-recomp-linux.tar.gz" "$archive" "$digest"
    mkdir -p "$EXT/ido/$version"
    tar xzf "$archive" -C "$EXT/ido/$version"
done

# Build the exact GNU release locally, avoiding distro package/shared-library dependencies.
download https://ftp.gnu.org/gnu/binutils/binutils-2.43.1.tar.xz "$EXT/binutils-2.43.1.tar.xz" 13f74202a3c4c51118b797a39ea4200d3f6cfbe224da6d1d95bb938480132dfd
if [[ ! -f $EXT/binutils/.setup-2.43.1-mips64-elf ]]; then
    [[ -d $EXT/binutils-2.43.1 ]] || tar xf "$EXT/binutils-2.43.1.tar.xz" -C "$EXT"
    mkdir -p "$EXT/binutils-build"
    (
        cd "$EXT/binutils-build"
        ../binutils-2.43.1/configure --target=mips64-elf --prefix="$EXT/binutils" CFLAGS="-O2 -std=gnu17" \
            --disable-nls --disable-werror --disable-gdb --disable-gprofng --disable-sim > configure.log 2>&1
        make -j"${JOBS:-4}" MAKEINFO=true > build.log 2>&1
        make install MAKEINFO=true > install.log 2>&1
    ) || { echo "Binutils build failed; inspect $EXT/binutils-build/*.log" >&2; exit 1; }
    touch "$EXT/binutils/.setup-2.43.1-mips64-elf"
fi
for tool in as ld objdump objcopy; do
    "$EXT/binutils/bin/mips64-elf-$tool" --version | sed -n '1p'
done
.venv/bin/python -c 'import splat, spimdisasm, rabbitizer; print("Python tool imports: OK")'
printf '\nSetup complete. For this shell:\nexport PATH="%s/.venv/bin:%s/tools/ext/binutils/bin:$PATH"\n' "$ROOT" "$ROOT"
printf 'IDO compilers: %s/tools/ext/ido/{5.3,7.1}/cc\n' "$ROOT"

# Prepare the pinned matching compressor so subsequent builds work offline.
.venv/bin/python -c 'from tools.compress.rarezip import build; print("Matching gzip:", build())'

# IDO GLOBAL_ASM preprocessing/postprocessing (Python implementation).
checkout asm-processor https://github.com/simonlindholm/asm-processor f3b2f85a5bc7e8ae2030ea5a83ea8aa0bcbede03
