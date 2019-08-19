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
#include <list>

namespace retrocombinator
{
    /** Outputs the results of the simulation to a file.
     *  Can output the following things at specified timesteps:
     *  * The tags of the sequences and the families.
     *  * The raw sequences themselves.
     *  * The distance of each sequence to the inital sequence.
     *  * The pairwise distances between sequences.
     */
    class Output
    {
    public:
        /// Borrow typedef
        typedef Family::seqs_type seqs_type;

        /** Constructor, to specify how often we write to file.
         *  \p num_out_X = \a n means that the 'X' output will occur \a n
         *  times. Look at the definitions of print_'X' to learn what 'X' is.
         */
        Output(const std::string& filename_out, size_type final_time,
               size_type num_out_tags,
               size_type num_out_init,
               size_type num_out_seqs,
               size_type num_out_pair);

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
        void print(size_type timestep, double real_time,
                   const std::list<Family>& seqs);

    private:
        /// A stream for the output
        std::fstream fout;

        /** The final timestep in our simulation.
         *  Make sure we output everything we can at this timestep, regardless
         *  of what we explicity said should be output.
         */
        const size_type final_time;

        //@{
        /** When to print out what data.
         *  * Only output X if \p to_output_X is a multiple of the current
         *    timestep in the simulation
         *  * Look at the definition of print_'X' to learn what 'X' is.
         */
        const size_type to_output_tags;
        const size_type to_output_init;
        const size_type to_output_seqs;
        const size_type to_output_pair;
        //@}

        //@{
        /** Helper print functions.
         *  tags: the tags of all sequences*
         *  init: display distance to inital sequence**
         *  seqs: display raw sequences
         *  pair: display pairwise distances between the sequences
         *
         *  NOTES:
         *  * tags is always printed if something else is to be printed
         *  ** init is always printed if seqs is to be printed
         */

        /// Prints distance to initial sequence family-wise, in order
        void print_init(const seqs_type& seqs);

        /** Prints pairwise distances across all families.
         *  The order is as follows:
         *  for each family F1:
         *      for each seq S1 in F1:
         *          for each other seq S2 in F1:
         *              print S1*S2
         *          for each other family F2:
         *              for each seq S2 in F2:
         *                  print S1*S2
         */
        void print_pair(const std::list<Family>& families);

        /// Prints raw sequences family-wise, in order
        void print_seqs(const seqs_type& seqs);

        /// Prints sequence tags family-wise, in order
        void print_seq_tags(const seqs_type& seqs);
        //@}

        /// The initial sequence to compare to
        std::string init_seq;
    };
}

#endif //OUTPUT_H
