#include "evolution.h"
#include "output.h"
#include "point_mutator.h"

using namespace retrocombinator;

Evolution::Evolution(size_type num_jumps, double timestep,
                     double burst_probability, double burst_mean,
                     size_type max_active_copies) :
    num_jumps(num_jumps), timestep(timestep),
    burst_probability(burst_probability), burst_mean(burst_mean),
    max_active_copies(max_active_copies),
    total_num_sequences(0)
{
    // set up the 0th family
    families.emplace_back(Consts::INIT_FAMILY_COUNT);
}

void Evolution::evolve(Output& output, PointMutator& pm,
                       const std::vector<std::string>& init_seqs,
                       double recomb_mean)
{
    size_type real_time = 0;

    families.front().seqs.assign(init_seqs.begin(), init_seqs.end());

    output.print(0, 0, families);
    for (size_type t = 1; t <= num_jumps; ++t)
    {
        // this is written in this way so that the time to the next event can be
        // sampled from some distribution instead of being constant
        size_type diff_time = timestep;
        real_time += diff_time;

        // first, we mutate the sequences in each of the families
        for (auto& family : families)
        {
            for (auto& seq : family.seqs)
            {
                pm.mutate_sequence(seq, diff_time);
            }
        }
        // then, burst the sequences
        if (burst_probability)
        {
            burst_seqs(t, recomb_mean);
        }

        output.print(t, real_time, families);
    }
}
