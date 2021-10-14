/**
 * @file
 *
 * \brief To keep track of our current pool of Sequences
 *
 * Every sequence in this pool is mutated, given the opportunity to be burst and
 * pruned, and selected based on some requirement.
 */

#ifndef POOL_H
#define POOL_H

#include "sequence.h"
#include "burster.h"
#include "mutator.h"

namespace retrocombinator
{
    class Pool
    {
    private:
        ActivityTracker activity_tracker;

        Mutator mutator;
        Burster burster;

        /// Kill sequences below this similarity to initial sequence
        double selection_threshold;

        sequence_list pool;

    public:
        /** Constructor of Sequence Pool, that gives it access to a
         *  burster/pruner and a mutator.
         *
         */
        Pool(std::string sequence, size_type sequence_length,
             size_type num_initial_copies,
             size_type critical_region_length, double inactive_probability,
             std::string mutation_model,
             double burst_probability, double burst_mean, size_type max_total_copies,
             double recomb_mean, double recomb_similarity,
             double selection_threshold);

        /// Refresh the pool to the next timestep
        void step(double time_per_step);

        const sequence_list& get_pool() const { return pool; }

        dist_type get_distance_matrix() const;
    };
}

#endif // POOL_H

