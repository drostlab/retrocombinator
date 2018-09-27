#' Run an entire simulation without flags
#' @export
simulate_without_flags <- function(num_seq, seq_length,
                                   point_mutation_model = "K80",
                                   num_jumps = 100, timestep = 1,
                                   burst_probability = 0.1, burst_mean = 1,
                                   max_active_copies = 100,
                                   recomb_mean = 1,
                                   file_out,
                                   num_out_tags = num_jumps,
                                   num_out_init = num_jumps,
                                   num_out_seqs = 20,
                                   num_out_pair = 10,
                                   to_randomise = TRUE,
                                   to_seed = FALSE,
                                   seed = 0,
                                   sequence_numbering = 0, family_numbering = 0)
{
  rcpp_simulate_without_flags(num_seq, seq_length, point_mutation_model,
                              num_jumps, timestep, burst_probability,
                              burst_mean, max_active_copies, recomb_mean,
                              file_out, num_out_tags, num_out_init,
                              num_out_seqs, num_out_pair, to_randomise,
                              to_seed, seed, sequence_numbering,
                              family_numbering)
}
