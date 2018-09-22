/**
 * @file
 *
 * \brief To test the functionality of the EvolutionWithFlags class.
 *
 */
#ifndef TEST_EVOLUTION_WITH_FLAGS_H
#define TEST_EVOLUTION_WITH_FLAGS_H

#include "evolution_with_flags.h"
#include "output.h"
#include "point_mutator.h"
#include <cassert>

namespace rcombinator
{
    int test_evolution_with_flags()
    {
        try
        {
            RNG.set_specific_seed(0);
            Sequence::renumber_sequences(0);
            Family::renumber_families(0);

            Sequence S0(50);
            std::vector<std::string> base_strings(4, S0.as_string());

            PointMutator pm("K80", 50, 10, 0.5);
            Output output("test_obj/test_with_flags.out", 60,
                          30, 6, 60, 60);
            output.set_init_seq(S0.as_string());

            EvolutionWithFlags e(60, 2,
                                 0.5, 1,
                                 20, 30);
            e.evolve(output, pm, base_strings, 1);
            assert (files_same("test_obj/test_with_flags.out",
                               "test_cpp/benchmark_with_flags.test"));
            return 0;
        }
        catch (Exception e)
        {
            std::cout << e.what() << std::endl;
            return 1;
        }
    }
}

#endif //TEST_EVOLUTION_WITH_FLAGS_H
