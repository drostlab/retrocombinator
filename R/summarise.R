#' Summary function wrapper
#' @param data Simulation output data obtained from [retrocombinator::parseEvolutionOutput()()]
#' @param type What should be summarised?
#' \describe{
#' \item{"initial"}{Summarise the similarity to initial sequence over time.}
#' \item{"pairwise"}{Summarise the similarity between sequences over time.}
#' \item{"families"}{Summarise the evolution of families over time.}
#' }
#' @param ... Any additional arguments to pass to specialised plotting functions
#'        (currently unused)
#' @return A corresponding summary dataframe, based on the simulation of
#'         the evolution of retrotransposons
#' @examples
#' \dontrun{
#' summariseEvolution(myData, "initial")
#' }
#' @export
summariseEvolution <- function(data, type, ...) {
  switch(type,
    initial = summariseInitialDistance(data, ...),
    pairwise = summarisePairwiseDistance(data, ...),
    families = summariseFamilies(data, ...),
    history = summariseHistory(data, ...)
  )
}

summariseInitialDistance <- function(data, activeCheck = FALSE) {
  sequences <- data$sequences
  if (activeCheck) {
    sequences <- sequences %>% dplyr::filter(isActive == TRUE)
  }
  seqLength <- data$params$SequenceParams_sequenceLength
  sequences %>%
    dplyr::group_by(realTime, step) %>%
    dplyr::summarise(
      numSequences = dplyr::n_distinct(sequenceId),
      divergenceMin = 1.0 - min(distanceToInitial)/seqLength,
      divergenceQ25 = 1.0 - quantile(distanceToInitial, 0.25)/seqLength,
      divergenceMedian = 1.0 - median(distanceToInitial)/seqLength,
      divergenceQ75 = 1.0 - quantile(distanceToInitial, 0.75)/seqLength,
      divergenceMax = 1.0 - max(distanceToInitial)/seqLength,
      divergenceMean = 1.0 - mean(distanceToInitial)/seqLength
    )
}

summarisePairwiseDistance <- function(data) {
  pairwise <- data$pairwise
  seqLength <- data$params$SequenceParams_sequenceLength
  pairwise %>%
    dplyr::group_by(realTime, step) %>%
    dplyr::summarise(
      pairwiseMin = 1.0 - min(distancePairwise)/seqLength,
      pairwiseQ25 = 1.0 - quantile(distancePairwise, 0.25)/seqLength,
      pairwiseMedian = 1.0 - median(distancePairwise)/seqLength,
      pairwiseQ75 = 1.0 - quantile(distancePairwise, 0.75)/seqLength,
      pairwiseMax = 1.0 - max(distancePairwise)/seqLength,
      pairwiseMean = 1.0 - mean(distancePairwise)/seqLength
    )
}

summariseFamilies <- function(data) {
  familyRepresentatives <- data$familyRepresentatives
  seqLength <- data$params$SequenceParams_sequenceLength
  familyRepresentatives %>%
    dplyr::group_by(realTime, step, familyId) %>%
    dplyr::summarise(familySize = dplyr::n()) %>%
    dplyr::group_by(realTime, step) %>%
    dplyr::summarise(
      numSequences = sum(familySize),
      numFamilies = dplyr::n_distinct(familyId),
      familiesMin = min(familySize),
      familiesQ25 = quantile(familySize, 0.25),
      familiesMedian = median(familySize),
      familiesQ75 = quantile(familySize, 0.75),
      familiesMax = max(familySize),
      familiesMean = mean(familySize)
    )
}
