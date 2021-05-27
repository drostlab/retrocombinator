#' Is x a SequenceParams object?
#' @export
is.SequenceParams  <- function(x) inherits(x, 'SequenceParams')

#' Create SequenceParams object
#' @param numInitialCopies The initial number of copies of a given sequence to consider
#' @param sequenceLength The number of nucleotides in each of the sequences in the
#' simulation
#' @param initialSequence An initial sequence (ignores sequenceLength if this is
#' specified)
#' @export
SequenceParams <- function(numInitialCopies = 20,
                           sequenceLength = 500,
                           initialSequence = NULL) {

  stopifnot("numInitialCopies must be a positive integer" =
            isPositiveNumber(numInitialCopies))
  params <- list(numInitialCopies = numInitialCopies)

  if(!is.null(initialSequence)) {
    stopifnot("initialSequence must be a character" =
              is.character(initialSequence))
    stopifnot("initialSequence must be a character" =
              is.character(initialSequence))
    params$initialSequence <- initialSequence
  }
  else {
    stopifnot("sequenceLength must be a positive integer if initialSequence is not specified" =
              isPositiveNumber(sequenceLength))
    params$sequenceLength <- sequenceLength
  }
  class(params) <- 'SequenceParams'
  return(params)
}

#' Is x a SimulationParams object?
#' @export
is.SimulationParams  <- function(x) inherits(x, 'SimulationParms')

#' Create SimulationParams object
#' @param numSteps How many steps we have in our simulation
#' @param timestep How much time passes in one jump (unit: millions of years)
#' @param maxActiveCopies The total number of sequences that have the ability
#' to burst that we allow in a simulation (if the number ever exceeds this
#' threshold, the simulation prunes the set of sequences by randomly choosing
#' the ones that live on)
#' @export
SimulationParams <- function(numSteps = 20,
                             timestep = 1,
                             maxActiveCopies = 500) {
  stopifnot("numSteps must be a positive integer" =
            isPositiveNumber(numSteps))
  stopifnot("timestep must be a positive number" =
            isPositiveNumber(timestep))
  stopifnot("maxActiveCopies must be a positive integer" =
            isPositiveNumber(maxActiveCopies))

  params <- list(numSteps = numSteps,
                 timestep = timestep,
                 maxActiveCopies = maxActiveCopies)
  class(params) <- 'SimulationParams'
  return(params)
}

#' Is x a MutationParams object?
#' @export
is.MutationParams  <- function(x) inherits(x, 'MutationParams')

#' Create MutationParams object
#' @param model Which point mutation/substitution model will be used to modify
#' the sequences during the simulation? Options are "JC69" (Jules and Cantor
#' 1969), "K80" (Kimura 1980), "F81" (Felsenstein 1981), "HKY85" (Hasegawa,
#' Kishino and Yano, 1985), "TN93" (Timura and Nei 1993), or "GTR" (General Time
#' Reversible Model, Tavaré 1986).
#' @export
MutationParams <- function(model = 'K80') {
  stopifnot("point mutation model name is invalid" =
            model %in% c('JC69', 'K80', 'F81', 'HKY85', 'TN93', 'GTR'))

  params <- list(model = model)
  class(params) <- 'MutationParams'
  return(params)
}

#' Is x a FlagParams object?
#' @export
is.FlagParams  <- function(x) inherits(x, 'FlagParams')

#' Create FlagParams object
#' @param lengthCriticalRegion How many positions (chosen randomly) in the
#' sequence are essential for the sequence to remain active (with the potential
#' to burst)? If the sequence experiences mutations in these areas, it loses its
#' activity with some probability
#' @param probInactiveWhenMutated What is the probability that a mutation in
#' the critical region causes the sequence to lose its bursting potential?
#' @param maxInactiveCopies The total number of inactive sequences that we
#' allow in our simulation (if the number ever exceeds this threshold, the
#' simulation prunes the set of sequences by randomly choosing the ones that
#' live on)
#' @export
FlagParams <- function(lengthCriticalRegion = 10,
                       probInactiveWhenMutated = 0.001,
                       maxInactiveCopies = 500) {
  stopifnot("lengthCriticalRegion must be a positive integer" =
            isPositiveNumber(lengthCriticalRegion))
  stopifnot("probInactiveWhenMutated must be a valid number between 0 and 1" =
            isProbability(probInactiveWhenMutated))
  stopifnot("maxInactiveCopies must be a positive integer" =
            isPositiveNumber(maxInactiveCopies))

  params <- list(lengthCriticalRegion = lengthCriticalRegion,
                 probInactiveWhenMutated = probInactiveWhenMutated,
                 maxInactiveCopies = maxInactiveCopies)
  class(params) <- 'FlagParams'
  return(params)
}

#' Is x a BurstParams object?
#' @export
is.BurstParams  <- function(x) inherits(x, 'BurstParams')

#' Create BurstParams object
#' @param burstProbability Probability that an active sequence bursts in one
#' timestep
#' @param burstMean The Poisson mean for the distribution that specifies how
#' many new sequences an active sequence will create during bursting
#' @param recombMean The expected number of template switches during
#' recombination between two sequences (chosen from a Poisson distribution with
#' this as its mean).
#' @param recombSimilarity TODO
#' @export
BurstParams <- function(burstProbability = 0.1,
                        burstMean = 1,
                        recombMean = 1.5,
                        recombSimilarity = 0.85) {
  stopifnot("burstProbability must be a valid number between 0 and 1" =
            isProbability(burstProbability))
  stopifnot("burstMean must be a positive number" =
            isPositiveNumber(burstMean))
  stopifnot("recombMean must be a positive number" =
            isPositiveNumber(recombMean))
  stopifnot("recombSimilarity must be a valid number between 0 and 1" =
            isProbability(recombSimilarity))

  params <- list(burstProbability = burstProbability,
                 burstMean = burstMean,
                 recombMean = recombMean,
                 recombSimilarity = recombSimilarity)
  class(params) <- 'BurstParams'
  return(params)
}

#' Is x a SpeciationParams object?
#' @export
is.SpeciationParams  <- function(x) inherits(x, 'SpeciationParams')

#' Create SpeciationParams object
#' @param selectionThreshold What sequence similarity percentage to the
#' original sequence we wish to maintain (distant sequences are dropped over the
#' course of the simulation)
#' @param speciesSimilarity If this proportion of the overall sequence similarity
#' matrix falls below a certain percentage (species_coehrence), then we split the
#' current species into two species, and allow for recombination only within
#' species.
#' @param speciesCoherence Refer to `speciesSimilarity`
#' @export
SpeciationParams <- function(selectionThreshold = 0.5,
                             speciesSimilarity = 0.7,
                             speciesCoherence = 0.5) {
  stopifnot("selectionThreshold must be a valid number between 0 and 1" =
            isProbability(selectionThreshold))
  stopifnot("speciesSimilarity must be a valid number between 0 and 1" =
            isProbability(speciesSimilarity))
  stopifnot("speciesCoherence must be a valid number between 0 and 1" =
            isProbability(speciesCoherence))

  params <- list(selectionThreshold = selectionThreshold,
                 speciesSimilarity = speciesSimilarity,
                 speciesCoherence = speciesCoherence)
  class(params) <- 'SpeciationParams'
  return(params)
}

#' Is x a OutputParams object?
#' @export
is.OutputParams  <- function(x) inherits(x, 'OutputParams')

#' Create OutputParams object
#' @param outputFilename Where should the results of the simulation be saved? (This
#' can be parsed by input_file)
#' @param outputNumRawSequence How many times across the simulation will we output the
#' raw sequences themselves
#' @param outputNumInitialDistance How many times across the simulation will we output the
#' distance of each sequence to the initial sequence
#' @param outputNumPairwiseDistance How many times across the simulation will we output the
#' pairwise distance between all pairs of sequences
#' @param outputNumSpeciesTags How many times across the simulation will we output
#' the tags (unique identifiers) of the sequences and their species
#' @export
OutputParams <- function(outputFilename = 'simulationOutput.out',
                         outputNumRawSequence = 2,
                         outputNumInitialDistance = 10,
                         outputNumPairwiseDistance = 10,
                         outputNumSpeciesTags = 10) {
  stopifnot("outputNumRawSequence must be a positive integer" =
            isPositiveNumber(outputNumRawSequence))
  stopifnot("outputNumInitialDistance must be a positive integer" =
            isPositiveNumber(outputNumInitialDistance))
  stopifnot("outputNumPairwiseDistance must be a positive integer" =
            isPositiveNumber(outputNumPairwiseDistance))
  stopifnot("outputNumSpeciesTags must be a positive integer" =
            isPositiveNumber(outputNumSpeciesTags))

  params <- list(outputFilename = outputFilename,
                 outputNumRawSequence = outputNumRawSequence,
                 outputNumInitialDistance = outputNumInitialDistance,
                 outputNumPairwiseDistance = outputNumPairwiseDistance,
                 outputNumSpeciesTags = outputNumSpeciesTags)
  class(params) <- 'OutputParams'
  return(params)
}

#' Is x a SeedParams object?
#' @export
is.SeedParams  <- function(x) inherits(x, 'SeedParams')

#' Create SeedParams object
#' @param toSeed Should this sequence be run with a specific initial seed? If
#' so, then the seed is specified by the parameter seedForRandom; else a seed
#' based on system time is used
#' @param seedForRandom seed to a (pseudo)random number generator, only used if `toSeed` is TRUE
#' @export
SeedParams <- function(toSeed = TRUE,
                       seedForRandom = 0) {

  stopifnot("toSeed must be a logical" = is.logical(toSeed))
  if (toSeed) {
    stopifnot("seedForRandom must be a number" = is.numeric(seedForRandom))
  }

  params <- list(toSeed = toSeed, seedForRandom = seedForRandom)
  class(params) <- 'SeedParams'
  return(params)
}
