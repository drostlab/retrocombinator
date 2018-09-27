/**
 * @file
 *
 * \brief
 *
 */
#ifndef TEST_SIMULATION_H
#define TEST_SIMULATION_H

#include "test_header.h"
#include "simulation.h"

namespace rcombinator
{
    /// Tests all the wrapper functions to set-up and run simulations
    int test_simulation()
    {
        try
        {
            simulate_without_flags(4, 50,
                                   "K80", 60, 2,
                                   0.5, 1, 20, 1,
                                   "test_obj/test_simulation_without_flags.out",
                                   60, 30, 10, 6,
                                   false, true, 0,
                                   0, 0);
            assert (files_same("test_obj/test_simulation_without_flags.out",
                               "test_cpp/benchmark_simulation_without_flags.test"));

            simulate_with_flags(4, 50,
                                "K80", 10, 0.5, 60, 2,
                                0.5, 1, 20, 30, 1,
                                50, 0.25, 80,
                                "test_obj/test_simulation_with_flags.out",
                                60, 30, 10, 6,
                                false, true, 0,
                                0, 0);
            assert (files_same("test_obj/test_simulation_with_flags.out",
                               "test_cpp/benchmark_simulation_with_flags.test"));
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

