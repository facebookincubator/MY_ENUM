#!/bin/bash

set -x # echo on
set -e # exit on error

sudo apt install libboost-system-dev
git clone https://github.com/google/googletest
cd googletest
mkdir build
cd build
cmake ..
make
sudo make install
cd ../..
git clone https://github.com/fmtlib/fmt.git
cd fmt
git checkout 6.2.1
mkdir build
cd build
cmake .. -DFMT_TEST=OFF
make -j2
sudo make install
cd ../..
git clone https://github.com/CLIUtils/CLI11.git
cd CLI11
git checkout v1.9.0
mkdir build
cd build
cmake .. -DCLI11_BUILD_TESTS=OFF
make -j2
sudo make install
cd ../..
