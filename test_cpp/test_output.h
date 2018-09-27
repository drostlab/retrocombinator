/**
 * @file
 *
 * \brief To test the functionality of the Output class.
 *
 */
#ifndef TEST_OUTPUT_H
#define TEST_OUTPUT_H

#include "test_header.h"
#include "output.h"

namespace rcombinator
{
    /// Tests the Output class
    int test_output()
    {
        try
        {
            RNG.set_specific_seed(0);
            Sequence::renumber_sequences(0);
            Family::renumber_families(0);

            Output o1("test_obj/test_output.out", 60,
                      60, 30, 10, 6);
            o1.set_init_seq("TTTT");

            // Test basic frequency of outputting and header
            o1.print_header();

            std::list<Family> fs;
            fs.emplace_back(Consts::INIT_FAMILY_COUNT);
            fs.front().seqs.emplace_back(4);
            fs.front().seqs.emplace_back("TTTT");
            fs.front().seqs.emplace_back(fs.front().seqs[0],
                                         fs.front().seqs[1], 1);
            fs.emplace_back(fs.front().get_tag());
            fs.back().seqs.emplace_back("AAAA");

            // Test each of the individual print functions
            for (size_type t = 0; t <= 60; ++t)
            {
                o1.print(t, t, fs);
            }

            assert (files_same("test_obj/test_output.out",
                               "test_cpp/benchmark_output.test"));
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
