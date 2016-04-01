# C++ Expose - library for type introspection, reflection, and scripting interface

```cppexpose``` is a C++11 library that provides tools for introspection of types,
properties, and classes. This allows for a C++ program to expose its interfaces into
runtime, making it possible to, e.g., create automatic GUI representations for interfaces,
or to expose them into a scripting environment.

The implementation is based on standard C++ templates and does not use language extensions
or macros, making it typesafe and usable with any C++11 compliant toolchain. Also, no meta
compilation step is required.


## Build Status

| Service | System | Compiler | Status |
| ------- | ------ | -------- | ------ |
| Jenkins | Ubuntu 14.04 | GCC 4.7 | [![Build Status](http://jenkins.hpi3d.de/buildStatus/icon?job=cppexpose-linux-gcc4.7)](http://jenkins.hpi3d.de/job/cppexpose-linux-gcc4.7)|
| Jenkins | Ubuntu 14.04 | GCC 4.8| [![Build Status](http://jenkins.hpi3d.de/buildStatus/icon?job=cppexpose-linux-gcc4.8)](http://jenkins.hpi3d.de/job/cppexpose-linux-gcc4.8)|
| Jenkins | Ubuntu 14.04 | GCC 4.9 | [![Build Status](http://jenkins.hpi3d.de/buildStatus/icon?job=cppexpose-linux-gcc4.9)](http://jenkins.hpi3d.de/job/cppexpose-linux-gcc4.9)|
| Jenkins | Ubuntu 14.04 | GCC 5.3 | [![Build Status](http://jenkins.hpi3d.de/buildStatus/icon?job=cppexpose-linux-gcc5.3)](http://jenkins.hpi3d.de/job/cppexpose-linux-gcc5.3)|
| Jenkins | Ubuntu 14.04 | Clang 3.5 | [![Build Status](http://jenkins.hpi3d.de/buildStatus/icon?job=cppexpose-linux-clang3.5)](http://jenkins.hpi3d.de/job/cppexpose-linux-clang3.5) |
| Jenkins | Windows 8.1 | MSVC 2013 Update 5 | [![Build Status](http://jenkins.hpi3d.de/buildStatus/icon?job=cppexpose-windows-msvc2013)](http://jenkins.hpi3d.de/job/cppexpose-windows-msvc2013) |
| Jenkins | Windows 8.1 | MSVC 2015 Update 1 | [![Build Status](http://jenkins.hpi3d.de/buildStatus/icon?job=cppexpose-windows-msvc2015)](http://jenkins.hpi3d.de/job/cppexpose-windows-msvc2015) |
