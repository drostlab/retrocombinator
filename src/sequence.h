/**
 * @file
 *
 * \brief For the Sequence class and auxiliary functions relating to sequences
 */
#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "constants.h"
#include "activity_tracker.h"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace retrocombinator
{
    namespace Consts {

        //@{ Constants that represent how a sequence was born.
        /// This sequence was created randomly.
        const tag_type SEQUENCE_CREATED_RANDOMLY_TAG = -2;
        /// This sequence was created from a specified string
        const tag_type SEQUENCE_INITIALISED_EXTERNALLY_TAG = -1;
        //@}

    }

    /** To represent a DNA sequence and the mutations that it has
     *  undergone.
     *
     *  Keeps track of the actual sequence, mutations and critical mutations.
     */
    class Sequence
    {
    private:

        /// For the raw sequence
        typedef std::vector<bool> raw_sequence_type;

        /** An internal counter that is incremented every time a sequence is
         *  created.
         *  Used to assign each sequence a unique tag.
         */
        static tag_type global_sequence_count;

        /** To keep track of the activity of all the sequences.
         */
        static ActivityTracker activity_tracker;

        /** A number that uniquely identifies this sequence.
         *  This tag transcends activity (if an inactive sequence becomes active
         *  again, it has the same tag)
         */
        const tag_type tag;

        /** The parent tags that this sequence was created from.
         *  If this was created as Sequence(S1, S2), the tags are ordered as
         *  <S1.get_tag(), S2.get_tag()>.
         *  If this was created randomly, the tags are <RAND_TAG, RAND_TAG>.
         *  If this was created from a string, the tags are <INIT_TAG, INIT_TAG>.
         */
        const std::pair<tag_type, tag_type> parent_tags;

        /** Actual sequence of nucleotides.
         *  Stored as a string internally.
         */
        raw_sequence_type bases;

        ///@{
        /** Basic typedefs - hashed data structures for quick lookup.
         *  For keeping track of mutations and critical mutations.
         */
        typedef std::unordered_map<size_type, char> mutations_type;
        typedef std::unordered_set<size_type> critical_mutations_type;
        ///@}

        /** Positions of mutations and what the *original* nucleotide was.
         *  Stored as an unordered map locally.
         */
        mutations_type mutations;

        /** Positions of mutations that are critical.
         *  Internally stored as a set. This set is always a subset of
         *  \p mutations.keys.
         */
        critical_mutations_type critical_mutations;

        /** Whether or not this sequence is capable of transposition.
          */
        bool active_status;

        /** Returns the 2bit encoding for a base at a given position.
         */
        inline std::pair<bool, bool> bits_at(size_type n) const
        {
            return std::make_pair(bases[2*n], bases[2*n+1]);
        }

    public:
        /** Explicitly update the global sequence count to start from a
         *  particular number.
         *  new_start_tag will be given to the next sequence created.
         *  Used when running multiple simulations one after the other.
         */
        static void renumber_sequences(tag_type new_start_tag = 1);

        /** Use a specified activity tracker.
          */
        static void set_activity_tracker(ActivityTracker activity_tracker_);

        /** Constructs a random sequence.
         *  This is considered initial, so no mutations are present.
         */
        Sequence();

        /** Constructs a sequence from a given string.
         *  This is considered initial, so no mutations are present.
         */
        Sequence(std::string s);

        /** Constructs a sequence from recombining two other sequences.
         *
         *  The number of template switches has to be specified, and the
         *  positions at which the template switches are made is random.
         *
         *  The first sequence is the "active" sequence, and reading starts from
         *  there. Reading can start from either end of that sequence, and
         *  continue in that direction.
         *
         *  The mutations recorded are with respect to the original sequences.
         *  That is, the new sequence \a s_new will have a mutation \a m at
         *  position \a l if and only if the sequence \a s_old whose nucleotide
         *  is used for \a s_new at position \a l had mutation \a m present at
         *  that position.
         *
         */
        Sequence(const Sequence& s1, const Sequence& s2,
                 size_type num_template_switches);

        ///@{
        /** Delete copy constructors as we want tags to be unique.
         */
        Sequence(Sequence const&) = delete;
        void operator=(Sequence const&) = delete;
        ///@}

        ///@{
        /** But make the objects moveable, to create containers of them.
         */
        Sequence(Sequence&&) = default;
        Sequence& operator=(Sequence&&) = default;
        ///@}

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
         *  The activity tracker is used to determined whether or not a mutation
         *  is critical.
         *
         *  Returns true iff there is a mutation present at the end.
         */
        bool point_mutate(size_type n, char new_nucleotide);

        /** Returns the raw nucleotide sequence as a string.
         */
        std::string as_string() const;

        /** Tests whether this sequence is active (can transpose) or not.
         */
        bool is_active() const { return active_status; }

        /** Returns how many mutations are present in this sequence.
         */
        size_type num_mutations() const { return mutations.size(); }

        /** Returns how many critical region mutations are present in this sequence.
         */
        size_type num_critical_mutations() const { return critical_mutations.size(); }

        /** Returns sequence similarity to initial sequence.
         */
        double init_seq_similarity() const
        {
            return (1.0-(1.0*mutations.size())/this->get_length());
        }

        /** Pairwise distances between two sequences.
         *  This is the standard edit distance score, and is the number of
         *  mismatches (because insertions and deletions are not possible in
         *  this system).
          */
        friend size_type operator *(const Sequence& s1, const Sequence& s2);
        /** Pairwise distances between a sequence and a string.
         *  This is the standard edit distance score, and is the number of
         *  mismatches (because insertions and deletions are not possible in
         *  this system).
          */
        friend size_type operator *(const Sequence& s1, std::string s2);

        /** Pairwise dissimilarity between two sequences.
         *  Similarity is 1-dissimilarity.
          */
        friend double operator %(const Sequence& s1, const Sequence& s2);
        /** Pairwise dissimilarity between a sequence and a string.
         *  Similarity is 1-dissimilarity.
          */
        friend double operator %(const Sequence& s1, std::string s2);
    };

    /// A list of sequences
    typedef std::list<Sequence> sequence_list;

    /** Pairwise distances between two strings.
     *  This is the standard edit distance score, and is the number of
     *  mismatches (because insertions and deletions are not possible in
     *  this system).
      */
    size_type operator *(std::string s1, std::string s2);

    /** Pairwise dissimilarity between two strings.
      *  Similarity is 1-dissimilarity.
      */
    double operator %(std::string s1, std::string s2);
}

#endif //SEQUENCE_H
