#' Run an entire simulation with flags
#' @param sequenceParams A [retrocombinator::SequenceParams()] object for the simulation
#' @param activityParams An [retrocombinator::ActivityParams()] object for the simulation
#' @param mutationParams A [retrocombinator::MutationParams()] object for the simulation
#' @param burstParams A [retrocombinator::BurstParams()] object for the simulation
#' @param recombParams A [retrocombinator::RecombParams()] object for the simulation
#' @param selectionParams A [retrocombinator::SelectionParams()] object for the simulation
#' @param familyParams A [retrocombinator::FamilyParams()] object for the simulation
#' @param simulationParams A [retrocombinator::SimulationParams()] object for the simulation
#' @param outputParams A [retrocombinator::OutputParams()] object for the simulation
#' @param seedParams A [retrocombinator::SeedParams()] object for the simulation
#' @return A single character, the filename of the output of the simulation that
#' can then be loaded into R using [retrocombinator::parseSimulationOutput()]
#' @examples
#' \dontrun{
#' simulateEvolution(sequenceParams = mySequenceParams,
#'                   familyParams = myFamilyParams)
#' }
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
