#' Run an entire simulation with flags
#' @useDynLib retrocombinator, .registration = TRUE
#' @importFrom Rcpp sourceCpp
#' @export
simulate <- function(sequenceParams = SequenceParams(),
                     simulationParams = SimulationParams(),
                     mutationParams = MutationParams(),
                     flagParams = FlagParams(),
                     burstParams = BurstParams(),
                     speciationParams = SpeciationParams(),
                     outputParams = OutputParams(),
                     seedParams = SeedParams())
{
  num_seq <- sequenceParams$num_initial_copies
  seq_length <- sequenceParams$seq_length
  num_jumps <- simulationParams$num_jumps
  timestep <- simulationParams$timestep
  max_active_copies <- simulationParams$max_active_copies
  model <- mutationParams$model
  length_critial_region <- flagParams$length_critial_region
  prob_inactive_when_mutated <- flagParams$prob_inactive_when_mutated
  max_inactive_copies <- flagParams$max_inactive_copies
  burst_probability <- burstParams$burst_probability
  burst_mean <- burstParams$burst_mean
  recomb_mean <- burstParams$recomb_mean
  recomb_similarity <- burstParams$recomb_similarity # TODO: Use this
  selection_threshold <- speciationParams$selection_threshold
  species_similarity <- speciationParams$species_similarity
  species_coherence <- speciationParams$species_coherence
  file_out <- outputParams$file_out
  num_out_seqs <- outputParams$num_out_seqs
  num_out_init <- outputParams$num_out_init
  num_out_pair <- outputParams$num_out_pair
  num_out_species <- outputParams$num_out_species
  to_randomise <- seedParams$to_randomise
  to_seed <- seedParams$to_seed
  seed <- seedParams$seed

  if (prob_inactive_when_mutated > 0 && length_critial_region >= 1) {
    rcpp_simulate_with_flags_random(
      num_seq, seq_length,
      model,
      length_critial_region, prob_inactive_when_mutated,
      num_jumps, timestep,
      burst_probability, burst_mean,
      max_active_copies, max_active_copies + max_inactive_copies,
      recomb_mean,
      selection_threshold, species_similarity, species_coherence,
      file_out, num_out_species, num_out_init, num_out_seqs, num_out_pair,
      to_randomise, to_seed, seed,
      0, 0,
      FALSE
    )
  } else {
    rcpp_simulate_without_flags_random(
      num_seq, seq_length,
      model,
      num_jumps, timestep,
      burst_probability, burst_mean,
      max_active_copies,
      recomb_mean,
      file_out, num_out_species, num_out_init, num_out_seqs, num_out_pair,
      to_randomise, to_seed, seed,
      0, 0,
      FALSE
    )
  }
}
