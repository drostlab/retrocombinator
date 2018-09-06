#include "evolution_with_flags.h"
#include "rand_maths.h"

#include <iterator>

using namespace rcombinator;

EvolutionWithFlags::EvolutionWithFlags(long num_jumps, double timestep,
                  double burst_probability, double burst_mean,
                  long max_total_copies, long max_active_copies):
    Evolution(num_jumps, timestep, burst_probability, burst_mean,
              max_total_copies, max_active_copies)
{}

void EvolutionWithFlags::burst_seqs(long /*unused t*/, double recomb_mean)
{
    // the number of sequences before this burst event
    const long prev_num_seqs = seqs.size();
    // the number of active sequences we have seen so far
    long num_active_seqs = 0;

    // index for loop, i and it correspond to the same sequence
    for (long i=0; i < prev_num_seqs; ++i)
    {
        if (seqs[i].is_active())
        {
            ++num_active_seqs;
            // this sequence is active, check if it bursts
            if (RNG.test_event(burst_probability))
            {
                long num_new_seqs = RNG.rand_poisson(burst_mean);

                for (long j = 0; j < num_new_seqs; ++j)
                {
                    // choose a sequence to recombine with, but not one that was
                    // created in this round of burst events
                    long recomb_index = RNG.rand_int(0, prev_num_seqs);

                    // then create the new sequence by recombining
                    seqs.emplace_back(seqs[i], seqs[recomb_index],
                                      RNG.rand_poisson(recomb_mean));
                    // check if we have new active sequences
                    if (seqs.back().is_active())
                    {
                        ++num_active_seqs;
                        // TODO: have a check if at this stage we are going to
                        // burst too fast and throw a warning/exception if it
                        // goes too high
                    }
                }
            }
        }
    }

    // kill sequences until we are within our limits
    while (seqs.size() > max_total_copies || num_active_seqs > max_active_copies)
    {
        auto to_delete = std::next(seqs.begin(), RNG.rand_int(0, seqs.size()));
        if (to_delete -> is_active())
        {
            --num_active_seqs;
        }
        seqs.erase(to_delete);
    }
}
