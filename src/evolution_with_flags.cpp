#include "evolution_with_flags.h"
#include "rand_maths.h"
#include "utilities.h"

#include <iterator>
using namespace retrocombinator;

EvolutionWithFlags::EvolutionWithFlags(size_type num_jumps, double timestep,
                  double burst_probability, double burst_mean,
                  size_type max_active_copies, size_type max_total_copies):
    Evolution(num_jumps, timestep, burst_probability, burst_mean,
              max_active_copies),
    max_total_copies(max_total_copies),
    selection_threshold(0), // no selection bias initially
    fam_proportion(1.0), fam_percentage(100) // no family splitting initially
{}

void EvolutionWithFlags::burst_seqs(const size_type /*unused t*/,
                                    const double recomb_mean)
{
    // The number of sequences we have seen so far across all families.
    // Count active sequences whenever we see one or create one
    size_type num_active_seqs = 0;
    // Count total sequences for each family after bursting that family
    size_type num_total_seqs = 0;

    for (auto& family : families)
    {
        auto& seqs = family.seqs;

        // the number of sequences before this burst event
        const size_type prev_num_seqs = seqs.size();

        for (size_type i=0; i < prev_num_seqs; ++i)
        {
            if (seqs[i].is_active())
            {
                ++num_active_seqs;
                // this sequence is active, check if it bursts
                if (RNG.test_event(burst_probability))
                {
                    size_type num_new_seqs = RNG.rand_poisson(burst_mean);

                    for (size_type j = 0; j < num_new_seqs; ++j)
                    {
                        // choose a sequence to recombine with, but not one that
                        // was created in this round of burst events
                        size_type recomb_index = RNG.rand_int(0, prev_num_seqs);

                        // then create the new sequence by recombining
                        seqs.emplace_back(seqs[i], seqs[recomb_index],
                                          RNG.rand_poisson(recomb_mean));
                        // check if we have new active sequences
                        if (seqs.back().is_active())
                        {
                            ++num_active_seqs;
                            // TODO: have a check if at this stage we are going
                            // to burst too fast and throw a warning/exception
                            // if it goes too high
                        }
                    }
                }
            }
        }
        // add all the sequences from the current family
        num_total_seqs += seqs.size();
    }

    kill_sequences(num_active_seqs, num_total_seqs);
    if (fam_percentage < 100)
    {
        split_families();
    }
}

void EvolutionWithFlags::kill_sequences(size_type num_active_seqs,
                                        size_type num_total_seqs)
{
    // kill sequences below our selection threshold
    if (selection_threshold > 0)
    {
        for (auto& family : families)
        {
            auto& seqs = family.seqs;
            for (auto it=seqs.begin(); it!=seqs.end(); )
            {
                if (it -> init_seq_similarity() < selection_threshold)
                {
                    if (it -> is_active())
                    {
                        // one less active sequence
                        --num_active_seqs;
                    }
                    // and one less sequence overall
                    --num_total_seqs;
                    it = seqs.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }
    }

    // remove dead families
    for (auto family_it=families.begin(); family_it!=families.end(); )
    {
        if (family_it->seqs.size() == 0)
        {
            family_it = families.erase(family_it);
        }
        else
        {
            ++family_it;
        }
    }
    remove_dead_families();

    // then, kill sequences until we are within our limits
    while ((num_total_seqs > max_total_copies ||
           num_active_seqs > max_active_copies) && families.size() > 0)
    {
        size_type random_family_index = RNG.rand_int(0, families.size());
        auto& seqs = std::next(families.begin(), random_family_index)->seqs;


        auto to_delete = std::next(seqs.begin(), RNG.rand_int(0, seqs.size()));
        if (to_delete -> is_active())
        {
            // one less active sequence
            --num_active_seqs;
        }
        // and one less sequence overall
        --num_total_seqs;
        seqs.erase(to_delete);
    }
    remove_dead_families();
}

void EvolutionWithFlags::remove_dead_families()
{
    for (auto family_it=families.begin(); family_it!=families.end(); )
    {
        if (family_it->seqs.size() == 0)
        {
            family_it = families.erase(family_it);
        }
        else
        {
            ++family_it;
        }
    }
}

void EvolutionWithFlags::split_families()
{
    // the last family tag, split until we reach this
    auto last_family_tag = families.back().get_tag();
    bool continue_loop = true;
    for (auto family_it = families.begin();
         continue_loop && family_it != families.end();
         ++family_it)
    {
        if (family_it->get_tag() == last_family_tag)
        {
            // all families after this point have been created recently
            continue_loop = false;
        }

        // the number of pairwise similarities less than the threshold
        size_type num_dissimilar = 0;
        size_type fam_size = family_it->size();
        // compute distance matrix and perform the check
        dist_type dist_matrix(fam_size);
        for (size_type i=0; i<dist_matrix.size(); ++i)
        {
            dist_matrix[i].assign(fam_size, 0);
        }
        for (size_type i=0; i < fam_size; ++i)
        {
            for (size_type j=i+1; j < fam_size; ++j)
            {
                auto diss = family_it->seqs[i] % family_it->seqs[j];
                dist_matrix[i][j] = 100.0 - diss;
                dist_matrix[j][i] = dist_matrix[i][j];
                if (dist_matrix[i][j] < fam_percentage)
                {
                    ++num_dissimilar;
                }
            }
        }

        // if we haven't crossed the threshold, carry on
        if (double(num_dissimilar)/(fam_size*(fam_size+1)/2.0) > fam_proportion)
        {
            // use the clustering algorithm to subdivide this family into two
            // others
            cluster_type small_cluster = Utils::cluster(dist_matrix, fam_size);
            // the new family created from smaller cluster
            families.emplace_back(family_it->get_tag());
            for (auto index : small_cluster)
            {
                families.back().seqs.emplace_back(
                                       std::move(family_it->seqs[index]));
            }
            // reflect the fact that this family split up
            family_it->split();
            // remove the deleted sequences
            size_type num_deleted = 0;
            // NOTE: Need the indices to be in ascending order for this to work,
            //       that is: we need cluster_type to be of type std::set, not
            //       std::unordered_set
            for (auto index : small_cluster)
            {
                family_it->seqs.erase(std::next(family_it->seqs.begin(),
                                                index - num_deleted));
                // reflect the fact that all indices have been shifted by one
                // down
                ++ num_deleted;
            }
        }
    }
}

void EvolutionWithFlags::set_selection_threshold(double percentage)
{
    if (percentage < 0 || percentage > 100)
    {
        throw Exception("Percentage needs to be between 0 and 100");
    }
    selection_threshold = percentage;
}

void EvolutionWithFlags::use_families_at(double proportion, double percentage)
{
    if (proportion < 0 || proportion > 1.0)
    {
        throw Exception("Proportion needs to be between 0.0 and 1.0");
    }
    if (percentage < 0 || percentage > 100)
    {
        throw Exception("Percentage needs to be between 0 and 100");
    }

    fam_proportion = proportion;
    fam_percentage = percentage;
}
