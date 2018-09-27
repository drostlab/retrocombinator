#!/bin/bash

options="$1"

# default is 'all'
if [ "$options" == "" ]
then
    options="a"
fi

if [ "$options" == "o" ] || [ "$options" == "a" ]
then
    # Clean Rcpp generated object files
    rm -f src/*.o
    rm -f src/*.so
fi

if [ "$options" == "c" ] || [ "$options" == "a" ]
then
    # Clean Rcpp generated source files
    rm -f src/RcppExports.cpp
    rm -f R/RcppExports.R
fi

if [ "$options" == "v" ] || [ "$options" == "a" ]
then
    # Clean vignette files
    rm -f vignettes/*.out
fi

if [ "$options" != "c" ] && [ "$options" != "a" ] && [ "$options" != "o" ]
then
    echo -e "Usage: ./clean_r.sh <option> where option is 'o', 'c', 'v' or 'a'"
    echo -e "o: Rcpp generated object files"
    echo -e "c: Rcpp generated source files"
    echo -e "v: Vignette generated files"
    echo -e "a: all Rcpp generated files"
    echo -e "Default behaviour is 'a'"
fi
