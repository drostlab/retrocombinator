/**
 * @file
 */

#ifndef ACTIVITY_TRACKER_H
#define ACTIVITY_TRACKER_H

#include "constants.h"

namespace retrocombinator
{
    /** To store the information and logic of whether or not a sequence is
      *  active, that is, capable of bursting/transposition.
      *  This class 'configures' the set of sequences we are dealing with
      */
    class ActivityTracker
    {
    private:
        /** Length of the sequence we allow
          */
        size_type sequence_length;

        /** How many positions on either side of the sequence is the critical
         *  region?
         *  A mutation to a critical region is what can perhaps cause inactivity
         */
        size_type critical_region_length;

        /** What is the probability that a mutation to the critical region
         * causes inactivity?
         */
        double inactive_probability;

    public:
        /** Configure our activity model
          * \param sequence_length \copydoc ActivityTracker::sequence_length
          * \param critical_region_length \copydoc ActivityTracker::critical_region_length
          * \param inactive_probability \copydoc ActivityTracker::inactive_probability
          */
        ActivityTracker(size_type sequence_length, size_type
                critical_region_length, double inactive_probability);

        /** Gets the length of sequences to be considered, in number of
         *  nucleotides
         */
        size_type get_sequence_length() const { return sequence_length; }

        /** Is a position in the critical region?
          */
        bool is_critical(size_type n) const;

        /** Has a sequence with a given number of mutations to the critical
         *  region become inactive?
         */
        bool check_activity(size_type num_critical_mutations) const;

    };
}

#endif // ACTIVITY_TRACKER_H

