/**
 * @file
 *
 * \brief Definitions of basic helper functions.
 *
 * A collection of short, useful functions and data structures
 */
#ifndef UTILITIES_H
#define UTILITIES_H

#include <algorithm>
#include <cmath>
#include <vector>

#include "constants.h"
#include "exception.h"

namespace retrocombinator
{
    /**
     *  To store some useful functions in a namespace and prevent conflicts.
     */
    class Utils
    {
    public:
        /** Checks whether a number lies within a range.
         *  The bounds are [inclusive, exclusive).
         */
        static inline bool is_in_range(size_type test, size_type lb, size_type ub)
        {
            return ((lb <= test) && (test < ub));
        }

        /// Type for a set (cluster) of indices
        typedef std::set<size_type> cluster_type;

        /** Returns a set of clusters (using SLINK)
         *  \param n the number of data points
         *  \param dist the nXn distance matrix between the data points
         *  \param join_threshold_max we cluster whilst we can merge two
         *  clusters with distance < join_threshold_max between them - if the
         *  closest distance between two clusters becomes >= than this, we stop
         *  clustering
         *
         *  Takes a distance matrix D, where D(i, j) is the distance between i
         *  and j, with D(i, i) being 0 for all i.
         *
         */
        static std::vector<cluster_type> cluster_slink(dist_type dist, size_type n,
                size_type join_threshold_max);

        /// Selects a representative from each cluster
        static std::vector<size_type>
        select_representatives(std::vector<cluster_type> clusters);

    };
}

#endif // UTILITIES_H
