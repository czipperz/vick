# Vick

**VICK IS NOWHERE NEAR READY FOR USAGE.  AS OF NOW IT DOESN'T EVEN
  EDIT TEXT!!**

Vick is a `VI` based editor that focuses on configuration.  To be able
to configure Vick you must be able to compile from source Vick.  So
here's how to compile it from source:

    git clone https://github.com/czipperz/vick vick
    cd vick
    make test     # will make and do tests

Vick will have a (minor) speed improvement if you compile it with
C++11 enabled.  This is because of the `move` constructor that deals
with resources better.  It will still work in both versions but large
files will work better in the C++11 version.  Just run make as the
following:

    make VER=c++11 test

The default is `c++98`.
