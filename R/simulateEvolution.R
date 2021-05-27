#' Run an entire simulation with flags
#' @useDynLib retrocombinator, .registration = TRUE
#' @importFrom Rcpp sourceCpp
#' @export
simulateEvolution <- function(
    sequenceParams = SequenceParams(),
    simulationParams = SimulationParams(),
    mutationParams = MutationParams(),
    flagParams = FlagParams(),
    burstParams = BurstParams(),
    speciationParams = SpeciationParams(),
    outputParams = OutputParams(),
    seedParams = SeedParams()
  ) {

  num_seq <- sequenceParams$numInitialCopies
  sequenceLength <- sequenceParams$sequenceLength
  initialSequence <- sequenceParams$initialSequence
  numSteps <- simulationParams$numSteps
  timestep <- simulationParams$timestep
  maxActiveCopies <- simulationParams$maxActiveCopies
  model <- mutationParams$model
  lengthCriticalRegion <- flagParams$lengthCriticalRegion
  probInactiveWhenMutated <- flagParams$probInactiveWhenMutated
  maxInactiveCopies <- flagParams$maxInactiveCopies
  burstProbability <- burstParams$burstProbability
  burstMean <- burstParams$burstMean
  recombMean <- burstParams$recombMean
  recombSimilarity <- burstParams$recombSimilarity # TODO: Use this
  selectionThreshold <- speciationParams$selectionThreshold
  speciesSimilarity <- speciationParams$speciesSimilarity
  speciesCoherence <- speciationParams$speciesCoherence
  outputFilename <- outputParams$outputFilename
  outputNumRawSequence <- outputParams$outputNumRawSequence
  outputNumInitialDistance <- outputParams$outputNumInitialDistance
  outputNumPairwiseDistance <- outputParams$outputNumPairwiseDistance
  outputNumSpeciesTags <- outputParams$outputNumSpeciesTags
  toRandomise <- !seedParams$toSeed # TODO: Stop doing this
  toSeed <- seedParams$toSeed
  seedForRandom <- seedParams$seedForRandom

  if (probInactiveWhenMutated > 0 && lengthCriticalRegion >= 1) {
    if (is.null(initialSequence)) {
      rcpp_simulate_with_flags_random(
        num_seq, sequenceLength,
        model,
        lengthCriticalRegion, probInactiveWhenMutated,
        numSteps, timestep,
        burstProbability, burstMean,
        maxActiveCopies, maxActiveCopies + maxInactiveCopies,
        recombMean,
        selectionThreshold, speciesSimilarity, speciesCoherence,
        outputFilename, outputNumSpeciesTags, outputNumInitialDistance, outputNumRawSequence, outputNumPairwiseDistance,
        toRandomise, toSeed, seedForRandom,
        0, 0,
        FALSE
      )
    } else {
      rcpp_simulate_with_flags_specified(
        initialSequence, 0,
        model,
        lengthCriticalRegion, probInactiveWhenMutated,
        numSteps, timestep,
        burstProbability, burstMean,
        maxActiveCopies, maxActiveCopies + maxInactiveCopies,
        recombMean,
        selectionThreshold, speciesSimilarity, speciesCoherence,
        outputFilename, outputNumSpeciesTags, outputNumInitialDistance, outputNumRawSequence, outputNumPairwiseDistance,
        toRandomise, toSeed, seedForRandom,
        0, 0,
        FALSE
      )
    }
  } else {
    if (is.null(initialSequence)) {
      rcpp_simulate_without_flags_random(
        num_seq, sequenceLength,
        model,
        numSteps, timestep,
        burstProbability, burstMean,
        maxActiveCopies,
        recombMean,
        outputFilename, outputNumSpeciesTags, outputNumInitialDistance, outputNumRawSequence, outputNumPairwiseDistance,
        toRandomise, toSeed, seedForRandom,
        0, 0,
        FALSE
      )
    } else {
      rcpp_simulate_without_flags_specified(
        initialSequence, 0,
        model,
        numSteps, timestep,
        burstProbability, burstMean,
        maxActiveCopies,
        recombMean,
        outputFilename, outputNumSpeciesTags, outputNumInitialDistance, outputNumRawSequence, outputNumPairwiseDistance,
        toRandomise, toSeed, seedForRandom,
        0, 0,
        FALSE
      )
    }
  }
  return(outputParams$outputFilename)
}
