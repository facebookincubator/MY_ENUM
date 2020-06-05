#!/bin/bash

set -x # echo on
set -e # exit on error

ls
mkdir build
cd build
cmake .. -DCMAKE_CXX_COMPILER="c++" -DCMAKE_CXX_FLAGS="-std=c++11 -stdlib=libc++"
cmake --build .
