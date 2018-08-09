#!/bin/bash 
cd libgit2
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=../../installed ..
cmake --build . --target install
