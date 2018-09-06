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

void Output::print_init(const std::vector<Sequence>& seqs)
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

void Output::print_pair(const std::vector<Sequence>& seqs)
{
    fout << "P" << endl;
    for (auto it = seqs.begin(); it != seqs.end(); ++it)
    {
        for (auto jt = std::next(it); jt != seqs.end(); ++jt)
        {
            fout << ((*it) * (*jt)) << " ";
        }
    }
    fout << endl;
}

void Output::print_seqs(const std::vector<Sequence>& seqs)
{
    fout << "S" << endl;
    for (const auto& seq : seqs)
    {
        fout << seq.as_string() << endl;
    }
}

void Output::print_tags(const std::vector<Sequence>& seqs)
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
                   const std::vector<Sequence>& seqs)
{
    if (timestep % to_output_tags == 0 ||
        timestep % to_output_init == 0 ||
        timestep % to_output_pair == 0 ||
        timestep % to_output_seqs == 0 ||
        timestep == final_time)
    {
        fout << "@" << endl;
        fout << timestep << " " << real_time << endl;
        print_tags(seqs);

        if (timestep % to_output_init == 0 || timestep == final_time)
        {
            print_init(seqs);
        }

        if (timestep % to_output_pair == 0 || timestep == final_time)
        {
            print_pair(seqs);
        }

        if (timestep % to_output_seqs == 0 || timestep == final_time)
        {
            print_seqs(seqs);
        }
    }
}

