/**
 * @file
 *
 * \brief
 *
 */
#ifndef TEST_HEADER_H
#define TEST_HEADER_H

#include <cassert>
#include <cstdlib>
#include <string>

#include "rand_maths.h"

namespace rcombinator
{
    /** Simple utility to check if two files are identical or not.
     *  Needs the command-line utility diff, on a Unix machine, to work.
     */
    bool files_same(std::string file1, std::string file2)
    {
        std::string difftool = "diff";
        std::string cmd = difftool + " " + file1 + " " + file2;
        auto result = system(cmd.c_str());
        return (result == 0);
    }

    /** Initialises a test harness, with a default seed.
     */
    void test_initialize(size_type seed = 0)
    {
        RNG.set_specific_seed(seed);
    }
}

#endif // TEST_HEADER_H

