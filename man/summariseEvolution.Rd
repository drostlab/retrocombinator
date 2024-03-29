% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/summarise.R
\name{summariseEvolution}
\alias{summariseEvolution}
\title{Summary function wrapper}
\usage{
summariseEvolution(data, type, ...)
}
\arguments{
\item{data}{Simulation output data obtained from [retrocombinator::parseEvolutionOutput()()]}

\item{type}{What should be summarised?
\describe{
\item{"initial"}{Summarise the similarity to initial sequence over time.}
\item{"pairwise"}{Summarise the similarity between sequences over time.}
\item{"families"}{Summarise the evolution of families over time.}
}}

\item{...}{Any additional arguments to pass to specialised plotting functions
(currently unused)}
}
\value{
A corresponding summary dataframe, based on the simulation of
        the evolution of retrotransposons
}
\description{
Summary function wrapper
}
\examples{
\dontrun{
summariseEvolution(myData, "initial")
}
}
