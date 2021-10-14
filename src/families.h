/**
 * @file
 *
 *
 */

#ifndef FAMILIES_H
#define FAMILIES_H

#include "pool.h"
#include "representative.h"

namespace retrocombinator
{
    class Families
    {
    private:
        const size_type join_threshold_max;
        size_type max_num_representatives;

        std::vector<Representative> representatives;
        /// dist[i][j] stores the distance between rep_i and rep_j for i <= j
        dist_type rep_pairwise_dist;
    public:
        /**
          * \p join_threshold_max indicates that the distance between two
          * clusters must be at most \p join_threshold_max for them to be
          * considered the same family.
          *
          * Also, new representatives are saved only if they are more than
          * \p join_threshold_max away from previous representatives.
          */
        Families(size_type join_threshold_max, size_type max_num_representatives);

        double get_join_threshold_max() const { return join_threshold_max; }
        const std::vector<Representative>& get_representatives() const {
            return representatives;
        }

        const dist_type& get_representative_matrix() const {
            return rep_pairwise_dist;
        }
        void update(const Pool& pool, size_type timestep);

    };
}
#endif // FAMILIES_H

