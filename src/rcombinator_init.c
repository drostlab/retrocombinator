#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME:
Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP _retrocombinator_rcpp_simulate_with_flags_random(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP);
extern SEXP _retrocombinator_rcpp_simulate_with_flags_specified(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP);
extern SEXP _retrocombinator_rcpp_simulate_without_flags_random(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP);
extern SEXP _retrocombinator_rcpp_simulate_without_flags_specified(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
  {"_retrocombinator_rcpp_simulate_with_flags_random",       (DL_FUNC) &_retrocombinator_rcpp_simulate_with_flags_random,       25},
  {"_retrocombinator_rcpp_simulate_with_flags_specified",    (DL_FUNC) &_retrocombinator_rcpp_simulate_with_flags_specified,    25},
  {"_retrocombinator_rcpp_simulate_without_flags_random",    (DL_FUNC) &_retrocombinator_rcpp_simulate_without_flags_random,    19},
  {"_retrocombinator_rcpp_simulate_without_flags_specified", (DL_FUNC) &_retrocombinator_rcpp_simulate_without_flags_specified, 19},
  {NULL, NULL, 0}
};

void R_init_retrocombinator(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}