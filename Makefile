CXX=clang++
NUM_THREADS=8

all:
	(cd vick-build; make)
	vick-build/vick-build NUM_THREADS=${NUM_THREADS} CXX=${CXX}

test:
	(cd vick-build; make)
	vick-build/vick-build NUM_THREADS=${NUM_THREADS} CXX=${CXX} \
test

clean:
	vick-build/vick-build clean

install: all
	cp vick /usr/bin

.PHONY: all test clean install
