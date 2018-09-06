#include "evolution.h"
#include "output.h"
#include "point_mutator.h"

using namespace rcombinator;

Evolution::Evolution(long num_jumps, double timestep,
                     double burst_probability, double burst_mean,
                     long max_total_copies, long max_active_copies):
    num_jumps(num_jumps), timestep(timestep),
    burst_probability(burst_probability), burst_mean(burst_mean),
    max_total_copies(max_total_copies), max_active_copies(max_active_copies)
{}

void Evolution::evolve(Output& output, PointMutator& pm,
                       const std::vector<std::string>& init_seqs,
                       double recomb_mean)
{
    long real_time = 0;

    seqs.assign(init_seqs.begin(), init_seqs.end());

    output.print(0, 0, seqs);
    for (long t = 1; t <= num_jumps; ++t)
    {
        // this is written in this way so that the time to the next event can be
        // sampled from some distribution instead of being constant
        long diff_time = timestep;
        real_time += diff_time;

        // first, we mutate the sequences
        for (auto it=seqs.begin(); it!=seqs.end(); ++it)
        {
            pm.mutate_sequence(*it, diff_time);
        }

        // then, burst the sequences
        if (burst_probability)
        {
            burst_seqs(t, recomb_mean);
        }
        output.print(t, real_time, seqs);
    }
}
