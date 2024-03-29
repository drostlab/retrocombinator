% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/params.R
\name{is.SeedParams}
\alias{is.SeedParams}
\title{Is x a SeedParams object?}
\usage{
is.SeedParams(x)
}
\arguments{
\item{x}{An arbitrary object}
}
\value{
A logical, TRUE if \code{x} is a SeedParams object, and FALSE otherwise
}
\description{
Is x a SeedParams object?
}
\examples{
is.SeedParams(SeedParams()) # TRUE
is.SeedParams(data.frame()) # FALSE
}
