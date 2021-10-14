/**
 * @file
 *
 *
 */

#ifndef OUTPUT_H
#define OUTPUT_H

#include "pool.h"
#include "families.h"
#include <fstream>

namespace retrocombinator
{
    class Output
    {
    public:
        Output(std::string filename_out, size_type final_timestep,
            size_type num_init_dist, size_type num_pair_dist,
            size_type num_fam_size, size_type num_fam_dist,
            size_type max_seq_dist_incl);

        ~Output();

        void output(size_type t, const Pool& pool, const Families& families);

        void print_params(
            std::string sequence, size_type sequence_length, size_type num_initial_copies,
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
        );

        void print_params(bool to_seed, size_type seed);

    private:
        const size_type final_timestep;
        const size_type to_print_init_dist;
        const size_type to_print_pair_dist;
        const size_type to_print_fam_size;
        const size_type to_print_fam_dist;
        const size_type max_seq_dist_incl;

        /// A stream for the output
        std::fstream fout;

        void print_initial_dist(size_type t, const Pool& pool);
        void print_pairwise_dist(size_type t, const Pool& pool);
        void print_family_sizes(size_type t, const Families& families, const Pool& pool);
        void print_family_dist(size_type t, const Families& families);
    };
}

#endif // OUTPUT_H

