# usage: score.py <obj> <func> <img_off_hex> : count differing words (jal targets masked)
import sys, subprocess, struct, re
import os
TXT = "/tmp/t037_text_%d.bin" % os.getpid()
obj, fn, off = sys.argv[1], sys.argv[2], int(sys.argv[3], 16)
out = subprocess.run(["tools/ext/binutils/bin/mips64-elf-nm", "-S", obj], capture_output=True, text=True).stdout
for l in out.split("\n"):
    p = l.split()
    if len(p) == 4 and p[3] == fn:
        a, sz = int(p[0], 16), int(p[1], 16)
subprocess.run(["tools/ext/binutils/bin/mips64-elf-objcopy", "-O", "binary", "-j", ".text", obj, TXT])
mine = open(TXT, "rb").read()[a:a+sz]
base = open("build/segments/main.bin", "rb").read()[off:off+sz]
d = 0
for i in range(0, sz, 4):
    x, y = struct.unpack(">I", mine[i:i+4])[0], struct.unpack(">I", base[i:i+4])[0]
    if x >> 26 == 3: x &= 0xfc000000; y &= 0xfc000000
    d += x != y
os.remove(TXT)
print(d, "sizes", sz)
if len(sys.argv) > 4:
    import os
    open("/tmp/t037_a.bin","wb").write(mine); open("/tmp/t037_b.bin","wb").write(base)
    dis = lambda f: [l.split("\t",2)[-1] for l in subprocess.run(["tools/ext/binutils/bin/mips64-elf-objdump","-D","-b","binary","-m","mips:4300","-EB","-Mreg-names=32",f],capture_output=True,text=True).stdout.split("\n") if re.match(r"\s+[0-9a-f]+:\t", l)]
    import re
    A, B = dis("/tmp/t037_a.bin"), dis("/tmp/t037_b.bin")
    for i in range(max(len(A), len(B))):
        a = A[i] if i < len(A) else ""; b = B[i] if i < len(B) else ""
        print(f"{i*4:4x} {'  ' if a==b else '**'} {a:40s} {b}")
