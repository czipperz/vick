# Contributing to vick

## Bug Fixes

If you want to fix a core feature in `vick`, please submit a pull
request to the [Github page](https://github.com/czipperz/vick).
Otherwise submit a pull request to a plugins' page.

## Making a plugin

Example for bash shells:

1.  Clone the plugin base repo and `cd` into it
2.  Change the remote origin to your own
3.  Make the `src` directory
4.  Make the plugin.  *Each file to be compiled should be added to the makefile.*

Code:

    $ git clone https://github.com/czipperz/vick-plugin-base <my-plugin-name>
    $ cd <my-plugin-name>
    $ git remote remove origin
    $ git remote add origin <git server location>
    $ mkdir src
    $ # make plugin
