#!/bin/bash

set -x # echo on
set -e # exit on error

brew install boost
brew install cmake
git clone https://github.com/google/googletest
cd googletest
mkdir build
cd build
cmake .. -DCMAKE_CXX_COMPILER="c++" -DCMAKE_CXX_FLAGS="-std=c++11 -stdlib=libc++"
make
sudo make install
cd ../..
git clone https://github.com/fmtlib/fmt.git
cd fmt
git checkout 6.2.1
mkdir build
cd build
cmake .. -DFMT_TEST=OFF -DCMAKE_CXX_COMPILER="c++" -DCMAKE_CXX_FLAGS="-std=c++11 -stdlib=libc++"
make -j2
sudo make install
cd ../..
git clone https://github.com/CLIUtils/CLI11.git
cd CLI11
git checkout v1.9.0
mkdir build
cd build
cmake .. -DCLI11_BUILD_TESTS=OFF -DCMAKE_CXX_COMPILER="c++" -DCMAKE_CXX_FLAGS="-std=c++11 -stdlib=libc++"
make -j2
sudo make install
cd ../..
