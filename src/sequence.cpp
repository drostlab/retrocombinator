#include "sequence.h"
#include "rand_maths.h"
#include "utilities.h"

#include <cctype>
#include <iterator>
#include <algorithm>
#include <string>

namespace retrocombinator
{
    // Start counting from sequence 1 by setting this to 0 and always
    // incrementing before assigning a new tag
    tag_type Sequence::global_sequence_count = 0;
    // Dummy activity tracker
    ActivityTracker Sequence::activity_tracker = ActivityTracker(0, 0, 0.0);
}

namespace retrocombinator
{
    size_type operator *(const Sequence& s1, const Sequence& s2)
    {
        if (s1.get_length() != s2.get_length()) {
            throw Exception("Cannot compare sequences of different lengths.");
        }
        size_type differences = 0;
        for (size_type i=0; i<s1.get_length(); ++i)
        {
            if (s1.char_at(i) != s2.char_at(i))
            {
                ++differences;
            }
        }
        return differences;
    }

    size_type operator *(const Sequence& s1, std::string s2)
    {
        if (s1.get_length() != s2.size()) {
            throw Exception("Cannot compare sequences of different lengths.");
        }
        size_type differences = 0;

        for (size_type i=0; i<s1.get_length(); ++i)
        {
            if (s1.char_at(i) != s2[i])
            {
                ++differences;
            }
        }
        return differences;
    }

    size_type operator *(std::string s1, std::string s2)
    {
        if (s1.size() != s2.size()) {
            throw Exception("Cannot compare sequences of different lengths.");
        }
        size_type differences = 0;

        for (size_type i=0; i<s1.size(); ++i)
        {
            if (s1[i] != s2[i])
            {
                ++differences;
            }
        }
        return differences;
    }

    double operator %(const Sequence& s1, const Sequence& s2)
    {
        if (s1.get_length() != s2.get_length()) {
            throw Exception("Cannot compare sequences of different lengths.");
        }
        return (double(s1*s2))/double(s1.get_length());
    }
    double operator %(const Sequence& s1, std::string s2)
    {
        if (s1.get_length() != s2.size()) {
            throw Exception("Cannot compare sequences of different lengths.");
        }
        return (double(s1*s2))/double(s1.get_length());
    }

    double operator %(std::string s1, std::string s2)
    {
        if (s1.size() != s2.size()) {
            throw Exception("Cannot compare sequences of different lengths.");
        }
        return (double(s1*s2))/double(s1.size());
    }
}

using namespace retrocombinator;

void Sequence::renumber_sequences(tag_type new_start_tag)
{
    Sequence::global_sequence_count = new_start_tag - 1;
}

void Sequence::set_activity_tracker(ActivityTracker activity_tracker_)
{
    Sequence::activity_tracker = activity_tracker_;
}

std::string Sequence::as_string() const
{
    // bases.size() should be an exact multiple of 2
    std::string s(bases.size()/2, ' ');

    for(size_type i=0; i<s.size(); ++i)
    {
        s[i] = Consts::NUC_BOOL2CHAR(std::make_pair(bases[2*i], bases[2*i+1]));
    }
    return s;
}
Sequence::Sequence() :

    tag(Sequence::global_sequence_count + 1),
    parent_tags(Consts::SEQUENCE_CREATED_RANDOMLY_TAG, Consts::SEQUENCE_CREATED_RANDOMLY_TAG),
    bases(2*activity_tracker.get_sequence_length(), false) // assign 2n because we have 2 bits per nucleotide base
{
    ++Sequence::global_sequence_count;

    for (size_type i=0; i<bases.size(); ++i)
    {
        bases[i] = RNG.rand_bit();
    }
    this->active_status = true;
}

Sequence::Sequence(std::string s):
    tag(Sequence::global_sequence_count + 1),
    parent_tags(Consts::SEQUENCE_INITIALISED_EXTERNALLY_TAG,
                       Consts::SEQUENCE_INITIALISED_EXTERNALLY_TAG)
{
    ++Sequence::global_sequence_count;
    if (s.size() != activity_tracker.get_sequence_length()) {
        throw Exception("String length " + std::to_string(s.size()) +
                "does not match sequence length" +
                std::to_string(activity_tracker.get_sequence_length()));
    }
    bases.assign(2*s.size(), false);

    for (size_type i=0; i<s.size(); ++i)
    {
        auto bits = Consts::NUC_CHAR2BOOL(s[i]);
        bases[2*i]   = bits.first;
        bases[2*i+1] = bits.second;
    }
    this->active_status = true;
}

Sequence::Sequence(const Sequence& s1, const Sequence& s2,
                   size_type num_template_switches):
    tag(Sequence::global_sequence_count + 1),
    parent_tags(s1.get_tag(), s2.get_tag())
{
    ++Sequence::global_sequence_count;
    if (s1.get_length() != s2.get_length()) {
        throw Exception("Cannot recombine sequences of different lengths.");
    }
    size_type n = s1.get_length();
    // sanitize the number of times we are allowed to template switch
    if (num_template_switches > n-1)
    {
        num_template_switches = n-1;
    }

    const Sequence * s1_ptr = &s1;
    const Sequence * s2_ptr = &s2;
    const Sequence * sequences[] = { s1_ptr, s2_ptr };

    // We want to 'start' reading from either end of the active (first)
    // sequence, but for implementation sake, we always read from 0, so we
    // choose whether or not to read from the active sequence depending on the
    // parity of num_template_switches
    size_type curr;
    if (num_template_switches % 2 == 0) {
        // Always start and end in the first sequence, order of reading doesn't
        // matter
        curr = 0;
    } else {
        // Else, start at first, end at other sequence. So flip a coin instead
        // to simulate 'reading from either end'
        curr = RNG.rand_int(0, 2);
    }

    bases.assign(sequences[curr]->bases.begin(),
                 sequences[curr]->bases.end());
    this->mutations = sequences[curr]->mutations;
    this->critical_mutations = sequences[curr]->critical_mutations;

    // Indices at which we make a template switch (the nucleotides from that
    // index onward are chosen from the 'other' sequence).
    // Cannot include 0 because that would mean we have one fewer template
    // switch. So, we sample from 1 to (n-1) (note that the sampler excludes the
    // upper bound).
    std::set<size_type> posns_of_recomb =
        RNG.sample_without_replacement(1, n, num_template_switches);
    // If there are an odd number, add the last position as a place of
    // recombination too (this means we can just read from the other
    // sequence between consecutive values of posns_of_recomb).
    if (num_template_switches % 2 != 0) { posns_of_recomb.insert(n); }

    for (auto it = posns_of_recomb.begin();
         it != posns_of_recomb.end(); it = std::next(it, 2))
    {
        size_type beg = *it;
        size_type end = *std::next(it);

        // copy nucleotides from the other sequence
        for (size_type i = 2*beg; i < 2*end; ++i)
        {
            bases[i] = (sequences[1-curr]->bases)[i];
        }

        // make sure we are keeping track of the mutations from the base
        // sequences
        for (auto t : sequences[curr]->mutations)
        {
            if (Utils::is_in_range(t.first, beg, end))
            {
                this->mutations.erase(t.first);
            }
        }
        for (auto t : sequences[curr]->critical_mutations)
        {
            if (Utils::is_in_range(t, beg, end))
            {
                this->critical_mutations.erase(t);
            }
        }
        for (auto t : sequences[1-curr]->mutations)
        {
            if (Utils::is_in_range(t.first, beg, end))
            {
                this->mutations[t.first] = t.second;
            }
        }
        for (auto t : sequences[1-curr]->critical_mutations)
        {
            if (Utils::is_in_range(t, beg, end))
            {
                this->critical_mutations.insert(t);
            }
        }
    }
    this->active_status = activity_tracker.check_activity(this->num_critical_mutations());
}

bool Sequence::point_mutate(size_type n, char new_nucleotide)
{
    // only if there is something new to do
    if (char_at(n) != new_nucleotide)
    {
        auto it = mutations.find(n);
        if (it == mutations.end())
        {
            // if this position has never been changed before, it is a
            // new mutation, so store the original nucleotide
            mutations[n] = char_at(n);
            if (activity_tracker.is_critical(n))
            {
                critical_mutations.insert(n);
                active_status = activity_tracker.check_activity(this->num_critical_mutations());
            }
        }
        else if (it->second == new_nucleotide)
        {
            // if new_nucleotide is the same as the original, the
            // mutation has been reversed
            mutations.erase(it);
            critical_mutations.erase(n);
        }
        // change the actual sequence
        auto new_bits = Consts::NUC_CHAR2BOOL(new_nucleotide);
        bases[2*n] = new_bits.first;
        bases[2*n+1] = new_bits.second;

        // if there is a critical mutation, store its position
    }
    return (mutations.find(n) != mutations.end());
}

