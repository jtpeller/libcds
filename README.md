# libcds

Thread safe, templated data structure library written in C++

## Overview

Currently a work in progress, but aimed to work on my understanding of typical data structures, C++ libraries / headers, multi-threading, test suites, Makefiles, etc.

## Data Structures

Data Structures implemented:

- Linked List
- Doubly Linked List

Data Structures planned:

- Stack
- Queue
- Arraylist (like a vector)
- Binary Trees
- B+ Tree (like used in databases)

## Contents

Structure for this library follows the [Canonical Project Structure](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1204r0.html).

| Folder or File | Description |
| -------------- | ----------- |
| build | Contains all build files, including bin and obj. These are created upon compilation. |
| libcds | contains all source files |
| tests | contains function/integration tests. Currently empty. |
| makefile | contains the recipe to create the program |
| README.md | what you're reading |

## Compilation

In order to compile this code, you have two methods: (1) using the Makefile or (2) using the `sh` scripts.

### Using Make

To use the Makefile, open a terminal in the project root, and run make. It defaults to all.

```sh
make
```

Other Make Labels are:

- `all`: Builds all preqrequisites: `build`, plus all data structures (currently implemented).
- `build`: Creates all necessary build folders. (`./build`, `./build/bin`, and `./build/objs`)
- `clean`: Cleans up created files, but not directories.
- `full-clean`: Cleans up created files and directories.
- `info`: Prints information about make variables.
- `release`: Adds `-O2` to the CXXFLAGS, then all.
- `test`: Adds `-DDEBUG -g` to the CXXFLAGS, then all.

### Using Scripts

I have two scripts: (1) unittest.sh and (2) runtests.sh

1. `unittest.sh`: Runs `make`, executes the files, then runs `make clean`.
2. `runtests.sh`: Assumes `make` is already run and tries to execute the files. Does no cleanup either. Useful for repeated testing of the same binaries (e.g., to test race conditions).

## Known Issues

- Currently, object files are not created, so running `make` will result in compilation every time.
- There seems to be a race condition (testThreadSafe is failing). This may be an implementation error in the test, or my mutex implementation is flawed.
