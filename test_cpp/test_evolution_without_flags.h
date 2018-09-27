/**
 * @file
 *
 * \brief To test the functionality of the EvolutionWithoutFlags class.
 *
 */
#ifndef TEST_EVOLUTION_WITHOUT_FLAGS_H
#define TEST_EVOLUTION_WITHOUT_FLAGS_H

#include "test_header.h"
#include "evolution_without_flags.h"

namespace rcombinator
{
    /// Tests EvolutionWithoutFlags
    int test_evolution_without_flags()
    {
        try
        {
            RNG.set_specific_seed(0);
            Sequence::renumber_sequences(0);
            Family::renumber_families(0);

            size_type NUM_SEQ = 4;
            Sequence S0(50);
            std::vector<std::string> base_strings(NUM_SEQ, S0.as_string());

            EvolutionWithoutFlags e(60, 2,
                                    0.5, 1,
                                    20);
            e.calculate_copy_number_tree(NUM_SEQ);

            std::fstream fout("test_obj/test_copy_tree.out", std::ios::out);
            const auto copy_tree = e.get_copy_tree();
            for (const auto& layer : copy_tree)
            {
                for (const auto& node : layer)
                {
                    fout << node.first << "/" << node.second << " ";
                }
                fout << std::endl;
            }
            assert (files_same("test_obj/test_copy_tree.out",
                               "test_cpp/benchmark_copy_tree.test"));

            PointMutator pm("K80", 50);
            Output output("test_obj/test_without_flags.out", 60,
                          60, 30, 10, 6);
            output.set_init_seq(S0.as_string());
            e.evolve(output, pm, base_strings, 1);
            assert (files_same("test_obj/test_without_flags.out",
                               "test_cpp/benchmark_without_flags.test"));
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
