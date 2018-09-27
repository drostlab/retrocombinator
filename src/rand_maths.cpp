#include "constants.h"
#include "rand_maths.h"

// Declaration of global random number generator
namespace rcombinator
{
    RandMaths& RNG = RandMaths::get_instance();
}

using namespace rcombinator;

RandMaths::RandMaths()
{
    last_seed = std::chrono::system_clock::now().time_since_epoch().count();
    re.seed(last_seed);
}
/*static*/ RandMaths& RandMaths::get_instance()
{
    static RandMaths instance;
    return instance;
}

void RandMaths::set_specific_seed(size_type seed)
{
    last_seed = seed;
    re.seed(seed);
}

void RandMaths::set_random_seed()
{
    last_seed = std::chrono::system_clock::now().time_since_epoch().count();
    re.seed(last_seed);
}

bool RandMaths::rand_bit()
{
    static std::uniform_int_distribution<size_type> bit_gen(0, 1);
    // implicity convert 0 or 1 to bool
    return bit_gen(re);
}

size_type RandMaths::rand_int(size_type low, size_type high)
{
    if (low >= high)
    {
        std::string msg = "rand_int: low is >= high: " + std::to_string(low) + " > " +
            std::to_string(high);
        throw Exception(msg);
    }
    using Dist = std::uniform_int_distribution<size_type>;
    static Dist uid {};
    return uid(re, Dist::param_type{low,high-1});
}

double RandMaths::rand_real(double low /*= 0.0*/, double high /*= 1.0*/)
{
    if (low >= high)
    {
        std::string msg = "rand_real: low is >= high: " + std::to_string(low) + " > " +
            std::to_string(high);
        throw Exception(msg);
    }
    using Dist = std::uniform_real_distribution<double>;
    static Dist urd {};
    return urd(re, Dist::param_type{low, high});
}

size_type RandMaths::rand_poisson(double mean)
{
    if (mean <= 0)
    {
        throw Exception("mean is <= 0 for Poisson distribution");
    }
    using Dist = std::poisson_distribution<size_type>;
    static Dist pd {};
    return pd(re, Dist::param_type{mean});
}

std::set<size_type> RandMaths::sample_without_replacement(size_type low, size_type high, size_type m)
{
    if (low >= high)
    {
        std::string msg = "sample_without_replacement: low is >= high: " +
            std::to_string(low) + " > " +
            std::to_string(high);
        throw Exception(msg);
    }
    if (m < 0)
    {
        throw Exception("sample size is < 0");
    }
    if (m > high - low)
    {
        throw Exception("Sample space is too small to pick from");
    }
    std::set<size_type> s;
    while(s.size() != m)
    {
        s.insert(rand_int(low, high));
    }
    return s;
}

std::pair<size_type, size_type> RandMaths::sample_distinct_pair(size_type low, size_type high)
{
    if (high - low <= 1)
    {
        throw Exception("Cannot sample distinct values in such a small range");
    }
    size_type a = rand_int(low, high);
    size_type b = a;
    while (b == a)
    {
        b = rand_int(low, high);
    }

    return std::make_pair(a, b);
}

bool RandMaths::test_event(double event_probability)
{
    if (event_probability < 0 || event_probability > 1)
    {
        throw Exception("Probability not in range");
    }
    return (rand_real() < event_probability);
}

size_type RandMaths::choose_event(const double events[], size_type num_events)
{
    double rand_num = rand_real();
    double running_total = 0;
    for (size_type i=0; i<num_events; ++i)
    {
        running_total += events[i];
        if (running_total >= rand_num) return i;
    }
    if (fabs(running_total-1.0) > Consts::DOUBLE_TOLERANCE)
    {
        throw Exception("Event probabilities do not add up to 1");
    }
    else
    {
        // else it is the last event
        return (num_events-1);
    }
}
