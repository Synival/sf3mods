# sf3mods

Shining Force III Mod Toolchain

This project is a template for creating C-based mods for Shining Force III. It contains several example mods and a slightly modified version of [Kentosama's sh2-elf-gcc](https://github.com/kentosama/sh2-elf-gcc) project to fetch and compile GCC 16.1.0 for C23 support.

It has some headers and linker scripts for Shining Force III structs, functions, and variables in the `lib/sf3` directory. This "library" is shared across all mods. It is currently very incomplete but it's a decent foundation and will be expanded upon later!

Mods can ultimately be compiled as standalone `.BIN` files or as `.DFR` files. To generate `.DFR` files from compiled source, `.DFR.in` files can be supplied to insert modified data directly from the compiled `.elf` file with a specific section name at an offset in the original file. (For more information, see the section [DFR.IN Files](#dfrin-files).)

## Building (Ubuntu-only):

1. Install SH2 toolchain build dependencies:
  - `sudo apt update && sudo apt install -y build-essential texinfo`

2. Fetch and compile the SH2 toolchain (locally):
  - `./download_and_build_toolchain.sh`

3. Copy Shining Force III disc files to the following places (or create symbolic links):
  - `game-files/scn1`
  - `game-files/scn2` (version 2.000)
  - `game-files/scn3`
  - `game-files/pd`

4. Compile
  - `make`

Files will be outputted to the following directories:

- `build/<mod>/<scenario>/<obj>`: Compiled `.c.o` and `.S.o` objects from C and ASM code
- `build/<mod>/<scenario>/<elf>`: Linked `.elf` files from compiled objects
- `build/<mod>/<scenario>/<bin>`: Dumps of `.bin` files from linked `.elf` files
- `build/<mod>/<scenario>/<dfr>`: Generated `.DFR` files from `.DFR.in` files

## Mod Structure

Mods are contained in the `mods/` directory and organized like so:

- `mods/<mod>/src/*.c, *.S`: Source code in C and ASM. Applicable to all scenarios.
- `mods/<mod>/<scenario>/ld/*.ld`: Linker scripts for generating `.elf` files
- `mods/<mod>/<scenario>/dfr/*.DFR.in`: Input DFR files with hooks for loading binary data from `.elf` files (For more information, see the section [DFR.IN Files](#dfrin-files).)

All build targets and dependencies are set up automatically in the `Makefile` with one exception: input files must be manually specified for each linker target.

In the large `Mods` section of the `Makefile`, you can specify linker inputs like so:

```
# All scenarios:
myModName_OBJS_myLinkTarget      = file1.c.o file2.c.o file3.c.o [...]

# Additional inputs for specific scenarios:
myModName_OBJS_myLinkTarget_scn1 = additional_scn1_file1.c.o [...]
myModName_OBJS_myLinkTarget_scn2 = additional_scn2_file1.c.o [...]
[...]
```

If you only have one link target, you can supply the variable `$(MOD_SCN_OBJS)` for convenience:

```
# Just use all the objects we've build!
myModName_OBJS_myLinkTarget = $(MOD_SCN_OBJS)
```

## DFR.in Files

Here is an excerpt from `X014.BIN.DFR.in` in the `modernizedCamera` mod:

```
; Jump to new code at the end of bcmd0x1b()
; (placed after smaller getScreenDistForPolyCharAttacker())
{ elf=x014.elf section=.replaceEndOfBCmd0x1b offset=0x02b68 length=0x014 }

; Replace getScreenDistForPolyCharAttacker() with smaller version and some new
; code used at the end of bcmd_0x1b().
{ elf=x014.elf section=.replaceGetScreenDistForAttack offset=0x05628 length=0x094 }

; New code in place of old camera functions, which aren't used anymore.
{ elf=x014.elf section=.replaceOldCameraFuncs offset=0x057b0 length=0x3e4 }

; New code for cameraAssign() and all remaining new code we need.
; (this is placed in space freed for use by "Mod Essentials")
; (code below starts with new cameraAssign() function)
{ elf=x014.elf section=.codeAndDataInFreedUpMemoryBlock offset=0x11ea0 max_length=0x784 replace_zeroes }
```

When the `.DFR` is compiled from the `.DFR.in` file (using a custom tool called `dfrc`), the lines in brackets (called "actions") are replaced with content from the referenced `.elf` file. When compiling, the `.elf` files for your mod should be located in the `build/<mod>/<scenario>/elf` directory.

The following parameters for `.DFR.in` actions are available:

- `elf=<filename>`: Required. The file with the payload.
- `section=<name>`: Required. This is the output section to insert, as specified in the `.ld` file.
- `offset=<offset>`: Required. This is the location of the data in the original file to replace.
- `length=<length>`: Optional. Sets the size of the block of data to replace. If the section in the `.elf` is smaller than the length provided, it is padded with zeroes at the end.
- `min_lengh=<length>`: Optional. Minimum length. Set automatically if using the `length` parameter.
- `max_length=<length>`: Optional. Maximum length. Set automatically if using the `length` parameter.
- `replace_zeroes`: Optional. When specified, the expected data to replace will be all zeroes instead of the content actually in the original file.
