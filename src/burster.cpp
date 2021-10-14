#include "burster.h"
#include "rand_maths.h"


using namespace retrocombinator;

Burster::Burster(double burst_probability, double burst_mean,
                 size_type max_total_copies,
                 double recomb_mean, double recomb_similarity):
    burst_probability(burst_probability), burst_mean(burst_mean),
    max_total_copies(max_total_copies),
    recomb_mean(recomb_mean), recomb_similarity(recomb_similarity)
{}

void Burster::burst_sequences(sequence_list& pool) {

    if (pool.empty()) return;

    // 1) How many new sequences to make?
    auto new_sequence_counts = get_new_sequence_counts(pool);

    auto pruned_sequence_counts =
        RNG.choose_items(new_sequence_counts, max_total_copies);

    // Store the last sequence we currently have
    auto last_sequence = std::next(pool.end(), -1);
    const size_type N = pool.size();

    sequence_list::iterator it, jt;
    size_type i, copy_num;
    std::vector<Sequence *> similar_seqs;

    // 2a) Create new sequences based on bursting
    for (it = pool.begin(), i = 0; i < N; ++it, ++i) {
        // If this sequence burst
        if (pruned_sequence_counts[N +i] > 0) {

            // Which sequences can it recombine with?
            similar_seqs.clear();
            for(jt = pool.begin(); jt != std::next(last_sequence); ++jt)
            {
                if (1-((*it) % (*jt)) > recomb_similarity)
                {
                    similar_seqs.push_back(&*jt);
                }
            }

            // Create the recombined sequences
            for(copy_num = 0; copy_num < pruned_sequence_counts[N+i]; ++copy_num)
            {
                auto new_seq = RNG.rand_int(0, similar_seqs.size());
                pool.emplace_back(*it, *similar_seqs[new_seq],
                    recomb_mean != 0 ? RNG.rand_poisson(recomb_mean) : 0);
            }
        }
    }

    // 2a) Keep/delete old sequences
    for (it = pool.begin(), i = 0; i < N; ++i) {
        // If this sequence was chosen
        if (pruned_sequence_counts[i] >= 1) { ++it;}
        else { it = pool.erase(it); }
    }

}

std::vector<size_type> Burster::get_new_sequence_counts(
        const sequence_list& pool)
{
    const size_type N = pool.size();
    // What are we trying to burst the N sequences into?
    // - The first N values are 1, representing the sequences themselves
    // - Value (N+i) represents the number of new sequences created by
    //   bursting sequence i
    std::vector<size_type> new_sequence_counts(N*2, 0);

    sequence_list::const_iterator it;
    size_type i;
    for (it = pool.begin(), i = 0; i < N; ++it, ++i) {
        new_sequence_counts[i] = 1;
        if (it->is_active() && RNG.test_event(burst_probability)) {
            new_sequence_counts[N + i] = RNG.rand_poisson(burst_mean);
        }
    }

    return new_sequence_counts;
}
