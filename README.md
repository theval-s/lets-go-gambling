## Simple Slot Machine on C++
This is a simple slot machine built on SFML in C++.

## Dependencies 
CMake
SFML (downloaded through CMake during build process)

## Build

```shell
mkdir build 
cmake -B build
cmake --build ./build
./OGGTest
```

In case you want to use specific build system generated by CMake pass it via the -G argument to 'cmake -B build' command.  
For example, use 'cmake -B build -G Ninja' to use Ninja instead of your default CMake generated build system.

## Resources
Icons were downloaded from public icon stocks under CC License, same as font.