/**
 * @file
 *
 * \brief
 *
 */
#ifndef SIMULATION_H
#define SIMULATION_H

#include "evolution_without_flags.h"
#include "evolution_with_flags.h"

namespace rcombinator
{
    /** Sets up and runs a simulation without flags.
     *  Takes a specified set of initial sequences.
     */
    void simulate_without_flags(
            std::vector<std::string> init_seqs, size_type init_seq_index,
            std::string point_mutation_model,
            size_type num_jumps, double timestep,
            double burst_probability, double burst_mean,
            size_type max_active_copies,
            double recomb_mean,
            std::string file_out,
            size_type num_out_tags, size_type num_out_init,
            size_type num_out_seqs, size_type num_out_pair,
            bool to_randomise, bool to_seed, size_type seed,
            size_type sequence_numbering, size_type family_numbering);

    /** Sets up and runs a simulation with flags.
     *  Takes a specified set of initial sequences.
     */
    void simulate_with_flags(
            std::vector<std::string> init_seqs, size_type init_seq_index,
            std::string point_mutation_model,
            size_type num_sensitive_posns, double inactive_probability,
            size_type num_jumps, double timestep,
            double burst_probability, double burst_mean,
            size_type max_active_copies, size_type max_total_copies,
            double recomb_mean,
            double selection_threshold,
            double fam_proportion, double fam_percentage,
            std::string file_out,
            size_type num_out_tags, size_type num_out_init,
            size_type num_out_seqs, size_type num_out_pair,
            bool to_randomise, bool to_seed, size_type seed,
            size_type sequence_numbering, size_type family_numbering);

    /** Sets up and runs a simulation without flags.
     *  Constructs initial sequences randomly.
     */
    void simulate_without_flags(
            size_type num_seq, size_type seq_length,
            std::string point_mutation_model,
            size_type num_jumps, double timestep,
            double burst_probability, double burst_mean,
            size_type max_active_copies,
            double recomb_mean,
            std::string file_out,
            size_type num_out_tags, size_type num_out_init,
            size_type num_out_seqs, size_type num_out_pair,
            bool to_randomise, bool to_seed, size_type seed,
            size_type sequence_numbering, size_type family_numbering);

    /** Sets up and runs a simulation with flags.
     *  Constructs initial sequences randomly.
     */
    void simulate_with_flags(
            size_type num_seq, size_type seq_length,
            std::string point_mutation_model,
            size_type num_sensitive_posns, double inactive_probability,
            size_type num_jumps, double timestep,
            double burst_probability, double burst_mean,
            size_type max_active_copies, size_type max_total_copies,
            double recomb_mean,
            double selection_threshold,
            double fam_proportion, double fam_percentage,
            std::string file_out,
            size_type num_out_tags, size_type num_out_init,
            size_type num_out_seqs, size_type num_out_pair,
            bool to_randomise, bool to_seed, size_type seed,
            size_type sequence_numbering, size_type family_numbering);
}

#endif // SIMULATION_H

