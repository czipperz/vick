# Contributing to vick

## Bug Fixes

If you want to fix a core feature in `vick`, please submit a pull
request to the [Github repository](https://github.com/czipperz/vick).
Otherwise submit a pull request to a plugins' repository.

## Making a plugin

Example for bash shells:

1.  Clone the main vick repo and `cd` into it
    `git clone https://github.com/czipperz/vick; cd vick`
2.  Generate documentation with `make doc`
3.  Configure vick with `./configure` (installing the packages isn't
    required).
4.  Create your package with `make new PACKAGE=<package_name>`
    where `<package_name>` is the name of the package
5.  Work on the package (it's in `plugins/<package_name>`).
    Declare interface and documentation in `lib.hh`, put source code in
    `src/<package_name>.cc`
6.  Compile the project with `make`
7.  Write tests in `test/<package_name>_tests.cc`
8.  Run tests with `make test`

If you want to read the vick documentation, you need to install
`doxygen` and `graphviz`.  Then go to the main vick repo location and
run `make doc`.  If you add documentation to your own code, it will be
included when you run `make doc`.

Code:

    $ git clone https://github.com/czipperz/vick
    $ cd vick
    $ make doc     # generate documentation
    $ ./configure
    $ make new PACKAGE=<package_name>
    $ cd plugins/<package_name>
