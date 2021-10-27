/**
 * @file
 */

#ifndef OUTPUT_H
#define OUTPUT_H

#include "pool.h"
#include "families.h"
#include <fstream>

namespace retrocombinator
{
    /** To store the results of our simulation to file
      */
    class Output
    {
    public:
        /** Initialise our writer to file and create an object for writing.
          * \param filename_out What file to save output to?
          * \param final_timestep \copydoc Output::final_timestep
          * \param num_init_dist How many times should we print out distances to
          * the initial sequence?
          * \param num_pair_dist How many times should we print out pairwise
          * distances between our sequences?
          * \param num_fam_size How many times should we print out family
          * sizes?
          * \param num_fam_dist How many times should we print out pairwise
          * distances between family representatives?
          * \param max_seq_dist_incl \copydoc Output::max_seq_dist_incl
          */
        Output(std::string filename_out, size_type final_timestep,
            size_type num_init_dist, size_type num_pair_dist,
            size_type num_fam_size, size_type num_fam_dist,
            size_type max_seq_dist_incl);

        /// Default destructor that closes our file
        ~Output();

        /** Writes the data for one timestep in our simulation to file
          * \param t Which timestep are we on?
          * \param pool What is the pool of sequences at time \p t?
          * \param families What are the families at time \p t?
          */
        void output(size_type t, const Pool& pool, const Families& families);

        ///@{
        /// Prints the simulation parameters to file
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
        ///@}

    private:
        /// What is the timestep of our last step in the simulation?
        const size_type final_timestep;

        ///@{
        /** Call the appropriate <tt>print_<xxx></tt> if the current time is a
         * multiple of <tt>to_print_<xxx></tt>
          */
        const size_type to_print_init_dist;
        const size_type to_print_pair_dist;
        const size_type to_print_fam_size;
        const size_type to_print_fam_dist;
        ///@}

        /** What is the largest sequence distance we
          * should print out (inclusive)? Distances greater than this are
          * suppressed (not printed) in the output file
          */
        const size_type max_seq_dist_incl;

        /// A stream for the output
        std::fstream fout;

        /// Prints distances to initial sequence at time \p t
        void print_initial_dist(size_type t, const Pool& pool);
        /// Prints pairwise distances between sequences at time \p t
        void print_pairwise_dist(size_type t, const Pool& pool);
        /// Prints family representatives and their members at time \p t
        void print_family_sizes(size_type t, const Families& families, const Pool& pool);
        /// Prints pairwise distances between representatives at time \p t
        void print_family_dist(size_type t, const Families& families);
    };
}

#endif // OUTPUT_H

