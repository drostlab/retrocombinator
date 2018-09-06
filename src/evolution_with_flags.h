#ifndef EVOLUTION_WITH_FLAGS_H
#define EVOLUTION_WITH_FLAGS_H

#include "evolution.h"

namespace rcombinator
{
    class EvolutionWithFlags : public Evolution
    {
    protected:
        void burst_seqs(long t, double recomb_mean) override;
    public:
        EvolutionWithFlags(long num_jumps, double timestep,
                  double burst_probability, double burst_mean,
                  long max_total_copies, long max_active_copies);
    };
}

#endif // EVOLUTION_WITH_FLAGS_H
