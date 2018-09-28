#include "sequence.h"
#include "rand_maths.h"
#include "utilities.h"

#include <iterator>
#include <algorithm>

namespace rcombinator
{
    tag_type Sequence::global_sequence_count = -1;
    const long Sequence::RAND = -10;
    const long Sequence::INIT = -20;
}

namespace rcombinator
{
    size_type operator *(const Sequence& s1, const Sequence& s2)
    {
        auto min_size = std::min(s1.get_length(), s2.get_length());
        auto max_size = std::max(s1.get_length(), s2.get_length());
        // the difference due to sequence length difference
        size_type extra = max_size - min_size;
        // the difference due to mutations
        size_type differences = 0;

        for (size_type i=0; i<min_size; ++i)
        {
            if (s1.char_at(i) != s2.char_at(i))
            {
                ++differences;
            }
        }
        return (differences + extra);
    }

    size_type operator *(const Sequence& s1, std::string s2)
    {
        auto min_size = std::min(s1.get_length(), size_type(s2.size()));
        auto max_size = std::max(s1.get_length(), size_type(s2.size()));
        // the difference due to sequence length difference
        size_type extra = max_size - min_size;
        // the difference due to mutations
        size_type differences = 0;

        for (size_type i=0; i<min_size; ++i)
        {
            if (s1.char_at(i) != s2[i])
            {
                ++differences;
            }
        }
        return (differences + extra);
    }

    double operator %(const Sequence& s1, const Sequence& s2)
    {
        auto min_size = std::min(s1.get_length(), size_type(s2.get_length()));
        return (100*double(s1*s2))/double(min_size);
    }
    double operator %(const Sequence& s1, std::string s2)
    {
        auto min_size = std::min(s1.get_length(), size_type(s2.size()));
        return (100*double(s1*s2))/double(min_size);
    }
}

using namespace rcombinator;

void Sequence::renumber_sequences(tag_type new_start_tag)
{
    Sequence::global_sequence_count = new_start_tag - 1;
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
Sequence::Sequence(size_type n) :

    bases(2*n, false) // assign 2n because we have 2 bits per nucleotide base
{
    ++Sequence::global_sequence_count;
    this->tag = Sequence::global_sequence_count;
    this->parent_tags = std::make_pair(Sequence::RAND, Sequence::RAND);

    for (size_type i=0; i<bases.size(); ++i)
    {
        bases[i] = RNG.rand_bit();
    }
}

Sequence::Sequence(std::string s) : bases(2*s.size(), false)
{
    ++Sequence::global_sequence_count;
    this->tag = Sequence::global_sequence_count;
    this->parent_tags = std::make_pair(Sequence::INIT, Sequence::INIT);

    for (size_type i=0; i<s.size(); ++i)
    {
        auto bits = Consts::NUC_CHAR2BOOL(s[i]);
        bases[2*i]   = bits.first;
        bases[2*i+1] = bits.second;
    }
}

Sequence::Sequence(const Sequence& s1, const Sequence& s2,
                   size_type num_template_switches)
{
    ++Sequence::global_sequence_count;
    this->tag = Sequence::global_sequence_count;
    this->parent_tags = std::make_pair(s1.get_tag(), s2.get_tag());

    const Sequence * s1_ptr = &s1;
    const Sequence * s2_ptr = &s2;
    const Sequence * sequences[] = { s1_ptr, s2_ptr };
    size_type curr = RNG.rand_int(0, 2); // index of current sequence

    size_type n = sequences[curr]->get_length();
    bases.assign(sequences[curr]->bases.begin(),
                 sequences[curr]->bases.end());
    // sanitize the number of times we are allowed to template switch
    if (num_template_switches > n-1)
    {
        num_template_switches = n-1;
    }

    this->mutations = sequences[curr]->mutations;
    this->lethal_mutations = sequences[curr]->lethal_mutations;

    // Indices at which we make a template switch (the nucleotides from that
    // index onward are chosen from the 'other' sequence).
    // Cannot include 0 because that would mean we have one fewer template
    // switch. So, we sample from 1 to (n-1) (note that the sampler exludes the
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
        for (auto t : sequences[curr]->lethal_mutations)
        {
            if (Utils::is_in_range(t, beg, end))
            {
                this->lethal_mutations.erase(t);
            }
        }
        for (auto t : sequences[1-curr]->mutations)
        {
            if (Utils::is_in_range(t.first, beg, end))
            {
                this->mutations[t.first] = t.second;
            }
        }
        for (auto t : sequences[1-curr]->lethal_mutations)
        {
            if (Utils::is_in_range(t, beg, end))
            {
                this->lethal_mutations.insert(t);
            }
        }
    }
}

void Sequence::point_mutate(size_type n, char new_nucleotide,
                            bool is_lethal /* = false */)
{
    // only if there is something new to do
    if (char_at(n) != new_nucleotide)
    {
        auto it = mutations.find(n);
        bool mutated = true; // if at the end there is a mutation at position n
        if (it == mutations.end())
        {
            // if this position has never been changed before, it is a
            // new mutation, so store the original nucleotide
            mutations[n] = char_at(n);
        }
        else if (it->second == new_nucleotide)
        {
            // if new_nucleotide is the same as the original, the
            // mutation has been reversed
            mutations.erase(it);
            lethal_mutations.erase(n);
            mutated = false;
        }
        // change the actual sequence
        auto new_bits = Consts::NUC_CHAR2BOOL(new_nucleotide);
        bases[2*n] = new_bits.first;
        bases[2*n+1] = new_bits.second;

        // if there is a lethal mutation, store its position
        if (mutated && is_lethal)
        {
            lethal_mutations.insert(n);
        }
    }
}

