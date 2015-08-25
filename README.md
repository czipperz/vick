# Vick

#### VICK IS NOWHERE NEAR READY FOR USAGE.  AS OF NOW IT DOESN'T EVEN EDIT TEXT!!

Vick is a `VI` based editor that focuses on configuration.  To be able
to configure Vick you must be able to compile from source Vick.  So
here's how to compile it from source:

    git clone https://github.com/czipperz/vick vick
    cd vick
    make VER=c++11   # leave out the version if you don't have c++11 support (modern computers do)
    make test        # testing requires c++11 (gcc >= 4.8)

The default `VER` is `c++98`.
