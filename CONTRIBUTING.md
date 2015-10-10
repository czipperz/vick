# Contributing to vick

## Bug Fixes

If you want to fix a core feature in `vick`, please submit a pull
request to the [Github page](https://github.com/czipperz/vick).
Otherwise submit a pull request to a plugins' page.

## Making a plugin

Example for bash shells:

1.  Clone the main vick repo and `cd` into it
2.  Make the plugins directory and `cd` into that
3.  Clone the plugin base repo under your own name and `cd` into it
4.  Change the remote origin to your own
5.  Make the `src` directory
6.  Create the plugin.  *Each file to be compiled should be added to
    the makefile.*

If you want to read the vick documentation, you need to install
`doxygen` and `graphviz`.  Then go to the main vick repo location and
run `make doc`.  If you add documentation to your own code, it will be
included when you run `make doc`.

Code:

    $ git clone https://github.com/czipperz/vick
    $ cd vick
    $ make doc     # generate documentation
    $ mkdir -p plugins
    $ cd plugins
    $ git clone https://github.com/czipperz/vick-plugin-base <my-plugin-name>
    $ cd <my-plugin-name>
    $ git remote remove origin
    $ git remote add origin <git-server-location>
    $ mkdir src
    $ # create plugin
