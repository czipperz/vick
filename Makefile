CXX=clang++
NUM_THREADS=8

all:
	vick-build/vick-build NUM_THREADS=${NUM_THREADS} CXX=${CXX}

test:
	vick-build/vick-build NUM_THREADS=${NUM_THREADS} CXX=${CXX} \
test

clean:
	vick-build/vick-build clean

install: all
	cp vick /usr/bin

.PHONY: all test clean install
