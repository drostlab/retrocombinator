/**
 * @file
 */
#ifndef SIMULATION_H
#define SIMULATION_H

#include "pool.h"
#include "families.h"
#include "output.h"

namespace retrocombinator
{
    /** To run a simulation of the molecular evolutionary process of a
     *  collection of retrotranposons.
     */
    class Simulation
    {
    public:
        /** Set up a simulation with the following parameters
          * \param sequence What is our initial sequence? If this is an empty
          * string, create one randomly, else use this sequence.
          * \param sequence_length If \p sequence is non-empty, ignore this.
          * Else, the length of sequences we are to consider for our simulation.
          * \param num_initial_copies How many sequences to start off with?
          * \param critical_region_length \copydoc ActivityTracker::critical_region_length
          * \param inactive_probability \copydoc ActivityTracker::inactive_probability
          * \param mutation_model \copydoc Mutator::Mutator(std::string model)
          * \param burst_probability \copydoc Burster::burst_probability
          * \param burst_mean \copydoc Burster::burst_mean
          * \param max_total_copies \copydoc Burster::max_total_copies
          * \param recomb_mean \copydoc Burster::recomb_mean
          * \param recomb_similarity \copydoc Burster::recomb_similarity
          * \param selection_threshold \copydoc Pool::selection_threshold
          * \param family_coherence The minimum similarity needed between
          * clusters for them to form the same family
          * \param max_num_representatives \copydoc Families::max_num_representatives
          * \param num_steps \copydoc Simulation::num_steps
          * \param time_per_step \copydoc Simulation::time_per_step
          * \param filename_out What file to save output to?
          * \param num_init_dist How many times should we print out distances to
          * the initial sequence?
          * \param num_pair_dist How many times should we print out pairwise
          * distances between our sequences?
          * \param num_fam_size How many times should we print out family
          * sizes?
          * \param num_fam_dist How many times should we print out pairwise
          * distances between family representatives?
          * \param min_output_similarity What is the lowest sequence similarity
          * we should print out (inclusive)? Similarities smaller than this are
          * suppressed (not printed) in the output file
          */
        Simulation(
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

        /** Prints the seed for random number generation to to output file
          * for reproducibility of experiments
          */
        void print_seed(bool to_seed, size_type seed);
        /// Runs the simulation with its specified parameters
        void simulate();

        /// Returns the current state of our pool of sequences
        const sequence_list& get_pool() const { return pool.get_pool(); }
    private:
        /// \copydoc ActivityTracker::sequence_length
        const size_type sequence_length;

        /// Stores the current state of our pool of sequences
        Pool pool;
        /// Stores the family representatives discovered so far
        Families families;

        /// Number of timesteps to run our simulation for
        size_type num_steps;
        /** How much real time corresponds to one timestep in our simulation?
          * (in millions of years)
          */
        double time_per_step;

        /// The object we use to write our results to file
        Output output;
    };
}

#endif // SIMULATION_H

