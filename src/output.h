/**
 * @file
 *
 * \brief To output the results of our simulation to a file.
 *
 */
#ifndef OUTPUT_H
#define OUTPUT_H

#include "sequence.h"
#include <fstream>

namespace rcombinator
{
    class Output
    {
    private:
        /// A stream for the output
        std::fstream fout;

        /** The final timestep in our simulation.
         *  Make sure we output everything we can at this timestep, regardless
         *  of what we explicity said should be output.
         */
        const long final_time;

        //@{
        /** Only output X if \p to_output_X is a multiple of the current
         *  timestep in the simulation.
         *  Look at the definition of print_<X> to learn what <X> is.
         */
        const long to_output_init;
        const long to_output_pair;
        const long to_output_seqs;
        const long to_output_tags;
        //@}

        //@{
        /** Helper print functions.
         *  init: display distance to inital sequence
         *  pair: display pairwise distances between the sequences
         *  seqs: display raw sequences
         *  tags: the tags and family tags of each of our sequences*
         *
         *  *Note that if any print function needs to be performed, print_tags
         *  automatically takes place alongside it.
         */
        void print_init(const std::vector<Sequence>& seqs);
        void print_pair(const std::vector<Sequence>& seqs);
        void print_seqs(const std::vector<Sequence>& seqs);
        void print_tags(const std::vector<Sequence>& seqs);
        //@}

        /// The initial sequence to compare to
        std::string init_seq;

    public:
        /** Constructor, to specify how often we write to file.
         *  \p num_out_X = \a n means that the <X> output will occur \a n
         *  times. Look at the definitions of print_<X> to learn what <X> is.
         */
        Output(const std::string& filename_out, long final_time,
               long num_out_init,
               long num_out_pair,
               long num_out_seqs,
               long num_out_tags);

        /** Destructor to close the file and clean-up.
         */
        ~Output();

        /** This sets the sequence that we compare all sequences in our
         *  simulation against.
         */
        void set_init_seq (std::string _init_seq);

        /** Prints auxillary information regarding the simulation.
         */
        void print_header();

        /** Prints the required information during the simulation.
         */
        void print(long timestep, double real_time,
                   const std::vector<Sequence>& seqs);

    };
}

#endif //OUTPUT_H
