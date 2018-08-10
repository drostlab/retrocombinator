/**
 * @file
 *
 * \brief To store a DNA sequence and the mutations that it has undergone.
 *
 * Includes methods to keep track of which mutations are lethal, methods to
 * recombine sequences and methods to get the pairwise distances between two
 * strings.
 */
#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "constants.h"

namespace rcombinator
{
    /** To represent a DNA sequence and the mutations that it has
     *  undergone.
     *
     *  Keeps track of the actual sequence, mutations and lethal mutations.
     */
    class Sequence
    {
    private:

        /** An internal counter that is incremented every time a sequence is
         *  created.
         *  Used to assign each sequence a unique tag.
         */
        static long global_sequence_count;

        /** A number that uniquely identifies this sequence.
         *  This tag transcends activity (if an inactive sequence becomes active
         *  again, it has the same tag)
         */
        long tag;

        /** Actual sequence of nucleotides.
         *  Stored as a string internally.
         */
        std::vector<bool> bases;

        //@{
        /** Basic typedefs - hashed data structures for quick lookup.
         *  For keeping track of mutations and lethal mutations.
         */
        typedef std::unordered_map<long, char> mutations_type;
        typedef std::unordered_set<long> lethal_mutations_type;
        //@}

        /** Positions of mutations and what the *original* nucleotide was.
         *  Stored as an unordered map locally.
         */
        mutations_type mutations;

        /** Positions of mutations that are lethal.
         *  Internally stored as a set. This set is always a subset of
         *  \p mutations.keys.
         */
        lethal_mutations_type lethal_mutations;

    public:

        /** Constructs a random sequence of length \a n.
         *  This is considered initial, so no mutations are present.
         */
        Sequence(long n);

        /** Constructs a sequence from a given string.
         *  This is considered initial, so no mutations are present.
         */
        Sequence(std::string s);

        /** Constructs a sequence from recombining two other sequences.
         *  The number of template switches has to be specified, and the
         *  positions at which the template switches are made is random.
         *
         *  The mutations recorded are with respect to the original sequences.
         *  That is, the new sequence \a s_new will have a mutation \a m at
         *  position \a l if and only if the sequence \a s_old whose nucleotide
         *  is used for \a s_new at position \a l had mutation \a m present at
         *  that position.
         *
         *  \todo Add an option for specifying the positions of the template
         *  switches too, or overload this function.
         */
        Sequence(Sequence& s1, Sequence& s2, int num_template_switches);

        /// Returns length of the sequence
        long get_length() const { return (bases.size()/2); }

        /// Returns the unique label for this sequence
        long get_tag() const { return tag; }

        /** Returns the 2bit encoding for a base at a given position.
         */
        inline std::pair<bool, bool> bits_at(long n) const
        {
            return std::make_pair(bases[2*n], bases[2*n+1]);
        }

        /** Returns the character for a base at a given position.
         */
        inline char char_at(long n) const
        {
            return Consts::NUC_BOOL2CHAR(bits_at(n));
        }

        /** Changes the nucleotide at position \a n to \a new_nucleotide.
         *
         *  If the new_nucleotide is the same as the original nucleotide in the
         *  string, the mutation disappears, else a mutation is created.
         *  It can also be specified whether or not the mutation is lethal.
         */
        void point_mutate(long n, char new_nucleotide, bool is_lethal = false);

        /** Returns the raw nucleotide sequence as a string.
         */
        std::string as_string() const;

        /** Tests whether this sequence is active (can transpose) or not.
         *  Returns true if and only if there are no lethal mutations.
         */
        bool is_active() const { return lethal_mutations.empty(); }

        /** Returns how many mutations are present in this sequence.
         */
        long num_mutations() const { return mutations.size(); }

        /** Computes pairwise distances between two sequences.
         *  This is the standard edit distance score, and is the number of
         *  mismatches (because insertions and deletions are not possible in this
         *  system).
         */
        friend long operator *(const Sequence& s1, const Sequence& s2);
    };
}

#endif //SEQUENCE_HPP
