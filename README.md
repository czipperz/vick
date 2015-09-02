# Vick [![Build Status](https://travis-ci.org/czipperz/vick.svg)](https://travis-ci.org/czipperz/vick)

#### VICK IS NOWHERE NEAR READY FOR USAGE.  AS OF NOW IT DOESN'T EVEN EDIT TEXT!!

Vick is a `VI` based editor that focuses on configuration.  To be able
to configure Vick you must be able to compile from source Vick.

Vick requires a compiler that supports `c++11`.  Most modern compilers
do.  For `gcc` that means version 4.8.

So here's how to compile it from source:

    git clone https://github.com/czipperz/vick vick
    cd vick
    make
    make test    # run test suite
