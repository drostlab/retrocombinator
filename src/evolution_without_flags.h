#ifndef EVOLUTION_WITHOUT_FLAGS_H
#define EVOLUTION_WITHOUT_FLAGS_H

#include "evolution.h"

#include <list>
#include <utility>
#include <vector>

namespace rcombinator
{
    class EvolutionWithoutFlags : public Evolution
    {
    private:
        /** The phyolgenetic tree of transposons for all times.
         *  copy_numbers[t][i] = (a, b) means that at time t,
         *  the ith sequence is got by recombining sequence a and b
         *  at time t-1.
         *  If a = -1, it is just purely sequence b.
         *  If recomb_mean is 0, we pick sequence a to burst.
         */
        std::vector<std::list<std::pair<long, long>>> copy_numbers;

        void burst_seqs(long t, double recomb_mean) override;

    public:
        /** Calculates the copy numbers of the sequences for all times.
         */
        void calculate_copy_number_tree(long num_init_seq);

        void evolve(Output& output, PointMutator& pm,
                    const std::vector<std::string>& init_seqs,
                    double recomb_mean) override;

        EvolutionWithoutFlags(long num_jumps, double timestep,
                  double burst_probability, double burst_mean,
                  long max_total_copies, long max_active_copies);
    };
}

#endif // EVOLUTION_WITH_FLAGS_H
