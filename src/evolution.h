#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "sequence.h"

#include <vector>

namespace rcombinator
{
    class Output;
    class PointMutator;

    class Evolution
    {
    protected:
        /// Number of jumps in our simulation
        const long num_jumps;
        /// How much time has passed in one jump (in millions of years)
        const double timestep;

        /// Probability that an active sequence bursts in \a timestep
        const double burst_probability;
        /// The Poisson mean for new number of sequences to be created
        const double burst_mean;
        /// The total number of sequences we allow in our simulation
        const long max_total_copies;
        /// The total number of active sequences we allow in our simulation
        const long max_active_copies;

        /// The actual values of the sequences during the simulation
        std::vector<Sequence> seqs;

        /** How the sequences burst after a timestep in the simulation.
         *  To be implemented by a derived class, depending on our assumptions.
         */
        virtual void burst_seqs(long t, double recomb_mean) = 0;
    public:
        /** Set up a simulation with given parameters.
         *  Look at documenation for the individual members to understand what
         *  they mean.
         */
        Evolution(long num_jumps, double timestep,
                  double burst_probability, double burst_mean,
                  long max_total_copies, long max_active_copies);

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

        /// To prevent distant sequences from recombining
        //virtual void recombination_threshold(double percentage);

        /// To separate our sequences into different families
        //virtual void use_families(double percentage);

        /// To kill sequences that have diverged too much
        //virtual void selection_threshold(double percentage);
    };
}

#endif //EVOLUTION_H
