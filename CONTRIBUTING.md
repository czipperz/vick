# Contributing to vick

## Bug Fixes

If you want to fix a core feature in `vick`, please submit a pull
request to the [Github repository](https://github.com/czipperz/vick).
Otherwise submit a pull request to a plugins' repository.

## Making a plugin

Example for bash shells:

1.  Clone the main vick repo and `cd` into it
2.  Run `./configure` (installing the packages isn't required).
3.  Run `./vick-package/vick-package create <package_name>` where
    `<package_name>` is the name of the package you wish to create.

If you want to read the vick documentation, you need to install
`doxygen` and `graphviz`.  Then go to the main vick repo location and
run `make doc`.  If you add documentation to your own code, it will be
included when you run `make doc`.

Code:

    $ git clone https://github.com/czipperz/vick
    $ cd vick
    $ make doc     # generate documentation
    $ ./configure
    $ ./vick-package/vick-package create <package_name>
    $ cd plugins/<package_name>
