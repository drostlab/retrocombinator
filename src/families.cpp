#include "families.h"
#include "utilities.h"
#include "sequence.h"

using namespace retrocombinator;

Families::Families(size_type join_threshold_max, size_type max_num_representatives):
    join_threshold_max(join_threshold_max), max_num_representatives(max_num_representatives)
{
}

void Families::update(const Pool& pool, const size_type timestep) {
    if (representatives.size() >= max_num_representatives) { return; }

    auto dist_mat = pool.get_distance_matrix();
    auto clusters = Utils::cluster_slink(dist_mat, pool.get_pool().size(),
                                         join_threshold_max);
    auto local_representatives = Utils::select_representatives(clusters);

    auto it = pool.get_pool().begin();
    for (size_type i=0,r=0; i < pool.get_pool().size(); ++i, ++it) {
        if (i < local_representatives[r]) { continue; }

        bool new_rep = true;
        for (size_type k=0; k < representatives.size(); ++k) {
            if (((*it) * representatives[k].raw_sequence) < join_threshold_max) {
                new_rep = false;
                break;
            }
        }
        if (new_rep) {
            representatives.push_back(
                Representative(it->as_string(), it->num_mutations(), timestep));
            rep_pairwise_dist.emplace_back();
            for (size_type i=0; i<representatives.size(); ++i) {
                rep_pairwise_dist[i].emplace_back(
                    representatives[i].raw_sequence * representatives.back().raw_sequence);
            }
        }
        if (representatives.size() >= max_num_representatives) { return; }
        ++r;
    }

}
