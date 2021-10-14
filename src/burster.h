/**
 * @file
 *
 * \brief To keep track of what sequences are bursting and what are not
 *
 * This takes in a pool of sequences, tries bursting the active ones, and then
 * prunes down to a set number of sequences by sampling from all possible
 * sequences.
 *
 */

#ifndef BURSTER_H
#define BURSTER_H

#include "constants.h"
#include "sequence.h"

namespace retrocombinator
{
    class Burster
    {
    private:
        /// Probability that an active sequence bursts in a timestep
        const double burst_probability;
        /// The Poisson mean for new number of sequences to be created
        const double burst_mean;

        /** The total number of sequences that we need to keep track of in our
         *  simulation.
         */
        const size_type max_total_copies;

        /** The Poisson mean for number of template switches during
         *  recombination
         */
        const double recomb_mean;
        /** Only recombine between two sequences if they are at least this
         *  similar.
         */
        const double recomb_similarity;

        /**
         * What are we trying to burst the N sequences into?
         * - The first N values are 1, representing the sequences themselves
         * - Value (N+i) represents the number of new sequences created by
         *   bursting sequence i
         */
        std::vector<size_type> get_new_sequence_counts(const sequence_list& pool);

    public:
        /** Constructs a burster with input information about how often
         *  sequences burst, and how many copies they create
          */
        Burster(double burst_probability, double burst_mean,
                size_type max_total_copies,
                double recomb_mean, double recomb_similarity);

        /** How the sequences burst after a timestep in the simulation.
         *  Input is a list of active sequences that are capable of bursting.
         *  Output is a list of how much each sequence is present
         */
        void burst_sequences(sequence_list& pool);
    };
}

#endif // BURSTER_H

