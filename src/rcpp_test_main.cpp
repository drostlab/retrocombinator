#include <Rcpp.h>

#include <iostream>

#include "rand_maths.h"
#include "utilities.h"

using namespace rcombinator;

static RandMaths& r = RandMaths::initializeRandMaths(1);

//' @export
// [[Rcpp::export]]
double test_main()
{
    auto ans = r.rand_real();
    return ans;
}

//' @export
// [[Rcpp::export]]
double test_other()
{
    auto ans = is_in_range(10, 11, 14);
    return ans;
}

//' @export
// [[Rcpp::export]]
double test_new()
{
    auto ans = r.rand_int(10, 100);
    return ans;
}
