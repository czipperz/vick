# CXX is builtin, if not provided, don't set for BUILD_FLAGS
ifeq (${origin CXX}, default)
CXX_Command :=
else
CXX_Command := CXX="${CXX}"
endif

ifeq (${origin CXXFLAGS}, undefined)
CXXFLAGS_Command :=
else
CXXFLAGS_Command := CXXFLAGS+="${CXXFLAGS}"
endif

NUM_THREADS ?= 8

BUILD_FLAGS := NUM_THREADS="${NUM_THREADS}" ${CXX_Command} ${CXXFLAGS_Command}

# begin vick-build commands
all: build
	vick-build/vick-build ${BUILD_FLAGS}

test: build
	vick-build/vick-build test ${BUILD_FLAGS}

clean: build
	vick-build/vick-build clean

build:
	(cd vick-build; make)
# end vick-build commands


install: all
	cp vick /usr/bin


# begin vick-package commands
new: package
	vick-package/vick-package create ${PACKAGE}

clone: package
	vick-package/vick-package install ${PACKAGE}

remove: package
	vick-package/vick-package remove ${PACKAGE}

search: package
	vick-package/vick-package search ${QUERY}

package: package
	(cd vick-package; make)
# end vick-package commands

tmp := $(shell mktemp)

doc:
	cp Doxyfile "${tmp}"
	echo "INPUT = src $(shell ls plugins | \
            perl -pe 's|(.*)|plugins/$$1/lib.hh|')" >> "${tmp}"
	doxygen "${tmp}"
	rm "${tmp}"

TAGS:
	@echo 'etags $$(find -name "*.cc" -o -name "*.hh")'
	@etags $(shell find -name "*.cc" -o -name "*.hh")


.PHONY: \
all test clean build \
install \
new clone remove search \
doc TAGS
