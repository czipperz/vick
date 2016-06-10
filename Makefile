CXX=clang++
NUM_THREADS=8
PACKAGE=

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

new:
	vick-package/vick-package create ${PACKAGE}

TAGS:
	@echo "Using etags to generate tags"
	@etags $(shell find -name '*.cc' -o -name '*.hh')

.PHONY: all test clean install new TAGS
