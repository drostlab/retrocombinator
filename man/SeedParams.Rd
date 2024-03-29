% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/params.R
\name{SeedParams}
\alias{SeedParams}
\title{Create SeedParams object}
\usage{
SeedParams(toSeed = TRUE, seedForRNG = 0)
}
\arguments{
\item{toSeed}{Should this sequence be run with a specific initial seed? If
so, then the seed is specified by the parameter seedForRNG; else a seed
based on system time is used}

\item{seedForRNG}{seed to a (pseudo)random number generator, only used if `toSeed` is TRUE}
}
\value{
A bundling of the parameters given to it as a SeedParams object
}
\description{
Create SeedParams object
}
\examples{
seedParams <- SeedParams(toSeed = FALSE)
}
