/**
 * @file
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
     *  A collection of short, useful functions and data structures.
     *  Stored in a class to prevent namespace conflicts
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

        /// Type for a set of indices that represent a cluster
        typedef std::set<size_type> cluster_type;

        /** Returns a set of clusters (using SLINK)
         *  \param n the number of data points
         *  \param dist the nXn distance matrix between the data points, the
         *  distance between \c i and \c j is given by <tt>dist[i, j]</tt>, and
         *  we assume <tt>dist[i, i] == 0</tt> for all \c i
         *  \param join_threshold_max we merge two for as long as the distance
         *  between them is < \a join_threshold_max (once the closest distance
         *  between two clusters becomes >= \a join_threshold_max this, we stop
         *  clustering)
         *  \return a sequence of clusters, where each cluster is a collection
         *  of indices belonging to it
         */
        static std::vector<cluster_type> cluster_slink(dist_type dist, size_type n,
                size_type join_threshold_max);

        /** Selects a representative from each cluster
          * \param clusters a sequence of clusters, where each cluster has all
          * the indices belonging to it
          * \return a sequence of indices, the representatives for each cluster
          */
        static std::vector<size_type>
        select_representatives(std::vector<cluster_type> clusters);

    };
}

#endif // UTILITIES_H
