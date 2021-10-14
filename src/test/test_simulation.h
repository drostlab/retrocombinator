/**
 * @file
 *
 *
 */

#include "test_header.h"
#include "../simulation.h"

#ifndef TEST_SIMULATION_H
#define TEST_SIMULATION_H

namespace retrocombinator
{
    int test_simulation()
    {
        test_initialize();
        try {
            std::string init_seq("TTTTTTTTTTTTTTTTTTTT");

            Simulation simulation(
                init_seq, init_seq.length(), 10,
                /* ActivityTracker */ 5, 1.0,
                /* Mutator */ "TN93",
                /* Burst */ 0.8, 3, 20,
                /* Recomb */ 3, 0.1,
                /* Select */ 0.5,
                /* Family */ 0.7, 10,
                /* Timesteps */ 10, 0.1,
                /* Output */ "./test_obj/test_simulation.out", 2, 2, 2, 2, 0.5
            );

            std::vector<std::string> expected {
                    "3: TTCTTTTTGTATTTTGAATT",
                   "30: CTTAGTTTGTTTTTAGGCTT",
                   "31: GTTTAACACTTAATCTTTTA",
                   "33: GGTTTTGTCCCTCTGTTTTC",
                   "36: TATTTCTATCATTTGTTATT",
                   "40: TTTCCTATACTTTCGTCTTA",
                   "46: TTTTGTATTTTATATTTTGT",
                   "48: TTTTGGCTTATTTTTTTTTT",
                   "50: TTTTGATCTTTTTTGTTTAA",
                   "55: TCTTTTTTAATTTAGTTTTC",
                   "57: TCTTTGTTGTATCAGCTTTT",
                   "58: TTTTCTGTGCTTTAGTTTAT",
                   "59: TTTTTTTCGCTTTTTTATTT",
                   "60: TTTTTGTTGATTTAGATTTT",
                   "61: ATTTATTTGGATAAGTTTGT",
                   "62: GTTTAGTAGTTTTTCTCTTT",
                   "63: TTTTTATCCTTTTTGTTTTT",
                   "64: TTTTGTACCTTATATTTTTT",
                   "65: TTTTTAATACTTTCGTCTTT"
            };
            simulation.print_seed(false, RNG.get_last_seed());
            simulation.simulate();

            assert(expected.size() == simulation.get_pool().size());

            size_type i = 0;
            for(const auto& seq : simulation.get_pool()) {
                assert(expected[i] == (std::to_string(seq.get_tag()) + ": " + seq.as_string()));
                ++i;
            }

            assert(files_same("./test_obj/test_simulation.out",
                              "./src/test/test_simulation.expected"));
            return 0;
        }
        catch (Exception e)
        {
            std::cout << e.what() << std::endl;
            return 1;
        }
    }
}

#endif // TEST_SIMULATION_H

