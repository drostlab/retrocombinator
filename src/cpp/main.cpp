#include "../rand_maths.h"
#include "../simulation.h"

#include <iostream>
using namespace retrocombinator;
using namespace std;

int main() {

    std::string sequence = "";
    size_type sequence_length = 5000;
    size_type num_initial_copies = 20;
    size_type critical_region_length = 10;
    double inactive_probability = 0.01;
    std::string mutation_model = "K80";
    double burst_probability = 0.1;
    double burst_mean = 1;
    size_type max_total_copies = 50;
    double recomb_mean = 1.5;
    double recomb_similarity = 0.8;
    double selection_threshold = 0.5;
    double family_coherence = 0.7;
    size_type max_num_representatives = 20;
    size_t num_steps = 20;
    double time_per_step = 1;
    std::string filename_out {"simulationOutput.out"};
    size_type num_init_dist = 10;
    size_type num_pair_dist = 10;
    size_type num_fam_size = 10;
    size_type num_fam_dist = 10;
    double min_output_similarity = 0.3;
    bool to_seed = true;
    size_type seed = 0;
    try
    {
        if (to_seed) { RNG.set_specific_seed(seed); }
        else { RNG.set_random_seed(); }

        Simulation Simulation(
            sequence, sequence_length, num_initial_copies,
            critical_region_length, inactive_probability,
            mutation_model,
            burst_probability, burst_mean, max_total_copies,
            recomb_mean, recomb_similarity,
            selection_threshold,
            family_coherence, max_num_representatives,
            num_steps, time_per_step,
            filename_out,
            num_init_dist, num_pair_dist,
            num_fam_size, num_fam_dist,
            min_output_similarity
        );
        Simulation.print_seed(to_seed, RNG.get_last_seed());
        Simulation.simulate();
    }
    catch (Exception e)
    {
        std::cout << "EXCEPTION: " << e.what() << std::endl;
    }
    return 0;
}
