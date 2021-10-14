#' Run an entire simulation with flags
#' @useDynLib retrocombinator, .registration = TRUE
#' @importFrom Rcpp sourceCpp
#' @export
simulateEvolution <- function(
    sequenceParams = SequenceParams(),
    activityParams = ActivityParams(),
    mutationParams = MutationParams(),
    burstParams = BurstParams(),
    recombParams = RecombParams(),
    selectionParams = SelectionParams(),
    familyParams = FamilyParams(),
    simulationParams = SimulationParams(),
    outputParams = OutputParams(),
    seedParams = SeedParams()
  ) {

  # TODO: Do this fixing in the SequenceParams object
  sequenceParams$initialSequence <- ifelse(is.null(sequenceParams$initialSequence), "", sequenceParams$initialSequence)
  chars <- unlist(strsplit(sequenceParams$initialSequence, ""))
  if(!all(chars %in% c("A", "T", "G", "C"))) {
    warning("String not comprising of only ATGC characters, ignoring other characters")
    chars_fixed <- chars[chars %in% c("A", "T", "G", "C")]
    sequenceParams$initialSequence <- paste0(chars_fixed, collapse = "")
  }
  rcpp_simulate_evolution(
    sequenceParams$initialSequence,
    sequenceParams$sequenceLength, sequenceParams$numInitialCopies,
    activityParams$lengthCriticalRegion, activityParams$probInactiveWhenMutated,
    mutationParams$model,
    burstParams$burstProbability, burstParams$burstMean, burstParams$maxTotalCopies,
    recombParams$recombMean, recombParams$recombSimilarity,
    selectionParams$selectionThreshold,
    familyParams$familyCoherence, familyParams$maxFamilyRepresentatives,
    simulationParams$numSteps, simulationParams$timePerStep,
    outputParams$outputFilename,
    outputParams$outputNumInitialDistance, outputParams$outputNumPairwiseDistance,
    outputParams$outputNumFamilyLabels, outputParams$outputNumFamilyMatrix,
    outputParams$outputMinSimilarity,
    seedParams$toSeed, seedParams$seedForRNG
  )
  return(outputParams$outputFilename)
}
