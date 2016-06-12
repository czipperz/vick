# begin vick-build commands
all: build
	vick-build/vick-build NUM_THREADS=8

test: build
	vick-build/vick-build test NUM_THREADS=8

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


TAGS:
	@echo 'etags $$(find -name "*.cc" -o -name "*.hh")'
	@etags $(shell find -name "*.cc" -o -name "*.hh")


.PHONY: \
all test clean build \
install \
new clone remove search \
TAGS
