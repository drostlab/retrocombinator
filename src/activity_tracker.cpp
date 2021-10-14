#include "rand_maths.h"
#include "activity_tracker.h"

using namespace retrocombinator;

ActivityTracker::ActivityTracker(size_type sequence_length, size_type critical_region_length,
        double inactive_probability):
    sequence_length(sequence_length),
    critical_region_length(critical_region_length),
    inactive_probability(inactive_probability)
{}

bool ActivityTracker::is_critical(size_type n) const
{
    return (n < critical_region_length) ||
        (n < sequence_length && (n+critical_region_length) >= sequence_length);
}

bool ActivityTracker::check_activity(size_type num_critical_mutations) const
{
    // P(staying active N mutations) = (1-x)^N
    double staying_alive = pow(1-inactive_probability, num_critical_mutations);

    // 0^0 case
    if (num_critical_mutations == 0) return true;
    return RNG.test_event(staying_alive);
}
