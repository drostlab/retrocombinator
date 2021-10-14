/**
 * @file
 *
 * \brief To keep track of what sequences are active and what are not
 *
 * A class that 'configures' the set of sequences we are dealing with and keeps
 * track of whether or not they are capable of bursting.
 */

#ifndef ACTIVITY_TRACKER_H
#define ACTIVITY_TRACKER_H

#include "constants.h"

namespace retrocombinator
{
    class ActivityTracker
    {
    private:
        /** Length of the sequence we allow
          */
        size_type sequence_length;

        /** How many positions on either side of the sequence is the critical
         *  region?
         */
        size_type critical_region_length;

        /** What is the probability that a mutation to the critical region
         * causes inactivity?
         */
        double inactive_probability;

    public:
        /// Constructor
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

