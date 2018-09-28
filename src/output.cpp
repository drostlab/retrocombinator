#include "output.h"
#include "rand_maths.h"

using namespace rcombinator;
using namespace std;

Output::Output(const std::string& filename_out, size_type final_time,
               size_type num_out_tags,
               size_type num_out_init,
               size_type num_out_seqs,
               size_type num_out_pair):
    final_time(final_time),
    to_output_tags(num_out_tags != 0 ?
                        floor(double(final_time)/num_out_tags) : final_time),
    to_output_init(num_out_init != 0 ?
                        floor(double(final_time)/num_out_init) : final_time),
    to_output_seqs(num_out_seqs != 0 ?
                        floor(double(final_time)/num_out_seqs) : final_time),
    to_output_pair(num_out_pair != 0 ?
                        floor(double(final_time)/num_out_pair) : final_time)
{
    fout.open(filename_out, std::fstream::out | std::fstream::trunc);
}

Output::~Output()
{
    fout.close();
}

void Output::print_header()
{
    fout << RNG.get_last_seed() << endl;
}

void Output::set_init_seq (std::string _init_seq)
{
    init_seq = _init_seq;
}

void Output::print_init(const seqs_type& seqs)
{
    if (init_seq.size() == 0)
    {
        throw Exception("initial sequence not set for output");
    }
    fout << "I" << endl;
    for (const auto& seq : seqs)
    {
        fout << (seq * init_seq) << " ";
    }
    fout << endl;
}

void Output::print_pair(const std::list<Family>& families)
{
    fout << "P" << endl;
    for (auto f1 = families.begin(); f1 != families.end(); ++f1)
    {
        for (auto s1 = f1->seqs.begin(); s1 != f1->seqs.end(); ++s1)
        {
            for (auto s2 = std::next(s1); s2 != f1->seqs.end(); ++s2)
            {
                fout << ((*s1) * (*s2)) << " ";
            }
            for (auto f2 = std::next(f1); f2 != families.end(); ++f2)
            {
                for (auto s2 = f2->seqs.begin(); s2 != f2->seqs.end(); ++s2)
                {
                    fout << ((*s1) * (*s2)) << " ";
                }
            }
        }
    }
    fout << endl;
}

void Output::print_seqs(const seqs_type& seqs)
{
    fout << "S" << endl;
    for (const auto& seq : seqs)
    {
        fout << seq.as_string() << endl;
    }
}

void Output::print_seq_tags(const seqs_type& seqs)
{
    fout << "T" << endl;
    fout << seqs.size() << endl;
    for (const auto& seq : seqs)
    {
        fout << seq.get_tag();
        if (seq.is_active())
        {
            fout << "*";
        }
        else
        {
            fout << "-";
        }
        fout << "(";
        auto p_tags = seq.get_parent_tags();
        if (p_tags.first == Sequence::RAND)
        {
            fout << "R/R";
        }
        else if (p_tags.first == Sequence::INIT)
        {
            fout << "I/I";
        }
        else
        {
            fout << p_tags.first << "/" << p_tags.second;
        }
        fout << ") ";
    }
    fout << endl;
}

void Output::print(size_type time, double real_time,
                   const std::list<Family>& families)
{
    // beginning or ending
    bool bend = (time == final_time) ||  (time == 0);
    bool p_tags = to_output_tags ? (time % to_output_tags == 0 || bend) : true;
    bool p_init = to_output_tags ? (time % to_output_init == 0 || bend) : true;
    bool p_seqs = to_output_tags ? (time % to_output_seqs == 0 || bend) : true;
    bool p_pair = to_output_tags ? (time % to_output_pair == 0 || bend) : true;

    if (p_tags || p_init || p_seqs || p_pair)
    {
        // always print tags if we have to print something else
        p_tags = true;
        // print distance to initial sequence if we are printing raw sequences
        if (p_seqs) { p_init = true; }

        // for this timestep
        fout << "@" << endl;
        fout << time << " " << real_time << endl;
        fout << p_tags << " " << p_init << " " << p_seqs << " " << p_pair
             << endl;

        fout << "F" << endl;
        fout << families.size() << endl;
        for (const auto& family : families)
        {
            fout << family.get_tag() << " " << family.get_parent_tag() << endl;
            if (p_tags) print_seq_tags(family.seqs);
            if (p_init) print_init(family.seqs);
            if (p_seqs) print_seqs(family.seqs);
        }
        if (p_pair) print_pair(families);
    }
}

