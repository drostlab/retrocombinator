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

#include "exception.h"

namespace rcombinator
{
    /** \namespace rcombinator::Utils
     *  To store some useful functions in a namespace and prevent conflicts.
     */
    namespace Utils
    {
        /** Checks whether a number lies within a range.
         *  The bounds are [inclusive, exclusive).
         */
        inline bool is_in_range(long test, long lb, long ub)
        {
            return ((lb <= test) && (test < ub));
        }

        /** Plain-Old-Data struct to store summary statistics for a list of values.
         *
         *  Is templated on T and T_cont, where
         *  T is a numeric type, and
         *  T_cont is a numeric type that can store fractional parts.
         *  Stores the quartiles and the mean for a list of values.
         */
        template <typename T, typename T_cont>
        struct SummaryStats
        {
            T      min;     ///< Minimum
            T_cont q25;     ///< First quartile, 25th percentile
            T_cont median;  ///< Median
            T_cont q75;     ///< Third quartile, 75th percentile
            T      max;     ///< Maximum
            T_cont mean;    ///< Arithmetic mean
        };
    }
}

#endif // UTILITIES_H
