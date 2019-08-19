/**
 * @file
 *
 * \brief To test the functionality of the EvolutionWithFlags class.
 *
 */
#ifndef TEST_EVOLUTION_WITH_FLAGS_H
#define TEST_EVOLUTION_WITH_FLAGS_H

#include "test_header.h"
#include "evolution_with_flags.h"

namespace retrocombinator
{
    /// Tests EvolutionWithFlags
    int test_evolution_with_flags()
    {
        try
        {
            RNG.set_specific_seed(0);
            Sequence::renumber_sequences(0);
            Family::renumber_families(0);

            // TEST 1 - basic
            Sequence S1(50);
            std::vector<std::string> base_strings1(4, S1.as_string());

            PointMutator pm1("K80", 50, 10, 0.5);
            Output output1("test_obj/test_with_flags_1.out", 60,
                           60, 30, 10, 6);
            output1.set_init_seq(S1.as_string());

            EvolutionWithFlags e1(60, 2,
                                  0.5, 1,
                                  20, 30);
            e1.evolve(output1, pm1, base_strings1, 1);
            assert (files_same("test_obj/test_with_flags_1.out",
                               "test_cpp/benchmark_with_flags_1.test"));

            // TEST 2 - with selection
            RNG.set_specific_seed(0);
            Sequence::renumber_sequences(0);
            Family::renumber_families(0);

            Sequence S2(50);
            std::vector<std::string> base_strings2(4, S2.as_string());

            PointMutator pm2("K80", 50, 10, 0.5);
            Output output2("test_obj/test_with_flags_2.out", 60,
                           60, 30, 10, 6);
            output2.set_init_seq(S2.as_string());

            EvolutionWithFlags e2(60, 2,
                                  0.5, 1,
                                  20, 30);
            e2.set_selection_threshold(50);
            e2.evolve(output2, pm2, base_strings2, 1);
            assert (files_same("test_obj/test_with_flags_2.out",
                               "test_cpp/benchmark_with_flags_2.test"));

            // TEST 3 - with families
            RNG.set_specific_seed(0);
            Sequence::renumber_sequences(0);
            Family::renumber_families(0);

            Sequence S3(50);
            std::vector<std::string> base_strings3(4, S3.as_string());

            PointMutator pm3("K80", 50, 10, 0.5);
            Output output3("test_obj/test_with_flags_3.out", 60,
                           60, 30, 10, 6);
            output3.set_init_seq(S3.as_string());

            // TODO: change 5 to 60
            EvolutionWithFlags e3(5, 2,
                                  0.5, 1,
                                  20, 30);
            e3.use_families_at(0.25, 80);
            e3.evolve(output3, pm3, base_strings3, 1);
            assert (files_same("test_obj/test_with_flags_3.out",
                               "test_cpp/benchmark_with_flags_3.test"));
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
