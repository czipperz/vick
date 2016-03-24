#!/bin/bash
cabal update
cabal install shake

shakedir=.shake
mkdir -p $shakedir
ghc --make Build.hs -rtsopts -with-rtsopts=-I0 -outputdir=$shakedir \
    -o make -DIS_IN_TESTING=True

./make test
