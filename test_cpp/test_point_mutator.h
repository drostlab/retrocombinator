/**
 * @file
 *
 * \brief To test the functionality of the Point Mutator class.
 *
 */
#ifndef TEST_POINT_MUTATOR_H
#define TEST_POINT_MUTATOR_H

#include <cassert>
#include <iostream>

#include "point_mutator.h"

namespace rcombinator
{
    int test_point_mutator()
    {
        try
        {
            RNG.set_specific_seed(0);
            Sequence::renumber_sequences(0);

            Sequence s("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
            PointMutator pm("K80", 40, 20, 0.5);
            assert (s.is_active());
            pm.mutate_sequence(s, 1 );
            assert (s.num_mutations() == 1);
            assert (s.as_string() == "TCTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
            assert (!s.is_active());
            return 0;
        }
        catch (Exception e)
        {
            std::cout << e.what() << std::endl;
            return 1;
        }
    }
}

#endif //TEST_POINT_MUTATOR_H
