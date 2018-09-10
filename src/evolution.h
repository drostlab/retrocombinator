#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "family.h"

namespace rcombinator
{
    class Output;
    class PointMutator;

    class Evolution
    {
    public:
        /// Borrow typedef from family
        typedef Family::seqs_type seqs_type;

        /** Set up a simulation with given parameters.
         *  Look at documenation for the individual members to understand what
         *  they mean.
         */
        Evolution(size_type num_jumps, double timestep,
                  double burst_probability, double burst_mean,
                  size_type max_active_copies);

        /** Run a simulation, modify the sequences, and output results to file.
         *  output:      where we write to disc
         *  pm:          the point mutator we use in our simulation
         *  init_seqs:   the initial sequences we start with
         *  recomb_mean: the expected number of template switches
         */
        virtual void evolve(Output& output, PointMutator& pm,
                            const std::vector<std::string>& init_seqs,
                            double recomb_mean);

        /// Use a virtual destructor so objects can be instantiated
        virtual ~Evolution() = default;

    protected:
        /// Number of jumps in our simulation
        const size_type num_jumps;
        /// How much time has passed in one jump (in millions of years)
        const double timestep;

        /// Probability that an active sequence bursts in \a timestep
        const double burst_probability;
        /// The Poisson mean for new number of sequences to be created
        const double burst_mean;

        /** The total number of sequences that have the ability to burst we
         *  allow in our simulation.
         */
        const size_type max_active_copies;

        /** The actual values of the sequences during the simulation.
         *  All sequences in family \a i are present in families[i].
         */
        std::vector<Family> families;
        /// The overall number of sequences across all families
        size_type total_num_sequences;

        /** How the sequences burst after a timestep in the simulation.
         *  To be implemented by a derived class, depending on our assumptions.
         */
        virtual void burst_seqs(const size_type t,
                                const double recomb_mean) = 0;
    };
}

#endif //EVOLUTION_H
