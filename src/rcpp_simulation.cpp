#include <Rcpp.h>

#include "simulation.h"
#include "rand_maths.h"

using namespace Rcpp;
using namespace retrocombinator;

// [[Rcpp::export]]
void rcpp_simulate_evolution(
    std::string sequence, size_t sequence_length, size_t num_initial_copies,
    size_t critical_region_length, double inactive_probability,
    std::string mutation_model,
    double burst_probability, double burst_mean, size_t max_total_copies,
    double recomb_mean, double recomb_similarity,
    double selection_threshold,
    double family_coherence, size_t max_num_representatives,
    size_t num_steps, double time_per_step,
    std::string filename_out,
    size_t num_init_dist, size_t num_pair_dist,
    size_t num_fam_size, size_t num_fam_dist,
    double min_output_similarity,
    bool to_seed, size_t seed
)
{
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
        Rcpp::Rcerr << "EXCEPTION: " << e.what() << std::endl;
    }
}
