/**
 * @file
 *
 *  To represent a centroid in a cluster of the sequence pool, that is, a
 *  'family representative'.
 */

#ifndef REPRESENTATIVE_H
#define REPRESENTATIVE_H

#include "constants.h"
#include <string>

namespace retrocombinator
{
    struct Representative
    {
    public:
        /// How to identify this representative?
        const tag_type tag;

        /// What the sequence actually is
        const std::string raw_sequence;

        /// Distance to initial sequence
        const size_type num_mutations;

        /// When in the simulation was this created?
        const size_type creation_timestep;


        Representative(std::string raw_sequence, size_type num_mutations,
                       size_type creation_timestep);
    private:
        /** An internal counter that is incremented every time a centroid is
         *  created.
         *  Used to assign each representative a unique tag.
         */
        static tag_type global_representative_count;


    };
}

#endif // REPRESENTATIVE_H

