#include <Rcpp.h>

#include "simulation.h"

using namespace Rcpp;
using namespace retrocombinator;

// Refer to the documentation in simulation.h for the details
// This file is just to link the two functions

// [[Rcpp::export]]
void rcpp_simulate_without_flags_random(
        size_t num_seq, size_t seq_length,
        std::string point_mutation_model,
        size_t num_jumps, double timestep,
        double burst_probability, double burst_mean,
        size_t max_active_copies,
        double recomb_mean,
        std::string file_out,
        size_t num_out_tags, size_t num_out_init,
        size_t num_out_seqs, size_t num_out_pair,
        bool to_randomise, bool to_seed, size_t seed,
        size_t sequence_numbering, size_t family_numbering,
        bool logging)
{
    try
    {
        simulate_without_flags(
            num_seq, seq_length, point_mutation_model, num_jumps, timestep,
            burst_probability, burst_mean, max_active_copies, recomb_mean, file_out,
            num_out_tags, num_out_init, num_out_seqs, num_out_pair, to_randomise,
            to_seed, seed, sequence_numbering, family_numbering,
            logging);
    }
    catch (Exception e)
    {
        Rcpp::Rcerr << "EXCEPTION: " << e.what() << std::endl;
    }
}

// [[Rcpp::export]]
void rcpp_simulate_with_flags_random(
        size_t num_seq, size_t seq_length,
        std::string point_mutation_model,
        size_t num_sensitive_posns, double inactive_probability,
        size_t num_jumps, double timestep,
        double burst_probability, double burst_mean,
        size_t max_active_copies, size_t max_total_copies,
        double recomb_mean,
        double selection_threshold,
        double fam_proportion, double fam_percentage,
        std::string file_out,
        size_t num_out_tags, size_t num_out_init,
        size_t num_out_seqs, size_t num_out_pair,
        bool to_randomise, bool to_seed, size_t seed,
        size_t sequence_numbering, size_t family_numbering,
        bool logging)
{
    try
    {
        simulate_with_flags(
            num_seq, seq_length, point_mutation_model, num_sensitive_posns,
            inactive_probability, num_jumps, timestep, burst_probability,
            burst_mean, max_active_copies, max_total_copies, recomb_mean,
            selection_threshold, fam_proportion, fam_percentage, file_out,
            num_out_tags, num_out_init, num_out_seqs, num_out_pair, to_randomise,
            to_seed, seed, sequence_numbering, family_numbering,
            logging);
    }
    catch (Exception e)
    {
        Rcpp::Rcerr << "EXCEPTION: " << e.what() << std::endl;
    }
}

// [[Rcpp::export]]
void rcpp_simulate_without_flags_specified(
        std::vector<std::string> init_seqs, size_t init_seq_index,
        std::string point_mutation_model,
        size_t num_jumps, double timestep,
        double burst_probability, double burst_mean,
        size_t max_active_copies,
        double recomb_mean,
        std::string file_out,
        size_t num_out_tags, size_t num_out_init,
        size_t num_out_seqs, size_t num_out_pair,
        bool to_randomise, bool to_seed, size_t seed,
        size_t sequence_numbering, size_t family_numbering,
        bool logging)
{
    try
    {
        simulate_without_flags(
            init_seqs, init_seq_index, point_mutation_model, num_jumps, timestep,
            burst_probability, burst_mean, max_active_copies, recomb_mean, file_out,
            num_out_tags, num_out_init, num_out_seqs, num_out_pair, to_randomise,
            to_seed, seed, sequence_numbering, family_numbering,
            logging);
    }
    catch (Exception e)
    {
        Rcpp::Rcerr << "EXCEPTION: " << e.what() << std::endl;
    }
}

// [[Rcpp::export]]
void rcpp_simulate_with_flags_specified(
        std::vector<std::string> init_seqs, size_t init_seq_index,
        std::string point_mutation_model,
        size_t num_sensitive_posns, double inactive_probability,
        size_t num_jumps, double timestep,
        double burst_probability, double burst_mean,
        size_t max_active_copies, size_t max_total_copies,
        double recomb_mean,
        double selection_threshold,
        double fam_proportion, double fam_percentage,
        std::string file_out,
        size_t num_out_tags, size_t num_out_init,
        size_t num_out_seqs, size_t num_out_pair,
        bool to_randomise, bool to_seed, size_t seed,
        size_t sequence_numbering, size_t family_numbering,
        bool logging)
{
    try
    {
        simulate_with_flags(
            init_seqs, init_seq_index, point_mutation_model, num_sensitive_posns,
            inactive_probability, num_jumps, timestep, burst_probability,
            burst_mean, max_active_copies, max_total_copies, recomb_mean,
            selection_threshold, fam_proportion, fam_percentage, file_out,
            num_out_tags, num_out_init, num_out_seqs, num_out_pair, to_randomise,
            to_seed, seed, sequence_numbering, family_numbering,
            logging);
    }
    catch (Exception e)
    {
        Rcpp::Rcerr << "EXCEPTION: " << e.what() << std::endl;
    }
}

