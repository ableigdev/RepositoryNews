#!/bin/bash 
conan remote add ableigdev https://api.bintray.com/conan/ableigdev/public-conan
mkdir build && cd build
conan install .. -s build_type=Release --build libgit2
cmake .. -G "Unix Makefiles"
cmake --build .
