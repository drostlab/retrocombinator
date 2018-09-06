/**
 * @file
 *
 * \brief To test the functionality of the Output class.
 *
 */
#ifndef TEST_OUTPUT_H
#define TEST_OUTPUT_H

#include <cassert>

#include "output.h"

namespace rcombinator
{
    int test_output()
    {
        try
        {
            RNG.set_specific_seed(0);
            Sequence::renumber_sequences(0);

            Output o1("test_output.out", 60,
                      30, 6, 2, 60);
            o1.set_init_seq("TTTT");

            // Test basic frequency of outputting and header
            o1.print_header();

            std::vector<Sequence> ss;
            ss.emplace_back(4);
            ss.emplace_back("TTTT");
            ss.emplace_back(ss[0], ss[1], 1);

            // Test each of the individual print functions
            for (long t = 0; t <= 60; ++t)
            {
                o1.print(t, t, ss);
            }
            return 0;
        }
        catch (Exception e)
        {
            std::cout << e.what() << std::endl;
            return 1;
        }
    }
}

#endif //TEST_OUTPUT_H
