/**
 * @file
 *
 * \brief Definitions for enums/constants that are used throughout the project.
 *
 * More specifically,
 * - biological constants (things like nucleotide names, a fixed nucleotide
 *   ordering etc),
 * - \todo add default constants for the simulation here as well
 */
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include "exception.h"
#include <utility>

namespace rcombinator
{
    /** \namespace rcombinator::Consts
     *  To store all global constants that can be accessed from anywhere in the
     *  code.
     *  Stores biological constants and constants that are specific to the
     *  implementation of the simulation.
     */
    namespace Consts
    {
        /** \enum
         *  This defines an ordering on the nucleotides, used for arrays and
         *  transition matrices that work on nucleotides.
         */
        enum NUC_VALS
        {
            T = 0,          ///< Thymine
            C = 1,          ///< Cytosine
            A = 2,          ///< Adenine
            G = 3,          ///< Guanine
            NUC_COUNT = 4   ///< Number of nucleotides, used as an upper bound for loops
        };

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
}

#endif //CONSTANTS_HPP
