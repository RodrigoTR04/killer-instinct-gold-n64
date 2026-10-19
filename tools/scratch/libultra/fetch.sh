#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
commit=9921382a68bb0c865e5e45eb594d9c64db59b1af
if [ -f sm64/.pinned-commit ]; then test "$(cat sm64/.pinned-commit)" = "$commit"; exit; fi
mkdir -p sm64
curl -fL "https://codeload.github.com/n64decomp/sm64/tar.gz/$commit" | tar xz --strip-components=1 -C sm64
printf '%s\n' "$commit" > sm64/.pinned-commit
