#!/bin/bash 
cd libgit2
mkdir build
cd build
cmake -DBUILD_CLAR=OFF -DCMAKE_INSTALL_PREFIX=../../installed ..
cmake --build . --target install
cd ../../
mkdir build
cd build
echo "-- Path to qt(bash): " $1
cmake -DPATH_TO_QT:STRING=$1 -DCMAKE_INSTALL_PREFIX=../rpnews_installed ..
cmake --build . --target install
