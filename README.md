# libfingc

![LICENSE](https://img.shields.io/github/license/dominik-chat/libfingc?style=flat-square)

libfingc is an implementation of standard C library.
The goal of this project is to provide simple, yet functional libc.

**The whole projest is WIP, so it does not have all required implementations to perform complete functions.**

# Porting

To work on different OSes the library requires a porting layer with appropriate syscalls (WIP).

## Compilation

This library requires [gcc](https://gcc.gnu.org/).
The compilation can be performed by executing the following command in the root of the repository:
```
make
```

## Usage

The library builds as a static library and set of include files.
Use it in place of normal libc - this can require cross-compiling or at least usage of `-nostdlib` flag to compiler.

The library also requires initialization code, which is WIP.
