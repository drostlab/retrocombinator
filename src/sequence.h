/**
 * @file
 *
 * \brief To store a DNA sequence and the mutations that it has undergone.
 *
 * Includes methods to keep track of which mutations are lethal, methods to
 * recombine sequences and methods to get the pairwise distances between two
 * strings.
 */
#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "constants.h"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

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
        static tag_type global_sequence_count;

        /** A number that uniquely identifies this sequence.
         *  This tag transcends activity (if an inactive sequence becomes active
         *  again, it has the same tag)
         */
        tag_type tag;

        /** The parent tags that this sequence was created from.
         *  If this was created as Sequence(S1, S2), the tags are ordered as
         *  <S1.get_tag(), S2.get_tag()>.
         *  If this was created randomly, the tags are <RAND, RAND>.
         *  If this was created from a string, the tags are <INIT, INIT>.
         */
        std::pair<tag_type, tag_type> parent_tags;

        /** Actual sequence of nucleotides.
         *  Stored as a string internally.
         */
        std::vector<bool> bases;

        //@{
        /** Basic typedefs - hashed data structures for quick lookup.
         *  For keeping track of mutations and lethal mutations.
         */
        typedef std::unordered_map<tag_type, char> mutations_type;
        typedef std::unordered_set<tag_type> lethal_mutations_type;
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

        /** Returns the 2bit encoding for a base at a given position.
         */
        inline std::pair<bool, bool> bits_at(size_type n) const
        {
            return std::make_pair(bases[2*n], bases[2*n+1]);
        }

    public:

        //@{ Constants that represent how a sequence was born.
        /// This sequence was created randomly.
        static const tag_type RAND;
        /// This sequence was created from a specified string
        static const tag_type INIT;
        //@}

        /** Explicitly update the global sequence count to start from a
         *  particular number.
         *  new_start_tag will be given to the next sequence created.
         *  Used when running multiple simulations one after the other.
         */
        static void renumber_sequences(tag_type new_start_tag);

        /** Constructs a random sequence of length \a n.
         *  This is considered initial, so no mutations are present.
         */
        Sequence(size_type n);

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
        Sequence(const Sequence& s1, const Sequence& s2,
                 size_type num_template_switches);

        //@{
        /** Delete copy constructors as we want tags to be unique.
         */
        Sequence(Sequence const&) = delete;
        void operator=(Sequence const&) = delete;
        //@}

        //@{
        /** But make the objects moveable, to create containers of them.
         */
        Sequence(Sequence&&) = default;
        Sequence& operator=(Sequence&&) = default;
        //@}

        /// Returns length of the sequence
        size_type get_length() const { return (bases.size()/2); }

        /// Returns the unique label for this sequence
        tag_type get_tag() const { return tag; }

        /** Returns the tags of the sequences that this sequence was created
         *  from.
         *  See the definition of parent_tags for more details.
         */
        std::pair<tag_type, tag_type> get_parent_tags() const { return parent_tags; }

        /** Returns the character for a base at a given position.
         */
        inline char char_at(size_type n) const
        {
            return Consts::NUC_BOOL2CHAR(bits_at(n));
        }

        /** Changes the nucleotide at position \a n to \a new_nucleotide.
         *
         *  If the new_nucleotide is the same as the original nucleotide in the
         *  string, the mutation disappears, else a mutation is created.
         *  It can also be specified whether or not the mutation is lethal.
         */
        void point_mutate(size_type n, char new_nucleotide, bool is_lethal = false);

        /** Returns the raw nucleotide sequence as a string.
         */
        std::string as_string() const;

        /** Tests whether this sequence is active (can transpose) or not.
         *  Returns true if and only if there are no lethal mutations.
         */
        bool is_active() const { return lethal_mutations.empty(); }

        /** Returns how many mutations are present in this sequence.
         */
        size_type num_mutations() const { return mutations.size(); }

        /** Returns sequence similarity to initial sequence.
         */
        double init_seq_similarity() const
        {
            return (100.0-(100.0*mutations.size())/this->get_length());
        }

        //@{
        /** Computes pairwise distances between two sequences.
         *  This is the standard edit distance score, and is the number of
         *  mismatches (because insertions and deletions are not possible in this
         *  system).
         */

        /** Pairwise distances.
         *  Between two sequences or between a sequence and a string.
         */
        friend size_type operator *(const Sequence& s1, const Sequence& s2);
        friend size_type operator *(const Sequence& s1, std::string s2);

        /** Pairwise sequence dissimilarity (as a percentage).
         *  Similarity is 100-dissimilarity.
         */
        friend double operator %(const Sequence& s1, const Sequence& s2);
        friend double operator %(const Sequence& s1, std::string s2);
        //@}
    };
}

#endif //SEQUENCE_H
