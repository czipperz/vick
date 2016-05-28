#!/bin/bash

set -e

git clone https://github.com/czipperz/vick-build

cd vick-build
./configure
make CXX=g++-4.8 -j5
cd ..

vick-build/vick-build NUM_THREADS=8 CXX=g++-4.8 test
