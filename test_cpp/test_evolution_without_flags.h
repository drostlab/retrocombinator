/**
 * @file
 *
 * \brief To test the functionality of the EvolutionWithoutFlags class.
 *
 */
#ifndef TEST_EVOLUTION_WITHOUT_FLAGS_H
#define TEST_EVOLUTION_WITHOUT_FLAGS_H

#include <cassert>

#include "evolution_without_flags.h"

namespace rcombinator
{
    int test_evolution_without_flags()
    {
        try
        {
            RNG.set_specific_seed(0);
            Sequence::renumber_sequences(0);

            Sequence S0(50);
            std::vector<std::string> base_strings(4, S0.as_string());

            PointMutator pm("K80", 50);

            Output output("test_evolution_without_flags.out", 60,
                          30, 6, 2, 60);
            output.set_init_seq(S0.as_string());

            EvolutionWithoutFlags e(60, 2,
                                    0.5, 1,
                                    30, 20);
            e.evolve(output, pm, base_strings, 1);
            return 0;
        }
        catch (Exception e)
        {
            std::cout << e.what() << std::endl;
            return 1;
        }
    }
}

#endif //TEST_EVOLUTION_WITHOUT_FLAGS_H
