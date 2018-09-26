/**
 * @file
 *
 * \brief To store a set of sequences that can recombine with each other
 *
 */
#ifndef FAMILY_H
#define FAMILY_H

#include "sequence.h"

namespace rcombinator
{
    /** To store a set of sequences that can recombine with each other.
     */
    class Family
    {
    private:
        /** An internal counter that is incremented every time a family is
         *  created.
         *  Used to assign each family a unique tag.
         */
        static tag_type global_family_count;

        /** A tag that uniquely identifies this family.
         *  If families are deleted forever, this tag is never updated again in
         *  the same simulation.
         */
        tag_type tag;

        /** The base family from which this family branched out from.
         *  0 is considered to be the initial family for a simulation
         */
        tag_type parent_tag;

    public:

        /** Constructor that takes the family that this was created from.
         *  If this was the initial family in a simulation, initialize with
         *  \a Consts::INIT_FAMILY_COUNT.
         */
        Family(tag_type parent_tag);

        //@{
        /** The actual sequences in this family that can recombine with each
         *  other.
         */
        /// The container for a family of sequences
        typedef std::vector<Sequence> seqs_type;
        /// The actual set of sequences
        seqs_type seqs;
        //@}

        /// Gets the number of sequences in this family
        size_type size() { return seqs.size(); }

        /// Gets the tag of this family
        tag_type get_tag() const { return tag; }
        /// Gets the tag of the parent family
        tag_type get_parent_tag() { return parent_tag; }

        /** When this family has split into subfamilies, update the tags.
         *  Give it a new tag.
         *  Update its parent tag with the old tag.
         */
        void split();

        /** Explicitly update the global family count to start from a
         *  particular number.
         *  new_start_tag will be given to the next family created.
         *  Used when running multiple simulations one after the other.
         */
        static void renumber_families(tag_type new_start_tag);
    };
}

#endif  //FAMILY_H
