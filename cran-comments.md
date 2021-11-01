## Resubmission

I am resubmitting my package without the "+ file LICENSE" in DESCRIPTION and the
LICENSE file because they were superfluous, as I am using GPL-3.

## Original message

Dear CRAN maintainers,

I have uploaded a new package named retrocombinator to CRAN. The package is also
hosted on https://github.com/drostlab/retrocombinator

I have read the CRAN policies and agree with them.

All automated checks have passed, with 0 ERRORs and 0 WARNINGs. Listed
below are some NOTEs from `R CMD CHECK`, and why they are OK.

Thank you very much!

Kind regards,
Anindya

## `R CMD check` - possible NOTEs and explanations

```
New submission
```

* Note that this is my first submission to CRAN

```
* checking installed package size ... NOTE
  installed size is  5.1Mb
  sub-directories of 1Mb or more:
    libs   4.5Mb
```

* This R package uses C++ code underneath for optimisation, and links the C++
  code to R using the Rcpp package. On some machines, where binaries are
  compiled with debugging symbols left in, the overall installed size becomes
  *5.1Mb*, with the libs directory taking up *4.5Mb*. On any machine that strips
  out this debug information during compilation, which is what most machines do,
  this is not a problem. On exceptional machines, debugging information can be
  stripped out by having `SHLIB_CXX11LDFLAGS = -Wl,-S -shared` in `Makevars`,
  which dramatically reduces the size of the package.

```
Possibly mis-spelled words in DESCRIPTION:
  extrachromosomal (9:125)
  retrotransposon (3:57, 9:89)
```

* The words "extrachromosomal" and "retrotransposon" (/"Retrotransposon") are
  not mis-spelled, they are words in the research field of biology which is
  investigating transposable elements that copy and paste themselves into
  different genomic locations via RNA intermediates.
