<p align = "center">
    <img alt = "license" src = "https://img.shields.io/badge/License-AGPLv3-green.svg">
</p>

<h1 align = "center">Oscar <code>beta</code></h1>
<h3 align = "center">a highly efficient garbage collector</h3>

# Overview

`oscar` is a conservative garbage collector for C that aims to automate and remove the `malloc` and `free` redundancy, replacing it with simpler and smarter functions. It is aimed to be highly efficient and fast, as suggested by it being named after the best Sesame Street character, [Oscar](https://muppet.fandom.com/wiki/Oscar_the_Grouch), and following the virtues listed in his record-breaking song, [I Love Trash](https://www.youtube.com/watch?v=rxgWHzMvXOY).

# Features
- [x] Reliable, and Conservative Design
- [x] Page-Sized Memory Allocation
- [x] Smart and Efficient Memory Scanning
- [x] Simple and User-Friendly API

# Downloading

Either `make` from source or download the release, and use the `oscar.h` in your code.

# API

### `oscarize()`
Initialize and setup `oscar`. No arguments and returns.

### `oscar()`
Garbage collect. No arguments and returns.

# Example

Allocate `char` sized memory to `elmo` and then garbage collect it before exiting.

```c
#include <stdio.h>
#include <oscar.h>

int main() {
    oscarize();
    char* elmo = (char*) allocate(sizeof(char));
    *elmo = "f";
    printf(elmo);
    oscar();
    return 0;
}
```

# Copyright &copy; 2022 Aarush Gupta
This code is copyrighted but licensed to the public under the GNU AGPLv3 license and any later versions.
