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

#include "constants.h"
#include "exception.h"

namespace retrocombinator
{
    /** \namespace retrocombinator::Utils
     *  To store some useful functions in a namespace and prevent conflicts.
     */
    namespace Utils
    {
        /** Checks whether a number lies within a range.
         *  The bounds are [inclusive, exclusive).
         */
        inline bool is_in_range(size_type test, size_type lb, size_type ub)
        {
            return ((lb <= test) && (test < ub));
        }

        /** Breaks a set into two clusters.
         *  \param n the number of data points
         *  \param dist the nXn distance matrix between the data points
         *  Takes a distance matrix D, where D(i, j) is the distance between i
         *  and j, with D(i, i) being 0 for all i.
         *  Returns a vector of indices that belong to the first cluster (the
         *  second cluster corresponds to everything else).
         *
         *  Algorithm:
         *      Start with n clusters
         *          Compute the cluster distance between all pairs of clusters
         *          Where cluster distance is:
         *              average distance of points from one cluster to the other
         *          Pick the two closest clusters, and merge them
         */
        cluster_type cluster(const dist_type& dist, size_type n);


        /** Computes the cluster distance between two clusters.
         *  Equal to the average of all pairs (a1, a2) in C1 X C2.
         */
        double cluster_dist(const dist_type& dist, size_type n,
                            const cluster_type& C1,
                            const cluster_type& C2);
    }
}

#endif // UTILITIES_H
