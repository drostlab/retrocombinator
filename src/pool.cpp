#include "pool.h"

using namespace retrocombinator;

Pool::Pool(std::string sequence, size_type sequence_length,
           size_type num_initial_copies,
           size_type critical_region_length, double inactive_probability,
           std::string mutation_model,
           double burst_probability, double burst_mean, size_type max_total_copies,
           double recomb_mean, double recomb_similarity,
           double selection_threshold):
    activity_tracker(sequence_length,
            critical_region_length, inactive_probability),
    mutator(mutation_model),
    burster(burst_probability, burst_mean, max_total_copies,
            recomb_mean, recomb_similarity),
    selection_threshold(selection_threshold)
{
    Sequence::set_activity_tracker(activity_tracker);
    Sequence::renumber_sequences();
    if (!sequence.empty()) {
        for (size_type i = 0; i < num_initial_copies; ++i) {
            pool.emplace_back(sequence);
        }
    }
    else {
        // Create one random sequence
        pool.emplace_back();
        for (size_type i = 1; i < num_initial_copies; ++i) {
            // Initialise everything else with that
            pool.emplace_back(pool.begin()->as_string());
        }
    }

}

void Pool::step(double time_per_step) {
    // 1) Mutate
    for (auto& seq : pool) {
        mutator.mutate_sequence(seq, time_per_step);
    }
    // 2) Burst and prune
    burster.burst_sequences(pool);

    // 3) Select
    if (selection_threshold > 0.0) {
        for (auto it=pool.begin(); it!=pool.end(); /* update it in loop*/)
        {
            if (it -> init_seq_similarity() < selection_threshold) {
                it = pool.erase(it);
            }
            else { ++it; }
        }
    }
}

dist_type Pool::get_distance_matrix() const {
    dist_type dist_mat;
    for (const auto& seq_i : pool) {
        dist_mat.emplace_back();
        for (const auto& seq_j : pool) {
            dist_mat.back().push_back(seq_i % seq_j);
        }
    }
    return dist_mat;
}

