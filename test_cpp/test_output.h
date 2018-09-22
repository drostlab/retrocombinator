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
    int test_output()
    {
        try
        {
            RNG.set_specific_seed(0);
            Sequence::renumber_sequences(0);
            Family::renumber_families(0);

            Output o1("test_obj/test_output.out", 60,
                      30, 6, 2, 60);
            o1.set_init_seq("TTTT");

            // Test basic frequency of outputting and header
            o1.print_header();

            std::vector<Family> fs;
            fs.emplace_back(Consts::INIT_FAMILY_COUNT);
            fs[0].seqs.emplace_back(4);
            fs[0].seqs.emplace_back("TTTT");
            fs[0].seqs.emplace_back(fs[0].seqs[0], fs[0].seqs[1], 1);
            fs.emplace_back(fs[0].get_tag());
            fs[1].seqs.emplace_back("AAAA");

            // Test each of the individual print functions
            for (long t = 0; t <= 60; ++t)
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