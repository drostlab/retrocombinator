#ifndef EVOLUTION_WITHOUT_FLAGS_H
#define EVOLUTION_WITHOUT_FLAGS_H

#include "evolution.h"

#include <list>
#include <utility>
#include <vector>

namespace retrocombinator
{
    /** A simulation where all sequences are active.
     *  In this class, a sequence beocoming inactive is equivalent to a sequence
     *  dying and being removed from the simulation and sequence pool.
     */
    class EvolutionWithoutFlags : public Evolution
    {
    public:
        /** Calculates the copy numbers of the sequences for all times.
         */
        void calculate_copy_number_tree(size_type num_init_seq);

        /** Overrides to create a copy number tree if it hasn't already been
         *  created.
         */
        void evolve(Output& output, PointMutator& pm,
                    const std::vector<std::string>& init_seqs,
                    double recomb_mean) override;

        /// Inherited constructor
        EvolutionWithoutFlags(size_type num_jumps, double timestep,
                  double burst_probability, double burst_mean,
                  size_type max_active_copies);

        /** To represent a phyogenetic tree.
         *  Refer to documentation of \p copy_numbers for more details.
         */
        typedef std::vector<std::list<std::pair<tag_type, tag_type>>> tree_type;

        /// To return the copy tree for testing purposes
        const tree_type get_copy_tree();
    private:
        /** The phyolgenetic tree of transposons for all times.
         *  This assumes there is only one family for the time being.
         *  copy_numbers[t][i] = (a, b) means that at time t,
         *  the ith sequence is got by recombining sequence a and b
         *  at time t-1.
         *  If b = SAME_SEQ it was just that sequence a.
         *  This is different to the case when a=b (where a new sequence, with a
         *  new sequence tag, was created but it is identical to a).
         *  If recomb_mean is 0, we pick sequence a to burst.
         */
        tree_type copy_numbers;

        /// Uses the copy number tree to burst sequences
        void burst_seqs(const size_type t, const double recomb_mean) override;

        /** Used to denote a sequence at time \a t-1 is present at time \a t
         *  in the copy number tree.
         */
        static const tag_type SAME_SEQ;
    };
}

#endif // EVOLUTION_WITH_FLAGS_H
