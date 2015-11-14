#!/bin/sh
make             regen       testing=t
make CXX=g++-4.8       -j 10 testing=t
make CXX=g++-4.8 test  -j 10 testing=t
