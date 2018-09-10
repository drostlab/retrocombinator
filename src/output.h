/**
 * @file
 *
 * \brief To output the results of our simulation to a file.
 *
 */
#ifndef OUTPUT_H
#define OUTPUT_H

#include "family.h"
#include <fstream>

namespace rcombinator
{
    class Output
    {
    public:
        /// Borrow typedef
        typedef Family::seqs_type seqs_type;

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
                   const std::vector<Family>& seqs);

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
         *  seq_tags: the tags within a family*
         *
         *  *Note that if any print function needs to be performed, tags are
         *  always printed automatically takes place alongside it.
         */
        void print_init(const seqs_type& seqs);
        void print_pair(const seqs_type& seqs);
        void print_seqs(const seqs_type& seqs);
        void print_seq_tags(const seqs_type& seqs);
        //@}

        /// The initial sequence to compare to
        std::string init_seq;
    };
}

#endif //OUTPUT_H
