# TODO: Check that Poisson mean can never be 0
# TODO: Check that integers are actually integers

#' Is x a SequenceParams object?
#' @param x An arbitrary object
#' @return A logical, TRUE if \code{x} is a SequenceParams object, and FALSE otherwise
#' @examples
#' is.SequenceParams(SequenceParams()) # TRUE
#' is.SequenceParams(data.frame()) # FALSE
#' @export
is.SequenceParams  <- function(x) inherits(x, 'SequenceParams')

#' Create SequenceParams object
#' @param numInitialCopies The initial number of copies of a given sequence to consider
#' @param sequenceLength The number of nucleotides in each of the sequences in the
#' simulation
#' @param initialSequence An initial sequence (ignores sequenceLength if this is
#' specified)
#' @return A bundling of the parameters given to it as a SequenceParams object
#' @examples
#' sequenceParams <- SequenceParams(numInitialCopies = 40)
#' @export
SequenceParams <- function(numInitialCopies = 20,
                           sequenceLength = 5000,
                           initialSequence = NULL) {

  stopifnot("numInitialCopies must be a positive integer" =
            isPositiveNumber(numInitialCopies))
  params <- list(numInitialCopies = numInitialCopies)

  if(!is.null(initialSequence)) {
    initialSequence <- initialSequence[[1]]
    stopifnot("initialSequence must be a character" =
              is.character(initialSequence))
    stopifnot("initialSequence must be a character" =
              is.character(initialSequence))

    chars <- unlist(strsplit(initialSequence, ""))
    if(!all(chars %in% c("A", "T", "G", "C"))) {
      warning("String not comprising of only ATGC characters, ignoring other characters")
      chars_fixed <- chars[chars %in% c("A", "T", "G", "C")]
      initialSequence <- paste0(chars_fixed, collapse = "")
    }

    params$initialSequence <- initialSequence
    params$sequenceLength <- nchar(initialSequence)
  }
  else {
    stopifnot("sequenceLength must be a positive integer if initialSequence is not specified" =
              isPositiveNumber(sequenceLength))
    params$initialSequence <- ""
    params$sequenceLength <- sequenceLength
  }

  class(params) <- 'SequenceParams'
  return(params)
}

#' Is x an ActivityParams object?
#' @param x An arbitrary object
#' @return A logical, TRUE if \code{x} is a ActivityParams object, and FALSE otherwise
#' @examples
#' is.ActivityParams(ActivityParams()) # TRUE
#' is.ActivityParams(data.frame()) # FALSE
#' @export
is.ActivityParams  <- function(x) inherits(x, 'ActivityParams')

#' Create ActivityParams object
#' @param lengthCriticalRegion Sequence length (number of nucleotides) of the critical region of a retrotransposon
#' @param probInactiveWhenMutated The probability that a singe point mutation to the critical region causes a sequence to become inactive
#' @return A bundling of the parameters given to it as a ActivityParams object
#' @examples
#' activityParams <- ActivityParams(lengthCriticalRegion = 40)
#' @export
ActivityParams <- function(lengthCriticalRegion = 10,
                           probInactiveWhenMutated = 0.01) {

  stopifnot("lengthCriticalRegion must be a positive integer" =
            isPositiveNumber(lengthCriticalRegion))
  stopifnot("probInactiveWhenMutated must be a valid number between 0 and 1" =
            isProbability(probInactiveWhenMutated))
  params <- list(lengthCriticalRegion = lengthCriticalRegion,
                 probInactiveWhenMutated = probInactiveWhenMutated)

  class(params) <- 'ActivityParams'
  return(params)
}

#' Is x a MutationParams object?
#' @param x An arbitrary object
#' @return A logical, TRUE if \code{x} is a MutationParams object, and FALSE otherwise
#' @examples
#' is.MutationParams(MutationParams()) # TRUE
#' is.MutationParams(data.frame()) # FALSE
#' @export
is.MutationParams  <- function(x) inherits(x, 'MutationParams')

#' Create MutationParams object
#' @param model Which point mutation/substitution model will be used to modify
#' the sequences during the simulation? Options are "JC69" (Jules and Cantor
#' 1969), "K80" (Kimura 1980), "F81" (Felsenstein 1981), "HKY85" (Hasegawa,
#' Kishino and Yano, 1985), "TN93" (Timura and Nei 1993), or "GTR" (General Time
#' Reversible Model, Tavaré 1986), note however that "GTR" is currently
#' unsupported.
#' @return A bundling of the parameters given to it as a MutationParams object
#' @examples
#' mutationParams <- MutationParams(model = 'F81')
#' @export
MutationParams <- function(model = 'K80') {
  stopifnot("point mutation model name is invalid" =
            model %in% c('JC69', 'K80', 'F81', 'HKY85', 'TN93', 'GTR'))

  params <- list(model = model)
  class(params) <- 'MutationParams'
  return(params)
}

#' Is x a BurstParams object?
#' @param x An arbitrary object
#' @return A logical, TRUE if \code{x} is a BurstParams object, and FALSE otherwise
#' @examples
#' is.BurstParams(BurstParams()) # TRUE
#' is.BurstParams(data.frame()) # FALSE
#' @export
is.BurstParams  <- function(x) inherits(x, 'BurstParams')

#' Create BurstParams object
#' @param burstProbability The probability that an active retrotransposon will increase in copy number during a time jump of one timestep
#' @param burstMean The Poisson mean for the distribution that specifies how many new sequences an active sequence will create during bursting
#' @param maxTotalCopies The largest population size of sequences to keep track of (if this is exceeded, sequences are randomly discarded to simulate death)
#' @return A bundling of the parameters given to it as a BurstParams object
#' @examples
#' burstParams <- BurstParams(burstMean = 2)
#' @export
BurstParams <- function(burstProbability = 0.1,
                        burstMean = 1,
                        maxTotalCopies = 50) {
  stopifnot("burstProbability must be a valid number between 0 and 1" =
            isProbability(burstProbability))
  stopifnot("burstMean must be a positive number" =
            isPositiveNumber(burstMean))
  stopifnot("maxTotalCopies must be a positive number" =
            isPositiveNumber(maxTotalCopies))

  params <- list(burstProbability = burstProbability,
                 burstMean = burstMean,
                 maxTotalCopies = maxTotalCopies)
  class(params) <- 'BurstParams'
  return(params)
}

#' Is x a RecombParams object?
#' @param x An arbitrary object
#' @return A logical, TRUE if \code{x} is a RecombParams object, and FALSE otherwise
#' @examples
#' is.RecombParams(RecombParams()) # TRUE
#' is.RecombParams(data.frame()) # FALSE
#' @export
is.RecombParams  <- function(x) inherits(x, 'RecombParams')

#' Create RecombParams object
#' @param recombMean The expected number of template switches during recombination between two sequences (chosen from a Poisson distribution with this as its mean)
#' @param recombSimilarity How similar does an active sequence have to be with another sequence for them to be allowed to be recombine during transposition?
#' @return A bundling of the parameters given to it as a RecombParams object
#' @examples
#' recombParams <- RecombParams(recombMean = 2)
#' @export
RecombParams <- function(recombMean = 1.5,
                         recombSimilarity = 0.80) {
  stopifnot("recombMean must be a semi-positive number" =
            isSemiPositiveNumber(recombMean))
  stopifnot("recombSimilarity must be a valid number between 0 and 1" =
            isProbability(recombSimilarity))

  params <- list(recombMean = recombMean,
                 recombSimilarity = recombSimilarity)
  class(params) <- 'RecombParams'
  return(params)
}

#' Is x a SelectionParams object?
#' @param x An arbitrary object
#' @return A logical, TRUE if \code{x} is a SelectionParams object, and FALSE otherwise
#' @examples
#' is.SelectionParams(SelectionParams()) # TRUE
#' is.SelectionParams(data.frame()) # FALSE
#' @export
is.SelectionParams  <- function(x) inherits(x, 'SelectionParams')

#' Create SelectionParams object
#' @param selectionThreshold What sequence similarity to the original sequence do we wish to maintain? Sequences that diverge beyond this similarity level are dropped over the course of simulation
#' @return A bundling of the parameters given to it as a SelectionParams object
#' @examples
#' selectionParams <- SelectionParams(selectionThreshold = 0.5)
#' @export
SelectionParams <- function(selectionThreshold = 0.3) {
  stopifnot("selectionThreshold must be a valid number between 0 and 1" =
            isProbability(selectionThreshold))

  params <- list(selectionThreshold = selectionThreshold)
  class(params) <- 'SelectionParams'
  return(params)
}

#' Is x a FamilyParams object?
#' @param x An arbitrary object
#' @return A logical, TRUE if \code{x} is a FamilyParams object, and FALSE otherwise
#' @examples
#' is.FamilyParams(FamilyParams()) # TRUE
#' is.FamilyParams(data.frame()) # FALSE
#' @export
is.FamilyParams  <- function(x) inherits(x, 'FamilyParams')

#' Create FamilyParams object
#' @param familyCoherence What sequence similarity do two sequences have to be to each other for them to be considered to be of the same family?
#' @param maxFamilyRepresentatives How many family representatives to keep track of during the simulation?
#' @return A bundling of the parameters given to it as a FamilyParams object
#' @examples
#' familyParams <- FamilyParams(familyCoherence = 0.775)
#' @export
FamilyParams <- function(familyCoherence = 0.70,
                         maxFamilyRepresentatives = 20) {
  stopifnot("familyCoherence must be a valid number between 0 and 1" =
            isProbability(familyCoherence))
  stopifnot("maxFamilyRepresentatives must be a positive number" =
            isPositiveNumber(maxFamilyRepresentatives))

  params <- list(familyCoherence = familyCoherence,
                 maxFamilyRepresentatives = maxFamilyRepresentatives)
  class(params) <- 'FamilyParams'
  return(params)
}

#' Is x a SimulationParams object?
#' @param x An arbitrary object
#' @return A logical, TRUE if \code{x} is a SimulationParams object, and FALSE otherwise
#' @examples
#' is.SimulationParams(SimulationParams()) # TRUE
#' is.SimulationParams(data.frame()) # FALSE
#' @export
is.SimulationParams  <- function(x) inherits(x, 'SimulationParms')

#' Create SimulationParams object
#' @param numSteps How many steps we have in our simulation
#' @param timePerStep How much time passes in one jump (unit: millions of years)
#' @return A bundling of the parameters given to it as a SimulationParams object
#' @examples
#' simulationParams <- SimulationParams(numSteps = 40)
#' @export
SimulationParams <- function(numSteps = 20,
                             timePerStep = 1) {
  stopifnot("numSteps must be a positive integer" =
            isPositiveNumber(numSteps))
  stopifnot("timePerStep must be a positive number" =
            isPositiveNumber(timePerStep))

  params <- list(numSteps = numSteps,
                 timePerStep = timePerStep)
  class(params) <- 'SimulationParams'
  return(params)
}


#' Is x a OutputParams object?
#' @param x An arbitrary object
#' @return A logical, TRUE if \code{x} is a OutputParams object, and FALSE otherwise
#' @examples
#' is.OutputParams(OutputParams()) # TRUE
#' is.OutputParams(data.frame()) # FALSE
#' @export
is.OutputParams  <- function(x) inherits(x, 'OutputParams')

#' Create OutputParams object
#' @param outputFilename Where should the results of the simulation be saved? (This
#' can be parsed by input_file)
#' @param outputNumInitialDistance How many times across the simulation will we output the
#' distance of each sequence to the initial sequence
#' @param outputNumPairwiseDistance How many times across the simulation will we output the
#' pairwise distance between all pairs of sequences
#' @param outputNumFamilyLabels How many times across the simulation will we output
#' the representative sequences for each family?
#' @param outputNumFamilyMatrix How many times across the simulation will we output
#' the pairwise distances between family representatives?
#' @param outputMinSimilarity What is the minimum similarity between two sequences we should report on?
#' @return A bundling of the parameters given to it as a SimulationParams object
#' @examples
#' outputParams <- OutputParams(outputFilename = 'myOutputFilename.out')
#' @export
OutputParams <- function(outputFilename = 'simulationOutput.out',
                         outputNumInitialDistance = 10,
                         outputNumPairwiseDistance = 10,
                         outputNumFamilyLabels = 10,
                         outputNumFamilyMatrix = 10,
                         outputMinSimilarity = 0.5) {
  stopifnot("outputNumInitialDistance must be a positive integer" =
            isPositiveNumber(outputNumInitialDistance))
  stopifnot("outputNumPairwiseDistance must be a positive integer" =
            isPositiveNumber(outputNumPairwiseDistance))
  stopifnot("outputNumFamilyLabels must be a positive integer" =
            isPositiveNumber(outputNumFamilyLabels))
  stopifnot("outputNumFamilyMatrix must be a positive integer" =
            isPositiveNumber(outputNumFamilyMatrix))
  stopifnot("outputMinSimilarity must be a number between 0 and 1" =
            isProbability(outputMinSimilarity)
  )

  params <- list(outputFilename = outputFilename,
                 outputNumInitialDistance = outputNumInitialDistance,
                 outputNumPairwiseDistance = outputNumPairwiseDistance,
                 outputNumFamilyLabels = outputNumFamilyLabels,
                 outputNumFamilyMatrix = outputNumFamilyMatrix,
                 outputMinSimilarity = outputMinSimilarity)
  class(params) <- 'OutputParams'
  return(params)
}

#' Is x a SeedParams object?
#' @param x An arbitrary object
#' @return A logical, TRUE if \code{x} is a SeedParams object, and FALSE otherwise
#' @examples
#' is.SeedParams(SeedParams()) # TRUE
#' is.SeedParams(data.frame()) # FALSE
#' @export
is.SeedParams  <- function(x) inherits(x, 'SeedParams')

#' Create SeedParams object
#' @param toSeed Should this sequence be run with a specific initial seed? If
#' so, then the seed is specified by the parameter seedForRNG; else a seed
#' based on system time is used
#' @param seedForRNG seed to a (pseudo)random number generator, only used if `toSeed` is TRUE
#' @return A bundling of the parameters given to it as a SeedParams object
#' @examples
#' seedParams <- SeedParams(toSeed = FALSE)
#' @export
SeedParams <- function(toSeed = TRUE,
                       seedForRNG = 0) {

  stopifnot("toSeed must be a logical" = is.logical(toSeed))
  if (toSeed) {
    stopifnot("seedForRNG must be a number" = is.numeric(seedForRNG))
  }

  params <- list(toSeed = toSeed, seedForRNG = seedForRNG)
  class(params) <- 'SeedParams'
  return(params)
}
