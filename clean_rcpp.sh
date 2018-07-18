#!/bin/bash

options="$1"

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

if [ "$options" != "c" ] && [ "$options" != "a" ] && [ "$options" != "o" ]
then
    echo -e "Usage: ./Rcpp_cleanup.sh <option> where option is 'o', 'c' or 'a'"
    echo -e "o: Rcpp generated object files"
    echo -e "c: Rcpp generated source files"
    echo -e "a: all Rcpp generated files"
fi
