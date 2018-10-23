[//]: # (Comment)

<br><a href="https://github.com/cginternals/cppexpose/"><img src="https://raw.githubusercontent.com/cginternals/cppexpose/master/cppexpose-logo.svg?sanitize=true" width="50%"></a>

*cppexpose* is a cross-platform C++11 library that provides tools for introspection of types,
properties, and classes. This allows for a C++ program to expose its interfaces into
runtime, making it possible to, e.g., create automatic GUI representations for interfaces,
or to expose them into a scripting environment.

![GitHub release](https://img.shields.io/github/release/cginternals/cppexpose.svg)
[![Travis](https://img.shields.io/travis/cginternals/cppexpose/master.svg?style=flat&logo=travis)](https://travis-ci.org/cginternals/cppexpose)
[![Tokei](https://tokei.rs/b1/github/cginternals/cppexpose)](https://github.com/Aaronepower/tokei)
[![Tokei](https://tokei.rs/b1/github/cginternals/cppexpose?category=comments)](https://github.com/Aaronepower/tokei)


The implementation is based on standard C++ templates and does not use language extensions
or macros, making it typesafe and usable with any C++11 compliant toolchain. Also, no meta
compilation step is required.
