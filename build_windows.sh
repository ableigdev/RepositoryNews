#!/bin/bash 
mkdir build && cd build
conan install .. -s compiler.version=15
cmake .. -G "Visual Studio 15 Win64"
cmake --build . 
