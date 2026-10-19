"""asm-differ configuration for independently linked executable images."""
import os


def apply(config, args):
    image = os.environ.get("KIG_IMAGE", "main")
    bases = {"main": 0x8000F960, "ovl_7DF8": 0x801ABB20,
             "ovl_7E00": 0x801AD900}
    if image not in bases:
        raise ValueError("KIG_IMAGE must be main, ovl_7DF8, or ovl_7E00")
    config.update(baseimg=f"build/segments/{image}.bin",
                  myimg=f"build/{image}.bin", mapfile=f"build/{image}.map",
                  source_directories=["src", "include"], arch="mips",
                  map_format="gnu", build_dir="build/",
                  objdump_executable="tools/ext/binutils/bin/mips64-elf-objdump")
    # GNU map load addresses already translate VRAM into image offsets.
    config["map_address_offset"] = 0
