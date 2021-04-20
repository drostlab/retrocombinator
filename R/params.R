#' Is x a SequenceParams object?
#' @export
is.SequenceParams  <- function(x) inherits(x, 'SequenceParams')

#' Create SequenceParams object
#' @param num_initial_copies The initial number of sequences to consider
#' @param seq_length The number of nucleotides in each of the sequences in the
#' simulation
#' @param seq_filename A path to a sequence to be used as initial sequence
#' @export
SequenceParams <- function(num_initial_copies = 100,
                           seq_length = 500,
                           seq_filename = NULL) {
  if(!is.null(seq_filename)) {
    stop('Not yet implemented reading of sequence file')
  }
  stopifnot('num_initial_copies must be a positive integer' =
            isPositiveNumber(num_initial_copies))
  stopifnot('seq_length must be a positive integer' =
            isPositiveNumber(seq_length))

  params <- list(num_initial_copies = num_initial_copies,
                 seq_length = seq_length)
  class(params) <- 'SequenceParams'
  return(params)
}

#' Is x a SimulationParams object?
#' @export
is.SimulationParams  <- function(x) inherits(x, 'SimulationParms')

#' Create SimulationParams object
#' @param num_jumps How many steps we have in our simulation
#' @param timestep How much time passes in one jump (unit: millions of years)
#' @param max_active_copies The total number of sequences that have the ability
#' to burst that we allow in a simulation (if the number ever exceeds this
#' threshold, the simulation prunes the set of sequences by randomly choosing
#' the ones that live on)
#' @export
SimulationParams <- function(num_jumps = 20,
                             timestep = 1,
                             max_active_copies = 500) {
  stopifnot('num_jumps must be a positive integer' =
            isPositiveNumber(num_jumps))
  stopifnot('timestep must be a positive number' =
            isPositiveNumber(timestep))
  stopifnot('max_active_copies must be a positive integer' =
            isPositiveNumber(max_active_copies))

  params <- list(num_jumps = num_jumps,
                 timestep = timestep,
                 max_active_copies = max_active_copies)
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
  stopifnot('point mutation model name is invalid' =
            model %in% c('JC69', 'K80', 'F81', 'HKY85', 'TN93', 'GTR'))

  params <- list(model = model)
  class(params) <- 'MutationParams'
  return(params)
}

#' Is x a FlagParams object?
#' @export
is.FlagParams  <- function(x) inherits(x, 'FlagParams')

#' Create FlagParams object
#' @param length_critical_region How many positions (chosen randomly) in the
#' sequence are essential for the sequence to remain active (with the potential
#' to burst)? If the sequence experiences mutations in these areas, it loses its
#' activity with some probability
#' @param prob_inactive_when_mutated What is the probability that a mutation in
#' the critical region causes the sequence to lose its bursting potential?
#' @param max_inactive_copies The total number of inactive sequences that we
#' allow in our simulation (if the number ever exceeds this threshold, the
#' simulation prunes the set of sequences by randomly choosing the ones that
#' live on)
#' @export
FlagParams <- function(length_critial_region = 10,
                       prob_inactive_when_mutated = 0.001,
                       max_inactive_copies = 500) {
  stopifnot('length_critial_region must be a positive integer' =
            isPositiveNumber(length_critial_region))
  stopifnot('prob_inactive_when_mutated must be a valid number between 0 and 1' =
            isProbability(prob_inactive_when_mutated))
  stopifnot('max_inactive_copies must be a positive integer' =
            isPositiveNumber(max_inactive_copies))

  params <- list(length_critial_region = length_critial_region,
                 prob_inactive_when_mutated = prob_inactive_when_mutated,
                 max_inactive_copies = max_inactive_copies)
  class(params) <- 'FlagParams'
  return(params)
}

#' Is x a BurstParams object?
#' @export
is.BurstParams  <- function(x) inherits(x, 'BurstParams')

#' Create BurstParams object
#' @param burst_probability Probability that an active sequence bursts in one
#' timestep
#' @param burst_mean The Poisson mean for the distribution that specifies how
#' many new sequences an active sequence will create during bursting
#' @param recomb_mean The expected number of template switches during
#' recombination between two sequences (chosen from a Poisson distribution with
#' this as its mean).
#' @param recomb_similarity TODO
#' @export
BurstParams <- function(burst_probability = 0.1,
                        burst_mean = 1,
                        recomb_mean = 1.5,
                        recomb_similarity = 0.85) {
  stopifnot('burst_probability must be a valid number between 0 and 1' =
            isProbability(burst_probability))
  stopifnot('burst_mean must be a positive number' =
            isPositiveNumber(burst_mean))
  stopifnot('recomb_mean must be a positive number' =
            isPositiveNumber(recomb_mean))
  stopifnot('recomb_similarity must be a valid number between 0 and 1' =
            isProbability(recomb_similarity))

  params <- list(burst_probability = burst_probability,
                 burst_mean = burst_mean,
                 recomb_mean = recomb_mean,
                 recomb_similarity = recomb_similarity)
  class(params) <- 'BurstParams'
  return(params)
}

#' Is x a SpeciationParams object?
#' @export
is.SpeciationParams  <- function(x) inherits(x, 'SpeciationParams')

#' Create SpeciationParams object
#' @param selection_threshold What sequence similarity percentage to the
#' original sequence we wish to maintain (distant sequences are dropped over the
#' course of the simulation)
#' @param species_similarity If this proportion of the overall sequence similarity
#' matrix falls below a certain percentage (species_coehrence), then we split the
#' current species into two species, and allow for recombination only within
#' species.
#' @param species_coherence Refer to `species_similarity`
#' @export
SpeciationParams <- function(selection_threshold = 0.5,
                             species_similarity = 0.7,
                             species_coherence = 0.5) {
  stopifnot('selection_threshold must be a valid number between 0 and 1' =
            isProbability(selection_threshold))
  stopifnot('species_similarity must be a valid number between 0 and 1' =
            isProbability(species_similarity))
  stopifnot('species_coherence must be a valid number between 0 and 1' =
            isProbability(species_coherence))

  params <- list(selection_threshold = selection_threshold,
                 species_similarity = species_similarity,
                 species_coherence = species_coherence)
  class(params) <- 'SpeciationParams'
  return(params)
}

#' Is x a OutputParams object?
#' @export
is.OutputParams  <- function(x) inherits(x, 'OutputParams')

#' Create OutputParams object
#' @param file_out Where should the results of the simulation be saved? (This
#' can be parsed by input_file)
#' @param num_out_seqs How many times across the simulation will we output the
#' raw sequences themselves
#' @param num_out_init How many times across the simulation will we output the
#' distance of each sequence to the initial sequence
#' @param num_out_pair How many times across the simulation will we output the
#' pairwise distance between all pairs of sequences
#' @param num_out_species How many times across the simulation will we output
#' the tags (unique identifiers) of the sequences and their species
#' @export
OutputParams <- function(file_out = 'output.out',
                         num_out_seqs = 2,
                         num_out_init = 10,
                         num_out_pair = 10,
                         num_out_species = 10) {
  stopifnot('num_out_seqs must be a positive integer' =
            isPositiveNumber(num_out_seqs))
  stopifnot('num_out_init must be a positive integer' =
            isPositiveNumber(num_out_init))
  stopifnot('num_out_pair must be a positive integer' =
            isPositiveNumber(num_out_pair))
  stopifnot('num_out_species must be a positive integer' =
            isPositiveNumber(num_out_species))

  params <- list(file_out = file_out,
                 num_out_seqs = num_out_seqs,
                 num_out_init = num_out_init,
                 num_out_pair = num_out_pair,
                 num_out_species = num_out_species)
  class(params) <- 'OutputParams'
  return(params)
}

#' Is x a SeedParams object?
#' @export
is.SeedParams  <- function(x) inherits(x, 'SeedParams')

#' Create SeedParams object
#' @param to_randomise Should this simulation be run with a random seed to begin
#' with? (Based on system time)
#' @param to_seed Should this sequence be run with a specific initial seed? If
#' so, then the seed is specified by the parameter sseed
#' @param seed Refer to documentation of to_seed
#' @export
SeedParams <- function(to_randomise = FALSE,
                       to_seed = TRUE,
                       seed = 0) {
  stopifnot('to_randomise must be a logical' =
            is.logical(to_randomise))
  stopifnot('to_seed must be a logical' =
            is.logical(to_seed))
  stopifnot('seed must be a number' =
            is.numeric(seed))

  params <- list(to_randomise = to_randomise,
                 to_seed = to_seed,
                 seed = seed)
  class(params) <- 'SeedParams'
  return(params)
}
