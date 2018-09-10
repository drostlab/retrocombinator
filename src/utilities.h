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
        inline bool is_in_range(size_type test, size_type lb, size_type ub)
        {
            return ((lb <= test) && (test < ub));
        }
    }
}

#endif // UTILITIES_H
