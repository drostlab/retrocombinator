/**
 * @file
 *
 *  To run an entire simulation.
 */

#ifndef SIMULATION_H
#define SIMULATION_H

#include "pool.h"
#include "families.h"
#include "output.h"

namespace retrocombinator
{
    class Simulation
    {
    public:
        Simulation(
            std::string sequence, size_type sequence_length, size_type num_initial_copies,
            size_type critical_region_length, double inactive_probability,
            std::string mutation_model,
            double burst_probability, double burst_mean, size_type max_total_copies,
            double recomb_mean, double recomb_similarity,
            double selection_threshold,
            double family_coherence, size_type max_num_representatives,
            size_type num_steps, double time_per_step,
            std::string filename_out,
            size_type num_init_dist, size_type num_pair_dist,
            size_type num_fam_size, size_type num_fam_dist,
            double min_output_similarity
            );

        void print_seed(bool to_seed, size_type seed);
        void simulate();

        const sequence_list& get_pool() const { return pool.get_pool(); }
    private:
        const size_type sequence_length;

        Pool pool;
        Families families;

        size_type num_steps;
        double time_per_step;

        Output output;
    };
}

#endif // SIMULATION_H

