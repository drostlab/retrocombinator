/**
 * @file
 *
 * \brief Definitions of basic helper functions.
 *
 * A collection of short, useful functions and data structures
 */
#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <algorithm>
#include <cmath>
#include <vector>

#include "exception.h"

namespace rcombinator
{
    /** Checks whether a number lies within a range.
     *  The bounds are [inclusive, exclusive).
     */
    inline bool is_in_range(long test, long lb, long ub)
    {
        return ((test >= lb) && (test < ub));
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

    /** Returns the SummaryStats for a list of values.
     *  This is not a linear operation as it sorts the values.
     */
    template <typename T, typename T_cont>
    SummaryStats<T, T_cont> get_summary_stats(std::vector<T> xs)
    {
        if (xs.size() == 0)
        {
            throw Exception("Vector empty, cannot compute summary statistics");
        }

        std::sort(xs.begin(), xs.end());
        T_cont n = T_cont(xs.size());

        SummaryStats<T, T_cont> s;

        s.min    = xs.front();
        s.max    = xs.back();

        //TODO: sort this out
        if (ceil(n/4.0) == n/4.0)
            s.q25    = (xs[n/4.0 - 1] + xs[n/4.0])/2.0;
        else
            s.q25    = xs[n/4.0 - 1];

        s.median = (xs[floor((n-1)/2.0)] + xs[ceil((n-1)/2.0)])/2.0;

        if (ceil(3*n/4.0) == 3*n/4.0)
            s.q75    = (xs[3*n/4.0 - 1] + xs[3*n/4.0])/2.0;
        else
            s.q75    = xs[3*n/4.0 - 1];

        T_cont total = 0.0;
        for (auto x : xs)
        {
            total += x;
        }
        s.mean = total/n;

        return s;
    }
}

#endif // UTILITIES_HPP
