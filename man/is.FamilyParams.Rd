% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/params.R
\name{is.FamilyParams}
\alias{is.FamilyParams}
\title{Is x a FamilyParams object?}
\usage{
is.FamilyParams(x)
}
\arguments{
\item{x}{An arbitrary object}
}
\value{
A logical, TRUE if \code{x} is a FamilyParams object, and FALSE otherwise
}
\description{
Is x a FamilyParams object?
}
\examples{
is.FamilyParams(FamilyParams()) # TRUE
is.FamilyParams(data.frame()) # FALSE
}
