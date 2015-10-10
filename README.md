# Vick [![Build Status](https://travis-ci.org/czipperz/vick.svg)](https://travis-ci.org/czipperz/vick)

#### VICK IS NOWHERE NEAR READY FOR USAGE.

Vick is a `VI` based editor that focuses on configuration.  It
intentionally comes with no behavior by default!  A make command will
be used to download default behavior because of this.  To be able to
configure Vick you must be able to compile from source Vick.

Vick requires a compiler that supports `c++11`.  Most modern compilers
do.  For `gcc` that means version 4.8.  Vick uses `clang` by default,
which requires version 3.4.  To use `gcc`, just pass `CXX=g++` to all
the make commands.

So here's how to compile it from source:

    git clone https://github.com/czipperz/vick vick
    cd vick
    ./configure  # setup Makefile and download basic plugins
    make         # compile `vick` and all plugins installed and make an executable
    make test    # run test suite
    make doc     # generate documentation - requires ``doxygen`` and ``graphviz``
