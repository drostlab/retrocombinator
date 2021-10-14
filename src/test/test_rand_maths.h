/**
 * @file
 *
 * \brief To test the functionality of the RandMaths class.
 *
 */

#ifndef TEST_RAND_MATHS_H
#define TEST_RAND_MATHS_H

#include "test_header.h"

#include <iostream>

namespace retrocombinator
{
    int test_rand_maths()
    {
        test_initialize();

        try {

            std::vector<double> k_1 {0.0, 1.0, 2.0, 5.0, 0.0, 0.0, 0.0,10.0, 0.0};
            auto ans_1 = RNG.choose_events<double>(k_1, 100);
            std::vector<size_type> expected_1{0, 4,10,24, 0, 0, 0,62, 0};
            assert (std::equal(ans_1.begin(), ans_1.end(),
                               expected_1.begin(), expected_1.end()));

            std::vector<size_type> k_2 { 1, 1, 2, 4};
            auto ans_2 = RNG.choose_events<size_type>(k_2, 100);
            std::vector<size_type> expected_2{13,12,28,47};
            assert (std::equal(ans_2.begin(), ans_2.end(),
                               expected_2.begin(), expected_2.end()));

            auto ans_3 = RNG.choose_items(
                    std::vector<size_type>   { 0, 1, 2, 0, 0, 5, 1, 0},  20);
            std::vector<size_type> expected_3{ 0, 1, 2, 0, 0, 5, 1, 0};
            assert (std::equal(ans_3.begin(), ans_3.end(),
                               expected_3.begin(), expected_3.end()));

            auto ans_4 = RNG.choose_items(
                    std::vector<size_type>   { 1, 1, 2, 0, 0, 5, 1,10},  10);
            std::vector<size_type> expected_4{ 0, 0, 0, 0, 0, 2, 1, 7};
            assert (std::equal(ans_4.begin(), ans_4.end(),
                               expected_4.begin(), expected_4.end()));

            return 0;
        }
        catch (Exception e)
        {
            std::cout << e.what() << std::endl;
            return 1;
        }
    }
}
#endif // TEST_RAND_MATHS_H

