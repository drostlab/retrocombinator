/**
 * @file
 *
 * \brief Definitions for enums/constants/functions that are used everywhere.
 *
 * More specifically,
 * - biological constants (things like nucleotide names, a fixed nucleotide
 *   ordering etc),
 * - implementation specific typedefs and constants
 */
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "exception.h"

#include <cmath>
#include <set>
#include <utility>
#include <vector>

namespace rcombinator
{
    /** \namespace rcombinator::Consts
     *  To store all constant values that we define.
     *  Stores biological constants and constants that are specific to the
     *  implementation of the simulation.
     */
    namespace Consts
    {
        /** Tolerance for double operations.
         */
        const double DOUBLE_TOLERANCE = pow(10.0, -8);

        /** This defines an ordering on the nucleotides, used for arrays and
         *  transition matrices that work on nucleotides.
         */
        enum NUC_VALS
        {
            T = 0,          ///< Thymine
            C = 1,          ///< Cytosine
            A = 2,          ///< Adenine
            G = 3,          ///< Guanine
            NUC_COUNT = 4   ///< Number of nucleotides
        };

        //@{
        /** Defaults for different point mutation models
         */
        const double K80_K      = 10;
        const double K80_SCALE  = 0.01;
        const double JC69_SCALE = 0.1;
        //@}

        /** Returns a character corresponding a nucleotide given its index.
         */
        inline char NUC_INT2CHAR(int index)
        {
            switch(index)
            {
                case NUC_VALS::T: return 'T';
                case NUC_VALS::C: return 'C';
                case NUC_VALS::A: return 'A';
                case NUC_VALS::G: return 'G';
                default: throw Exception("Not a valid nucleotide index");
            }
        }

        /** Returns the index of a nucleotide given its character form.
         */
        inline int NUC_CHAR2INT(char nucleotide)
        {
            switch(nucleotide)
            {
                case 'T': return NUC_VALS::T;
                case 'C': return NUC_VALS::C;
                case 'A': return NUC_VALS::A;
                case 'G': return NUC_VALS::G;
                default: throw Exception("Not a valid nucleotide");
            }
        }

        /** Returns the 2bit-encoding of a nucleotide given its character form.
         */
        inline std::pair<bool, bool> NUC_CHAR2BOOL(char nucleotide)
        {
            switch(nucleotide)
            {
                case 'T': return std::make_pair(false, false);
                case 'C': return std::make_pair(false, true );
                case 'A': return std::make_pair(true , false);
                case 'G': return std::make_pair(true , true );
                default: throw Exception("Not a valid nucleotide");
            }
        }

        /** Returns the character of a nucleotide given its 2bit-encoding.
         */
        inline char NUC_BOOL2CHAR(std::pair<bool, bool> bits)
        {
            if(!bits.first)
            {
                if(!bits.second) return 'T';
                else             return 'C';
            }
            else
            {
                if(!bits.second) return 'A';
                else             return 'G';
            }
        }
    }

    /// For transition matrices, rate matrices etc
    typedef double NucMatrix[Consts::NUC_COUNT][Consts::NUC_COUNT];

    /// For functions that return NucMatrix and accept no parameters
    typedef const double (*ReturnsNucMatrix())[Consts::NUC_COUNT];

    /// For functions that return NucMatrix and accept time as parameter
    typedef const double (*ReturnsNucMatrixFromDouble(double))[Consts::NUC_COUNT];

    /// For all indices and sizes
    typedef std::size_t size_type;

    //@{
    /** For clustering algorithms.
     */
    /// For a set of indices
    typedef std::set<size_type> cluster_type;
    /// For a distance matrix between data points
    typedef std::vector<std::vector<size_type>> dist_type;
    //@}

    /// For all integer-based codes
    typedef long tag_type;

    namespace Consts
    {
        /** The family tag to represent initial sequences in a simulation.
         */
        const tag_type INIT_FAMILY_COUNT = -1;
    }
}

#endif //CONSTANTS_H
