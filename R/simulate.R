#' Run an entire simulation with flags
#' @export
simulate_with_flags_random <- function(
                                num_seq, seq_length,
                                point_mutation_model = "K80",
                                num_sensitive_posns = 10,
                                inactive_probability = 0.1,
                                num_jumps = 100, timestep = 1,
                                burst_probability = 0.1, burst_mean = 1,
                                max_active_copies = 100,
                                max_total_copies = 200,
                                recomb_mean = 1,
                                selection_threshold = 0,
                                fam_proportion = 1, fam_percentage = 100,
                                file_out,
                                num_out_tags = 100,
                                num_out_init = 100,
                                num_out_seqs = 10,
                                num_out_pair = 20,
                                to_randomise = TRUE, to_seed = FALSE,
                                seed = 0,
                                sequence_numbering = 0, family_numbering = 0)
{
  rcpp_simulate_with_flags_random(
                           num_seq, seq_length, point_mutation_model,
                           num_sensitive_posns, inactive_probability, num_jumps,
                           timestep, burst_probability, burst_mean,
                           max_active_copies, max_total_copies, recomb_mean,
                           selection_threshold, fam_proportion, fam_percentage,
                           file_out, num_out_tags, num_out_init, num_out_seqs,
                           num_out_pair, to_randomise, to_seed, seed,
                           sequence_numbering, family_numbering)
}

#' Run an entire simulation without flags
#' @export
simulate_without_flags_random <- function(
                                   num_seq, seq_length,
                                   point_mutation_model = "K80",
                                   num_jumps = 100, timestep = 1,
                                   burst_probability = 0.1, burst_mean = 1,
                                   max_active_copies = 100,
                                   recomb_mean = 1,
                                   file_out,
                                   num_out_tags = 100,
                                   num_out_init = 100,
                                   num_out_seqs = 10,
                                   num_out_pair = 20,
                                   to_randomise = TRUE,
                                   to_seed = FALSE,
                                   seed = 0,
                                   sequence_numbering = 0, family_numbering = 0)
{
  rcpp_simulate_without_flags_random(
                              num_seq, seq_length, point_mutation_model,
                              num_jumps, timestep, burst_probability,
                              burst_mean, max_active_copies, recomb_mean,
                              file_out, num_out_tags, num_out_init,
                              num_out_seqs, num_out_pair, to_randomise,
                              to_seed, seed, sequence_numbering,
                              family_numbering)
}

#' Run an entire simulation with flags
#' @export
simulate_with_flags_specified <- function(
                                init_seqs, init_seq_index = 0,
                                point_mutation_model = "K80",
                                num_sensitive_posns = 10,
                                inactive_probability = 0.1,
                                num_jumps = 100, timestep = 1,
                                burst_probability = 0.1, burst_mean = 1,
                                max_active_copies = 100,
                                max_total_copies = 200,
                                recomb_mean = 1,
                                selection_threshold = 0,
                                fam_proportion = 1, fam_percentage = 100,
                                file_out,
                                num_out_tags = 100,
                                num_out_init = 100,
                                num_out_seqs = 10,
                                num_out_pair = 20,
                                to_randomise = TRUE, to_seed = FALSE,
                                seed = 0,
                                sequence_numbering = 0, family_numbering = 0)
{
  rcpp_simulate_with_flags_specified(
                           init_seqs, init_seq_index, point_mutation_model,
                           num_sensitive_posns, inactive_probability, num_jumps,
                           timestep, burst_probability, burst_mean,
                           max_active_copies, max_total_copies, recomb_mean,
                           selection_threshold, fam_proportion, fam_percentage,
                           file_out, num_out_tags, num_out_init, num_out_seqs,
                           num_out_pair, to_randomise, to_seed, seed,
                           sequence_numbering, family_numbering)
}

#' Run an entire simulation without flags
#' @export
simulate_without_flags_specified <- function(
                                   init_seqs, init_seq_index = 0,
                                   point_mutation_model = "K80",
                                   num_jumps = 100, timestep = 1,
                                   burst_probability = 0.1, burst_mean = 1,
                                   max_active_copies = 100,
                                   recomb_mean = 1,
                                   file_out,
                                   num_out_tags = 100,
                                   num_out_init = 100,
                                   num_out_seqs = 10,
                                   num_out_pair = 20,
                                   to_randomise = TRUE,
                                   to_seed = FALSE,
                                   seed = 0,
                                   sequence_numbering = 0, family_numbering = 0)
{
  rcpp_simulate_without_flags_specified(
                              num_seq, seq_length, point_mutation_model,
                              num_jumps, timestep, burst_probability,
                              burst_mean, max_active_copies, recomb_mean,
                              file_out, num_out_tags, num_out_init,
                              num_out_seqs, num_out_pair, to_randomise,
                              to_seed, seed, sequence_numbering,
                              family_numbering)
}
