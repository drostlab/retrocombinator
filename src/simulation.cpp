#include "simulation.h"
#include "rand_maths.h"

using namespace retrocombinator;

Simulation::Simulation(
    std::string sequence, size_type sequence_length_in, size_type num_initial_copies,
    size_type critical_region_length, double inactive_probability,
    std::string mutation_model,
    double burst_probability, double burst_mean, size_type max_total_copies,
    double recomb_mean, double recomb_similarity,
    double selection_threshold,
    double family_coherence, size_type max_num_representatives,
    size_type num_steps, double time_per_step,
    std::string filename_out,
    size_type num_init_dist, size_type num_pair_dist,
    size_type num_fam_size, size_type num_fam_dist,
    double min_output_similarity
):
    sequence_length(sequence.empty() ? sequence_length_in : sequence.length()),
    pool(sequence, sequence_length, num_initial_copies,
         critical_region_length, inactive_probability,
         mutation_model,
         burst_probability, burst_mean, max_total_copies,
         recomb_mean, recomb_similarity,
         selection_threshold),
    families((1.0-family_coherence)*sequence_length, max_num_representatives),
    num_steps(num_steps), time_per_step(time_per_step),
    output(filename_out, num_steps,
           num_init_dist, num_pair_dist, num_fam_size, num_fam_dist,
           floor((1.0-min_output_similarity)*sequence_length))
{
    output.print_params(sequence, sequence_length, num_initial_copies,
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
}

using namespace std;
void Simulation::simulate() {
    // timestep 0 is initial case
    for(size_type timestep = 1; timestep <= num_steps; ++timestep) {
        pool.step(time_per_step);
        families.update(pool, timestep);
        output.output(timestep, pool, families);
    }
}

void Simulation::print_seed(bool to_seed, size_type seed) {
    output.print_params(to_seed, seed);
}
