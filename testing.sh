#!/bin/bash

git clone https://github.com/czipperz/vick-build

cd vick-build
./configure
make
cd ..

./configure
make
