#include "evolution_with_flags.h"
#include "rand_maths.h"

#include <iterator>
using namespace rcombinator;

EvolutionWithFlags::EvolutionWithFlags(size_type num_jumps, double timestep,
                  double burst_probability, double burst_mean,
                  size_type max_active_copies, size_type max_total_copies):
    Evolution(num_jumps, timestep, burst_probability, burst_mean,
              max_active_copies),
    max_total_copies(max_total_copies),
    selection_threshold(0) // no selection bias initially
{}

void EvolutionWithFlags::burst_seqs(const size_type /*unused t*/,
                                    const double recomb_mean)
{
    // The number of sequences we have seen so far across all families.
    // Count active sequences whenever we see one or create one
    size_type num_active_seqs = 0;
    // Count total sequences for each family after bursting that family
    size_type num_total_seqs = 0;

    for (auto& family : families)
    {
        auto& seqs = family.seqs;

        // the number of sequences before this burst event
        const size_type prev_num_seqs = seqs.size();

        for (size_type i=0; i < prev_num_seqs; ++i)
        {
            if (seqs[i].is_active())
            {
                ++num_active_seqs;
                // this sequence is active, check if it bursts
                if (RNG.test_event(burst_probability))
                {
                    size_type num_new_seqs = RNG.rand_poisson(burst_mean);

                    for (size_type j = 0; j < num_new_seqs; ++j)
                    {
                        // choose a sequence to recombine with, but not one that
                        // was created in this round of burst events
                        size_type recomb_index = RNG.rand_int(0, prev_num_seqs);

                        // then create the new sequence by recombining
                        seqs.emplace_back(seqs[i], seqs[recomb_index],
                                          RNG.rand_poisson(recomb_mean));
                        // check if we have new active sequences
                        if (seqs.back().is_active())
                        {
                            ++num_active_seqs;
                            // TODO: have a check if at this stage we are going
                            // to burst too fast and throw a warning/exception
                            // if it goes too high
                        }
                    }
                }
            }
        }
        // add all the sequences from the current family
        num_total_seqs += seqs.size();
    }

    kill_sequences(num_active_seqs, num_total_seqs);
}
void EvolutionWithFlags::kill_sequences(size_type num_active_seqs,
                                        size_type num_total_seqs)
{
    // kill sequences below our selection threshold
    if (selection_threshold > 0)
    {
        for (auto& family : families)
        {
            auto& seqs = family.seqs;
            for (auto it=seqs.begin(); it!=seqs.end(); )
            {
                if (it -> init_seq_similarity() < selection_threshold)
                {
                    if (it -> is_active())
                    {
                        // one less active sequence
                        --num_active_seqs;
                    }
                    // and one less sequence overall
                    --num_total_seqs;
                    it = seqs.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }
    }

    // then, kill sequences until we are within our limits
    while (num_total_seqs > max_total_copies ||
           num_active_seqs > max_active_copies)
    {
        size_type random_family_index = RNG.rand_int(0, families.size());
        auto& seqs = families[random_family_index].seqs;

        auto to_delete = std::next(seqs.begin(), RNG.rand_int(0, seqs.size()));
        if (to_delete -> is_active())
        {
            // one less active sequence
            --num_active_seqs;
        }
        // and one less sequence overall
        --num_total_seqs;
        seqs.erase(to_delete);
    }

    // remove dead families
    for (auto family_it=families.begin(); family_it!=families.end(); )
    {
        if (family_it->seqs.size() == 0)
        {
            family_it = families.erase(family_it);
        }
        else
        {
            ++family_it;
        }
    }
}
