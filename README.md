# JSON++

A flex+bison JSON parser to be controlled from C++.

## Usage



## How to build JSON++

Just run

    make

## Flex/Bison quirks when using C++ classes

* `%union { ... }` must only contain native C types or pointers to C++ classes,
* in case pointers to C++ classes are used in `%union`, classes extended from `std` containers won't work,
* 