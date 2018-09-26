#ifndef EVOLUTION_WITH_FLAGS_H
#define EVOLUTION_WITH_FLAGS_H

#include "evolution.h"

namespace rcombinator
{
    class EvolutionWithFlags : public Evolution
    {
    protected:
        /** The total number of sequences (active + inactive) we allow in our
         *  simulation.
         */
        const size_type max_total_copies;

        /** What percentage sequence similarity to the original we wish to
         *  maintain.
         */
        double selection_threshold;

        /** Burst by taking into consideration activity of sequences, events,
         *  and selection.
         */
        void burst_seqs(const size_type t, const double recomb_mean) override;

        /** Kill excess sequences.
         *  Provide the number of active sequences and total sequences
         *  currently, remove sequences until we have met both selection
         *  threshold needs and max_copies needs.
         */
        void kill_sequences(size_type num_active_copies,
                            size_type num_total_copies);
        /** Removes empty families.
         */
        void remove_dead_families();

        /** To split any large family into two families that can no longer
         *  recombine with each other.
         */
        void split_families();

        //@{
        /** Parameters for deciding when to split a family into two.
         *  If \p fam_proportion of the sequence similarity matrix goes
         *  below \p fam_percentage then split the family into two.
         */
        double fam_proportion;
        double fam_percentage;
        //@}

    public:
        /** Inherited constructor.
         *  \p max_total_copies is the total number of active and inactive
         *  sequences that we allow in our simulation.
         */
        EvolutionWithFlags(size_type num_jumps, double timestep,
                  double burst_probability, double burst_mean,
                  size_type max_active_copies, size_type max_total_copies);

        /// To kill sequences that have diverged too much
        void set_selection_threshold(double percentage);

        /** To prevent distant sequences from recombining.
         *  If \p proportion of the sequence similarity matrix goes below \p
         *  percentage then split the family into two.
         */
        void use_families_at(double proportion, double percentage);
    };
}

#endif // EVOLUTION_WITH_FLAGS_H
