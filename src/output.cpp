#include "output.h"
#include "rand_maths.h"

using namespace rcombinator;
using namespace std;

Output::Output(const std::string& filename_out, long final_time,
               long num_out_init,
               long num_out_pair,
               long num_out_seqs,
               long num_out_tags):
    final_time(final_time),
    to_output_init(floor(double(final_time)/num_out_init)),
    to_output_pair(floor(double(final_time)/num_out_pair)),
    to_output_seqs(floor(double(final_time)/num_out_seqs)),
    to_output_tags(floor(double(final_time)/num_out_tags))
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

void Output::print(long timestep, double real_time,
                   const std::list<Family>& families)
{
    if (timestep % to_output_tags == 0 ||
        timestep % to_output_init == 0 ||
        timestep % to_output_pair == 0 ||
        timestep % to_output_seqs == 0 ||
        timestep == final_time)
    {
        fout << "@" << endl;
        fout << timestep << " " << real_time << endl;

        fout << "F" << endl;
        fout << families.size() << endl;
        for (const auto& family : families)
        {
            fout << family.get_tag() << " " << family.get_parent_tag() << endl;
            print_seq_tags(family.seqs);

            if (timestep % to_output_init == 0 || timestep == final_time)
            {
                print_init(family.seqs);
                if (timestep % to_output_seqs == 0 || timestep == final_time)
                {
                    print_seqs(family.seqs);
                }
            }
        }
        if (timestep % to_output_pair == 0 || timestep == final_time)
        {
            print_pair(families);
        }
    }
}

