#include "output.h"
#include "point_mutator.h"
#include "rand_maths.h"
#include "simulation.h"

namespace retrocombinator
{
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
            size_type sequence_numbering, size_type family_numbering)
    {
        if (init_seq_index >= init_seqs.size())
        {
            throw Exception("Choose a valid index for the initial sequence.");
        }

        if (to_randomise)
        {
            RNG.set_random_seed();
        }
        if (to_seed)
        {
            RNG.set_specific_seed(seed);
        }
        Sequence::renumber_sequences(sequence_numbering);
        Family::renumber_families(family_numbering);

        EvolutionWithoutFlags e(num_jumps, timestep,
                                burst_probability, burst_mean,
                                max_active_copies);
        e.calculate_copy_number_tree(init_seqs.size());

        size_type max_seq_length = 0;
        for (const auto& seq : init_seqs)
        {
            if (seq.size() > max_seq_length)
            {
                max_seq_length = seq.size();
            }
        }
        PointMutator pm(point_mutation_model, max_seq_length);

        Output output(file_out, num_jumps,
                      num_out_tags, num_out_init, num_out_seqs, num_out_pair);
        output.set_init_seq(init_seqs[init_seq_index]);
        e.evolve(output, pm, init_seqs, recomb_mean);
    }

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
            size_type sequence_numbering, size_type family_numbering)
    {
        if (init_seq_index >= init_seqs.size())
        {
            throw Exception("Choose a valid index for the initial sequence.");
        }

        if (to_randomise)
        {
            RNG.set_random_seed();
        }
        if (to_seed)
        {
            RNG.set_specific_seed(seed);
        }
        Sequence::renumber_sequences(sequence_numbering);
        Family::renumber_families(family_numbering);

        EvolutionWithFlags e(num_jumps, timestep,
                             burst_probability, burst_mean,
                             max_active_copies, max_total_copies);

        size_type max_seq_length = 0;
        for (const auto& seq : init_seqs)
        {
            if (seq.size() > max_seq_length)
            {
                max_seq_length = seq.size();
            }
        }
        PointMutator pm(point_mutation_model, max_seq_length,
                        num_sensitive_posns, inactive_probability);

        Output output(file_out, num_jumps,
                      num_out_tags, num_out_init, num_out_seqs, num_out_pair);
        output.set_init_seq(init_seqs[init_seq_index]);
        e.set_selection_threshold(selection_threshold);
        e.use_families_at(fam_proportion, fam_percentage);
        e.evolve(output, pm, init_seqs, recomb_mean);

    }

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
            size_type sequence_numbering, size_type family_numbering)
    {
        if (to_randomise)
        {
            RNG.set_random_seed();
        }
        if (to_seed)
        {
            RNG.set_specific_seed(seed);
        }

        Sequence S0(seq_length);
        std::vector<std::string> init_seqs(num_seq, S0.as_string());

        simulate_without_flags(
            init_seqs, size_type(0),
            point_mutation_model,
            num_jumps, timestep, burst_probability, burst_mean,
            max_active_copies, recomb_mean,
            file_out, num_out_tags, num_out_init, num_out_seqs, num_out_pair,
            false, false, seed, sequence_numbering, family_numbering);
    }

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
            size_type sequence_numbering, size_type family_numbering)
    {
        if (to_randomise)
        {
            RNG.set_random_seed();
        }
        if (to_seed)
        {
            RNG.set_specific_seed(seed);
        }

        Sequence S0(seq_length);
        std::vector<std::string> init_seqs(num_seq, S0.as_string());

        simulate_with_flags(
            init_seqs, size_type(0),
            point_mutation_model,
            num_sensitive_posns, inactive_probability,
            num_jumps, timestep, burst_probability, burst_mean,
            max_active_copies, max_total_copies, recomb_mean,
            selection_threshold, fam_proportion, fam_percentage,
            file_out, num_out_tags, num_out_init, num_out_seqs, num_out_pair,
            false, false, seed, sequence_numbering, family_numbering);
    }

}
