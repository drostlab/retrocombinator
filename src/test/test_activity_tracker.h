/**
 * @file
 *
 * \brief To test the functionality of the ActivityTracker class.
 *
 */

#ifndef TEST_ACTIVITY_TRACKER_H
#define TEST_ACTIVITY_TRACKER_H

#include "test_header.h"
#include "../activity_tracker.h"

#include <iostream>

namespace retrocombinator
{
    int test_activity_tracker()
    {
        test_initialize();

        try {

            ActivityTracker at(10, 2, 1);

            assert (at.get_sequence_length() == 10);
            assert (at.is_critical(0) == true);
            assert (at.is_critical(1) == true);

            assert (at.is_critical(2) == false);
            assert (at.is_critical(3) == false);
            assert (at.is_critical(6) == false);
            assert (at.is_critical(7) == false);

            assert (at.is_critical(8) == true);
            assert (at.is_critical(9) == true);

            assert (at.check_activity(0) == true);
            assert (at.check_activity(1) == false);
            assert (at.check_activity(2) == false);

            ActivityTracker at_hi(10, 2, 0.9);
            assert (at_hi.check_activity(1) == false);
            assert (at_hi.check_activity(2) == false);

            ActivityTracker at_low(1000, 2, 0.01);
            assert (at_low.check_activity(1) == true);
            assert (at_low.check_activity(2) == true);
            assert (at_low.check_activity(5) == true);
            assert (at_low.check_activity(999) == false);

            ActivityTracker at_mid(10, 2, 0.4);
            assert (at_mid.check_activity(1) == true);
            assert (at_mid.check_activity(2) == false);

            return 0;
        }
        catch (Exception e)
        {
            std::cout << e.what() << std::endl;
            return 1;
        }
    }
}

#endif // TEST_ACTIVITY_TRACKER_H

