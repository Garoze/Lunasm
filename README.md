# Lunasm

A simple assembly language written in C++17 for the [Luna16](https://github.com/Garoze/Console) fantasy console.

## Compiling from Source

_Lunasm_ uses [CMake](https://cmake.org/) and [Ninja](https://ninja-build.org/manual.html) as a build solution. To build the project follow the steps according to your operating system.

### Linux / macOS

Clone this repository

```
git clone --recursive https://github.com/Garoze/Lunasm.git
```
Enter on the `Lunasm` folder, and run the configure script
```
./configure.sh
``` 
To compile it run the following command
```
ninja -C build 
```

### Windows

Not supported.

## Run 

To run the project execute the binary inside `Lunasm/bin/Lunasm` or execute the `run.sh` script.

## Resources

### Toolchain

* [CMake 3.24.3](https://cmake.org/)
* [Ninja 1.11.1](https://ninja-build.org/manual.html)
* [GCC 11.3.1](https://gcc.gnu.org/)

### Libraries

* [fmtlib](https://github.com/fmtlib/fmt) - A modern formatting library in
  the style of C++20 std::format _(contained in `external/fmtlib`)_
* [argparse](https://github.com/p-ranav/argparse) - Argument Parser for Modern C++ _(contained in `external/argparse`)_
* [googletest](https://github.com/google/googletest) - GoogleTest - Google Testing and Mocking Framework _(contained in `external/googletest`)_

## License

This project in under the [MIT](https://mit-license.org/). You can check the file [here](LICENSE)
