#include "evolution_without_flags.h"
#include "rand_maths.h"

#include <iterator>

using namespace rcombinator;

namespace rcombinator
{
    const tag_type EvolutionWithoutFlags::SAME_SEQ = -1;
}

const EvolutionWithoutFlags::tree_type EvolutionWithoutFlags::get_copy_tree()
{
    return copy_numbers;
}

EvolutionWithoutFlags::EvolutionWithoutFlags(size_type num_jumps, double timestep,
                  double burst_probability, double burst_mean,
                  size_type max_active_copies):
    Evolution(num_jumps, timestep, burst_probability, burst_mean,
              max_active_copies)
{}

void EvolutionWithoutFlags::calculate_copy_number_tree(size_type num_init_seq)
{
    // assigns an empty list for each timestep
    copy_numbers.resize(num_jumps+1);

    // 0) Initial conditions, just the sequence indices
    for (size_type i = 0; i<num_init_seq; ++i)
    {
        copy_numbers[0].emplace_back(i, SAME_SEQ);
    }

    for (size_type t=1; t <= num_jumps; ++t)
    {
        // 1) Copy all of the previous generation
        for (size_type older=0; older<copy_numbers[t-1].size(); ++older)
        {
            copy_numbers[t].emplace_back(older, SAME_SEQ);
        }
        // 2) Go through the old sequences and test for bursts
        for (size_type older=0; older<copy_numbers[t-1].size(); ++older)
        {
            if (RNG.test_event(burst_probability))
            {
                // if we burst a sequence, pick a sequence to recombine with
                size_type new_copies = RNG.rand_poisson(burst_mean);
                for (size_type cp=0; cp<new_copies; ++cp)
                {
                    // choose a sequence to recombine with, but not one that was
                    // created in this round of burst events
                    size_type recomb_index = RNG.rand_int(0, copy_numbers[t-1].size());
                    copy_numbers[t].emplace_back(older, recomb_index);
                }
            }
        }
        // 3) Kill if excessive numbers are reached
        size_type new_size = std::min(size_type(copy_numbers[t].size()), max_active_copies);
        while (copy_numbers[t].size() > new_size)
        {
            size_type to_delete = RNG.rand_int(0, copy_numbers[t].size());
            copy_numbers[t].erase(std::next(copy_numbers[t].begin(), to_delete));
        }
    }

}

void EvolutionWithoutFlags::burst_seqs(const size_type t, const double recomb_mean)
{
    // this assumes there is only family
    auto& seqs = families.front().seqs;

    // STEP 1) store the deleted sequences for later recombination
    // NOTE: we can only start deleting sequences after we have done this
    // because we need to keep indices of sequences intact
    std::unordered_map<size_type, Sequence> deleted_sequences;

    // expected_seq denotes which sequences we expect to see at time t, given
    // that we saw them at time t-1;
    // if we do not see it, it must have been killed
    size_type expected_seq_index = 0;

    for (auto it=copy_numbers[t].begin(); it!=copy_numbers[t].end(); ++it)
    {
        // if we are no longer looking at original sequences,
        // all the remaing ones were killed
        if (it->second != SAME_SEQ)
        {
            for ( ; expected_seq_index < seqs.size(); ++expected_seq_index)
            {
                deleted_sequences.emplace(expected_seq_index,
                                          std::move(seqs[expected_seq_index]));
            }
            // now finished copying sequences, create new sequences
            break;
        }
        // else if we have found a different original sequence,
        // the intermediate ones were killed
        else if (it->first != tag_type(expected_seq_index))
        {
            for ( ; tag_type(expected_seq_index) != it->first;
                    ++expected_seq_index)
            {
                // move the current sequence out of the container
                deleted_sequences.emplace(expected_seq_index,
                                          std::move(seqs[expected_seq_index]));
            }
        }
        ++expected_seq_index;
    }
    // deleted_sequences now contains all the sequences present at time t-1 but
    // not present at t, with the correct indices;
    // seqs contains all sequences present at time t-1

    // STEP 2) create the next set of sequences
    // the set of sequences we have from the previous timestep
    size_type prev_num_seqs = seqs.size();
    // which sequence we are currently looking at - may have to delete this or
    // burst it depending on copy_numbers
    size_type cur_seq_index = 0;
    auto cur_seq_it = seqs.begin();
    // whether we need to start creating new sequences
    bool start_recombining = false;

    for (auto it=copy_numbers[t].begin(); it !=copy_numbers[t].end(); ++it)
    {
        if (it->second == SAME_SEQ)
        {
            // keep iterating through sequences if they are not killed
            if (it->first != tag_type(cur_seq_index))
            {
                while (tag_type(cur_seq_index) != it->first)
                {
                    cur_seq_it = seqs.erase(cur_seq_it);
                    ++cur_seq_index;
                }
            }
            ++cur_seq_index;
            ++cur_seq_it;
        }
        else
        {
            // from now on, all sequences are new
            if (!start_recombining)
            {
                // delete all the remaining sequences before the ones that are
                // created from recombination
                while(cur_seq_index < prev_num_seqs)
                {
                    cur_seq_it = seqs.erase(cur_seq_it);
                    ++cur_seq_index;
                }
                start_recombining = true;
            }

            // a local function for finding the location of sequences
            auto find_sequence = [&] (size_type seq_num) -> const Sequence*
            {
                auto check_deleted = deleted_sequences.find(seq_num);
                // if this sequence has been deleted, find it in the hashmap
                if (check_deleted != deleted_sequences.end())
                {
                    return &(check_deleted->second);
                }
                // else, this sequence has not been deleted, it must be present
                // as a raw sequence somewhere in copy_numbers[t], see which
                // position it was at
                size_type find_index = 0; // the position it was at
                for (auto jt=copy_numbers[t].begin();
                     jt!=copy_numbers[t].end(); ++jt, ++find_index)
                {
                    if (jt->second == SAME_SEQ && jt->first == tag_type(seq_num))
                    {
                        break;
                    }
                }
                return &*std::next(seqs.begin(), find_index);
            };
            auto seq1_ptr = find_sequence(it->first);
            auto seq2_ptr = find_sequence(it->second);

            // if no recombination, just duplicate the sequence
            if (recomb_mean == 0)
            {
                seqs.emplace_back(*seq1_ptr, *seq1_ptr, 0);
            }
            // else, recombine two sequences
            else
            {
                seqs.emplace_back(*seq1_ptr, *seq2_ptr, recomb_mean);
            }
        }
    }
}

void EvolutionWithoutFlags::evolve(Output& output, PointMutator& pm,
                                   const std::vector<std::string>& init_seqs,
                                   double recomb_mean)
{
    // recalculate copy number tree only if we haven't already computed it
    // TODO: come up with a more rigorous test of whether we have computed the
    // tree or not

    // if the tree itself has not been initialized
    if (copy_numbers.empty())
    {
        calculate_copy_number_tree(init_seqs.size());
    }
    // if the first layer is different
    else if(copy_numbers[0].size() != init_seqs.size())
    {
        calculate_copy_number_tree(init_seqs.size());
    }

    Evolution::evolve(output, pm, init_seqs, recomb_mean);
}

