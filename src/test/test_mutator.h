/**
 * @file
 *
 * \brief To test the functionality of the Mutator class.
 *
 */
#ifndef TEST_MUTATOR_H
#define TEST_MUTATOR_H

#include "test_header.h"
#include "../mutator.h"

namespace retrocombinator
{
    /// Tests Mutator
    int test_mutator()
    {
        test_initialize();
        try
        {
            ActivityTracker at(40, 5, 0.8);

            Sequence::renumber_sequences();
            Sequence::set_activity_tracker(at);

            Sequence s("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
            Mutator mutator("K80");
            assert (s.is_active());
            mutator.mutate_sequence(s, 5);
            assert (s.num_mutations() == 3);
            assert (s.as_string() == "TTTTTTTTTTTTTTTTTCTCTTTTTTTTTTTTTTTTTTCT");

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

#endif //TEST_MUTATOR_H
