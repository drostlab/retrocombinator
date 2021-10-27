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
    /** To store all families of retrotranposons that emerge during a
      * simulation, by saving a representative for each family.
      */
    class Families
    {
    private:
        /** join_threshold_max indicates that the distance between two
          * clusters must be at most \p join_threshold_max for them to be
          * considered the same family.
          */
        const size_type join_threshold_max;

        /** The maximum number of families to keep track of (we stop keeping
         *  track of families that emerge once this threshold is passed)
          */
        size_type max_num_representatives;

        /// What the actual representatives for each family are
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

        /// Returns the maximum permitted distance between two clusters
        double get_join_threshold_max() const { return join_threshold_max; }

        /// What are the representatives of each family?
        const std::vector<Representative>& get_representatives() const {
            return representatives;
        }

        /** What is the pairwise distance between the representatives of each
          * family?
          */
        const dist_type& get_representative_matrix() const {
            return rep_pairwise_dist;
        }
        /** Store new representatives if need, and re-calculate the pairwise
          * distance matrix between representatives if needed
          */
        void update(const Pool& pool, size_type timestep);

    };
}
#endif // FAMILIES_H

