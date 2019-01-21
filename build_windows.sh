#!/bin/bash 
conan remote add ableigdev https://api.bintray.com/conan/ableigdev/public-conan
mkdir build && cd build
conan install .. -s compiler.version=15 -s build_type=Release --build libgit2
cmake .. -G "Visual Studio 15 Win64"
cmake --build . 
