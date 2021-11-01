## R CMD check results

* Note that this is my first submission to CRAN

```
* checking installed package size ... NOTE
  installed size is  5.1Mb
  sub-directories of 1Mb or more:
    libs   4.5Mb
```

* On some machines, where binaries are compiled with debugging symbols, the
  installed size is 5.1Mb, with the libs directory taking up 4.5Mb. On any
  machine that strips out this debug information during compilation,
  (by having `SHLIB_CXX11LDFLAGS = -Wl,-S -shared` in `Makevars`), this is not
  an issue.

```
Possibly mis-spelled words in DESCRIPTION:
  extrachromosomal (9:125)
  retrotransposon (3:57, 9:89)
```

* The words "extrachromosomal" and "retrotransposon" are not mis-spelled, they
  reflect neologisms in the research fields investigating transposable elements
  that copy and paste themselves into different genomic locations via RNA
  intermediates. 
