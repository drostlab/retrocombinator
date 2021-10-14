/**
 * @file
 *
 * \brief To test the functionality of the Pool class.
 */

#ifndef TEST_POOL_H
#define TEST_POOL_H

#include "test_header.h"
#include "../pool.h"
#include <string>

namespace retrocombinator
{
    int test_pool()
    {
        test_initialize();

        try {
            std::string init_seq("TTTTTTTTTTTTTTTTTTTT");
            Pool pool(init_seq, init_seq.length(), 10,
                      /* ActivityTracker */ 5, 1.0,
                      /* Mutator */ "TN93",
                      /* Burst */ 0.8, 3, 20,
                      /* Recomb */ 3, 0.1,
                      /* Select */ 0.0);

            pool.step(0.1);

            std::vector<std::string> expected {
                "2: TTTTTTTTTTTTTTTTTTTT",
                "3: TTATTTTTTTATTGTTTTTT",
                "4: TTCTTTATTTTTTGTTTTTT",
                "5: TTTTTTTTTTTTTTTTTTTT",
                "6: TTTTTTTTGTTTTTTATTTT",
                "7: TTTTTTTTTTTTTATTTTGT",
                "8: TTTTTTTTTTTTTTGTTTTT",
                "9: TTCTTTTTTTCTTTTTTGTT",
               "11: TTTTTTTTTTTTTTTTTTTT",
               "12: TTATTTTTTTATTTTTTTTT",
               "13: TTTTTTTTTTTTTATTTTGT",
               "14: TTTTTTTTTTTTTTTTTTTT",
               "15: TTTTTTTTTTTTTTTTTTGT",
               "16: TATTTTTTTTTTTTTTTTTT",
               "17: TTTTTTTTTTTTTTTTTTTT",
               "18: TTTTTTTTGTTTTTTATTTT",
               "19: TTATTTTTTTATTGGTTTTT",
               "20: TTTTTTTTTTTTTTTATTTT",
               "21: TTTTTTTTGTTTTTGTTTTT",
               "22: TTTTTTTTTTTTTTTTTTTT"
            };
            assert(expected.size() == pool.get_pool().size());

            size_type i = 0;
            for(const auto& seq : pool.get_pool()) {
                assert(expected[i] == (std::to_string(seq.get_tag()) + ": " + seq.as_string()));
                ++i;
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
#endif // TEST_POOL_H

