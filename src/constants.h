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
#include <list>
#include <set>
#include <utility>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace retrocombinator
{
    /** \namespace retrocombinator::Consts
     *  Stores biological constants and constants that are specific to an
     *  implementation of the simulation.
     */
    namespace Consts
    {
        /** Tolerance for operations on variables of datatype double.
         */
        const double DOUBLE_TOLERANCE = pow(10.0, -8);

        /** This defines an ordering on the nucleotides, it is used for arrays
         *  and transition matrices that work on nucleotides.
         */
        enum NUC_VALS
        {
            T = 0,          ///< Thymine
            C = 1,          ///< Cytosine
            A = 2,          ///< Adenine
            G = 3,          ///< Guanine
            NUC_COUNT = 4   ///< Number of nucleotides
        };


        ///@{
        /** Converts between different forms of representing a nucleotide (its
         * index based on NUC_VALS, its representation as two consecutive bits
         * based on that index, and its character representation - 'T', 'C', 'A'
         * or 'G')
         * \copydoc NUC_VALS
         */
        /** \param index The nucleotide index, based on NUC_VALS
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
         /**  \param nucleotide The character for a nucleotide, 'T', 'C', 'A' or
           *  'G'
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
         /**  \param nucleotide The character for a nucleotide, 'T', 'C', 'A' or
           *  'G'
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
        /** \param bits Two bits that when interpreted as a number correspond to
         *  a nucleotide index
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
        ///@}
    }

    /// Type for transition matrices and rate matrices
    typedef double NucMatrix[Consts::NUC_COUNT][Consts::NUC_COUNT];

    /// Type for functions that return NucMatrix and accept no parameters
    typedef const double (*ReturnsNucMatrix())[Consts::NUC_COUNT];

    /// Type for functions that return NucMatrix and accept time as parameter
    typedef const double (*ReturnsNucMatrixFromDouble(double))[Consts::NUC_COUNT];

    /// Type for all indices, sizes, and edit distances
    typedef std::size_t size_type;
    /// For all integer-based codes
    typedef long tag_type;

    /// Type for a row in a distance matrix
    typedef std::vector<size_type> dist_row_type;
    /// Type for a distance matrix
    typedef std::vector<dist_row_type > dist_type;

}

#endif //CONSTANTS_H
