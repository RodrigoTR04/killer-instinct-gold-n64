# SDK audio declarations

These scoped headers come from n64decomp/libreultra revision
`1aca5c13ca041cef86f8dc194b727361dad9c09b` (`include/2.0I/PR` and
`src/audio`). They are used only by the reconstructed libaudio units.

`libaudio.h` uses this project's scalar types and the audio command header
instead of importing the graphics/OS header tree. `abi.h` includes the two
bitfield macros normally supplied by `mbi.h`. TRUE/FALSE are release SDK
constants. `alFxNew` maps to the existing `func_8003EF90` symbol; FU-15
symbol renaming remains deferred. Other original SDK layouts and declarations
are retained. See T-078/REPORT.md for source-version adaptations and flags.
