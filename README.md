# libcds

Thread safe, templated data structure library written in C++

## Overview

Currently a work in progress, but aimed to work on my understanding of typical data structures, C++ libraries / headers / projects, DLL creation, multi-threading, test suites, Makefiles, CMake, cross-platform development, etc.

The eventual goal is for this to be a lock-free, leak-free, and absolutely marvelous library for C++, complete with a solid cross-platform build system generator thanks to CMake. This is primarily a personal challenge, but it'll most certainly help me learn all those topics and more.

## Data Structures

Data Structures so far:

- Linked List
  - Unit Tested, verified 2025.07.07
- Doubly Linked List
  - Unit Tested, verified 2025.07.07

Data Structures planned:

- Array
- Stack
- Queue
- Arraylist (like a vector)
- Binary Trees
- B+ Tree (like those used in databases)

> Stack and Queue will probably be built on top of a Linked List, but potentially a simple List.

## Contents

Structure now aims to follow the [Pitchfork](https://github.com/vector-of-bool/pitchfork) conventions as closely as possible.

| Folders | Description |
| :-----: | :---------- |
| bin | Contains all "installed" executables and libraries. |
| build | Where build systems should be built. |
| cmake | CMake functions and utilities. |
| docs | Documentation markdowns, installation, tutorials, etc. |
| examples | Pending several things, this will include some example uses of the library. |
| include | Contains public headers. |
| src | Contains source code & private headers [currently empty] |
| test | Holds all test code, like unit & stress tests. |

TODO: where should `utils` go? `include` makes sense; perhaps just put utility stuff into `include/util`, then separate files based on usage?

## Compilation

There is already a CMake system in place to generate the build system.

I have confirmed it works with Win32 and x64 builds using Visual Studio 2022.

You can utilize the CMake GUI to get started now. Instructions, when complete, will be located in `/docs/build.md`

## Known Issues & To-Dos

Many issues have been fixed thus far, but some still remain...

- Memory leaks need to be investigated in both the tests and library
- Also, the library doesn't actually build anything (there is no `.lib` or `.dll` or anything).
- Need to implement the INSTALL instructions so that the INSTALL project in VS2022 actually does something.
  - This will likely just move something from the build folder to the corresponding bin folder.

Besides implementing the rest of the data structures, some additional features and functionality are pending...

- Stress Tests, to be hosted inside `/test` as a means of really putting the data structures to the test.
- To-String method, probably returning a `const char*` rather than `std::string`.
- Docs need to be written, regarding how to include, usage, etc.
- Lock-free (this one will be here for a long time).
