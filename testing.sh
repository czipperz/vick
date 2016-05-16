#!/bin/bash

git clone https://github.com/czipperz/vick-build

cd vick-build
./configure
make CXX=g++-4.8
cd ..

./configure
vick-build/vick-build NUM_THREADS=8 CXX=g++-4.8 test
