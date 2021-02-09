#include "simulation.h"

using namespace retrocombinator;
int main() {

    int num_seq = 100;
    int seq_length = 5000;

    std::string point_mutation_model = "K80";

    double num_sensitive_positions = 10;    // only with flags
    double inactive_probability = 0.1;      // only with flags

    int num_jumps = 500;
    int timestep = 1;

    double burst_probability = 0.1;
    double burst_mean = 1;

    int max_active_copies = 1000;
    int max_total_copies = 10000;           // only with flags

    double recomb_mean = 1;

    double selection_threshold = 50;        // only with flags
    double fam_proportion = 30;             // only with flags
    double fam_percentage = 30;             // only with flags

    int num_out_tags = 10;
    int num_out_init = 10;
    int num_out_seqs = 0;
    int num_out_pair = 0;

    bool to_randomise = false;
    bool to_seed = true;
    int seed = 0;

    string filename_without = "main_simulation_without_flags_" +
        to_string(num_seq) + "_" + to_string(seq_length) + "_" +
        point_mutation_model + "_" +
        to_string(num_jumps) + "_" + to_string(timestep) + "_" +
        to_string(burst_probability) + "_" + to_string(burst_mean) + "_" +
        to_string(max_active_copies) + "_" +
        to_string(recomb_mean) + "_" +
        to_string(num_out_tags) + "_" + to_string(num_out_init) + "_" +
        to_string(num_out_seqs) + "_" + to_string(num_out_pair) + "_" +
        to_string(to_randomise) + "_" + to_string(to_seed) + "_" +
        to_string(seed) +
        ".out";
    string filename_with = "main_simulation_with_flags_" +
        to_string(num_seq) + "_" + to_string(seq_length) + "_" +
        point_mutation_model + "_" +
        to_string(num_sensitive_positions) + "_" +
        to_string(inactive_probability) + "_" +
        to_string(num_jumps) + "_" + to_string(timestep) + "_" +
        to_string(burst_probability) + "_" + to_string(burst_mean) + "_" +
        to_string(max_active_copies) + "_" + to_string(max_total_copies) + "_" +
        to_string(recomb_mean) + "_" +
        to_string(selection_threshold) + "_" +
        to_string(fam_proportion) + "_" + to_string(fam_percentage) + "_" +
        to_string(num_out_tags) + "_" + to_string(num_out_init) + "_" +
        to_string(num_out_seqs) + "_" + to_string(num_out_pair) + "_" +
        to_string(to_randomise) + "_" + to_string(to_seed) + "_" +
        to_string(seed) +
        ".out";

    simulate_without_flags(
        num_seq, seq_length, point_mutation_model,
        num_jumps, timestep,
        burst_probability, burst_mean,
        max_active_copies,
        recomb_mean,
        filename_without,
        num_out_tags, num_out_init, num_out_seqs, num_out_pair,
        to_randomise, to_seed, seed,
        0, 0, true
    );
    simulate_with_flags(
        num_seq, seq_length, point_mutation_model,
        num_sensitive_positions, inactive_probability,
        num_jumps, timestep,
        burst_probability, burst_mean,
        max_active_copies, max_total_copies,
        recomb_mean,
        selection_threshold, fam_proportion, fam_percentage,
        filename_with,
        num_out_tags, num_out_init, num_out_seqs, num_out_pair,
        to_randomise, to_seed, seed,
        0, 0, true
    );
    return 0;
}
