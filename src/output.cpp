#include "output.h"

using namespace retrocombinator;

Output::Output(std::string filename_out, size_type final_timestep,
    size_type num_init_dist, size_type num_pair_dist,
    size_type num_fam_size, size_type num_fam_dist,
    size_type max_seq_dist_incl):
    final_timestep(final_timestep),
    to_print_init_dist(num_init_dist == 0 ? final_timestep + 1 :
                        ceil(double(final_timestep)/num_init_dist)),
    to_print_pair_dist(num_pair_dist == 0 ? final_timestep + 1 :
                        ceil(double(final_timestep)/num_pair_dist)),
    to_print_fam_size(num_fam_size == 0 ? final_timestep + 1 :
                        ceil(double(final_timestep)/num_fam_size)),
    to_print_fam_dist(num_fam_size == 0 ? final_timestep + 1 :
                        ceil(double(final_timestep)/num_fam_dist)),
    max_seq_dist_incl(max_seq_dist_incl)
{
    fout.open(filename_out, std::fstream::out | std::fstream::trunc);
}

Output::~Output() {
    fout.close();
}

void Output::output(size_type t, const Pool& pool, const Families& families) {
    bool p_init_dist = (t % to_print_init_dist == 0 ||
            (t == final_timestep && to_print_init_dist <= final_timestep));
    bool p_pair_dist = (t % to_print_pair_dist == 0 ||
            (t == final_timestep && to_print_pair_dist <= final_timestep));
    bool p_fam_size = (t % to_print_fam_size == 0 ||
            (t == final_timestep && to_print_fam_size <= final_timestep));
    bool p_fam_dist = (t % to_print_fam_dist == 0 ||
            (t == final_timestep && to_print_fam_dist <= final_timestep));

    if (p_init_dist) { print_initial_dist(t, pool); }
    if (p_pair_dist) { print_pairwise_dist(t, pool); }
    if (p_fam_size) { print_family_sizes(t, families, pool); }
    if (p_fam_dist) { print_family_dist(t, families); }
}

void Output::print_initial_dist(size_type t, const Pool& pool)
{
    fout << "Init<" << std::endl;
    fout << "@" << t << std::endl;
    fout << "!" << pool.get_pool().size() << std::endl;

    for (const auto& seq : pool.get_pool()) {
        fout << seq.get_tag() << ":"
             << (seq.get_parent_tags().first < 0 ? -1 : seq.get_parent_tags().first)
             << ":"
             << (seq.get_parent_tags().second < 0 ? -1 : seq.get_parent_tags().second)
             << ":"
             << seq.num_mutations()
             << ":"
             << (seq.is_active() ? "T" : "F") << std::endl;
    }
    fout << ">Init" << std::endl;
}

void Output::print_pairwise_dist(size_type t, const Pool& pool)
{
    fout << "Pair<" << std::endl;
    fout << "@" << t << std::endl;
    fout << "!" << pool.get_pool().size() << std::endl;

    size_type d;
    for (auto it = pool.get_pool().begin(); it != pool.get_pool().end(); ++it) {
        for (auto jt = std::next(it); jt != pool.get_pool().end(); ++jt) {
            d = (*it) * (*jt);
            if(d <= max_seq_dist_incl) {
                fout << it->get_tag() << ":" << jt->get_tag() << ":" << d << std::endl;
            }
        }
    }

    fout << ">Pair" << std::endl;
}

void Output::print_family_sizes(size_type t, const Families& families, const Pool& pool)
{
    fout << "FamTags<" << std::endl;
    fout << "@" << t << std::endl;
    fout << "!" << families.get_representatives().size() << std::endl;
    fout << "!" << pool.get_pool().size() << std::endl;

    for (auto rep : families.get_representatives()) {
        fout << rep.tag << ":" << rep.creation_timestep << ":";
        for (const auto& seq : pool.get_pool()) {
            if(seq % rep.raw_sequence < families.get_join_threshold_max()) {
                fout << seq.get_tag() << ",";
            }
        }
        fout << std::endl;
    }
    fout << ">FamTags" << std::endl;
}

void Output::print_family_dist(size_type t, const Families& families)
{
    fout << "FamDist<" << std::endl;
    fout << "@" << t << std::endl;
    fout << "!" << families.get_representatives().size() << std::endl;

    const auto& reps = families.get_representatives();
    const auto& matrix = families.get_representative_matrix();
    for (size_type i = 0; i < reps.size(); ++i) {
        for (size_type j = i+1; j < reps.size(); ++j) {
            if(matrix[i][j] <= max_seq_dist_incl) {
                fout << reps[i].tag << ":" << reps[j].tag << ":" << matrix[i][j] << std::endl;
            }
        }
    }

    fout << ">FamDist" << std::endl;
}

void Output::print_params(
    std::string sequence, size_type sequence_length, size_type num_initial_copies,
    size_type critical_region_length, double inactive_probability,
    std::string mutation_model,
    double burst_probability, double burst_mean, size_type max_total_copies,
    double recomb_mean, double recomb_similarity,
    double selection_threshold,
    double family_coherence, size_type max_num_representatives,
    size_type num_steps, double time_per_step,
    std::string filename_out,
    size_type num_init_dist, size_type num_pair_dist,
    size_type num_fam_size, size_type num_fam_dist,
    double min_output_similarity
    )
{
    fout << "Param<" << std::endl;

    std::string header = "SequenceParams";
    fout << header + "_" + "sequenceLength:" <<
        (sequence.empty() ? sequence_length : sequence.length())
        << std::endl;
    fout << header + "_" + "initialSequence:" << sequence << std::endl;
    fout << header + "_" + "numInitialCopies:" <<  num_initial_copies << std::endl;

    header = "ActivityParams";
    fout << header + "_" + "lengthCriticalRegion:" <<  critical_region_length << std::endl;
    fout << header + "_" + "probInactiveWhenMutated:" <<  inactive_probability << std::endl;

    header = "MutationParams";
    fout << header + "_" + "model:" << mutation_model  << std::endl;

    header = "BurstParams";
    fout << header + "_" + "burstProbability:" << burst_probability  << std::endl;
    fout << header + "_" + "burstMean:" << burst_mean  << std::endl;
    fout << header + "_" + "maxTotalCopies:" << max_total_copies  << std::endl;

    header = "RecombParams";
    fout << header + "_" + "recombMean:" << recomb_mean  << std::endl;
    fout << header + "_" + "recombSimilarity:" << recomb_similarity  << std::endl;

    header = "SelectionParams";
    fout << header + "_" + "selectionThreshold:" << selection_threshold  << std::endl;

    header = "FamilyParams";
    fout << header + "_" + "familyCoherence:" << family_coherence  << std::endl;
    fout << header + "_" + "maxFamilyRepresentatives:" << max_num_representatives  << std::endl;

    header = "SimulationParams";
    fout << header + "_" + "numSteps:" << num_steps  << std::endl;
    fout << header + "_" + "timePerStep:" << time_per_step  << std::endl;

    header = "OutputParams";
    fout << header + "_" + "outputFileName:" << filename_out  << std::endl;
    fout << header + "_" + "outputNumInitialDistance:" << num_init_dist  << std::endl;
    fout << header + "_" + "outputNumPairwiseDistance:" << num_pair_dist  << std::endl;
    fout << header + "_" + "outputNumFamilyLabels:" << num_fam_size  << std::endl;
    fout << header + "_" + "outputNumFamilyMatrix:" << num_fam_dist  << std::endl;
    fout << header + "_" + "outputMinPairwiseSimilarity:" << min_output_similarity  << std::endl;

    fout << ">Param" << std::endl;

}

void Output::print_params(bool to_seed, size_type seed) {
    fout << "Param<" << std::endl;

    std::string header = "SeedParams";
    fout << header + "_" + "toSeed:" << (to_seed ? "TRUE" : "FALSE") << std::endl;
    fout << header + "_" + "seed:" << seed  << std::endl;

    fout << ">Param" << std::endl;
}
