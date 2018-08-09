#include "rand_maths.h"

// Declaration of global random number generator
namespace rcombinator
{
    RandMaths& RNG = RandMaths::get_instance();
}

using namespace rcombinator;

RandMaths::RandMaths()
{
    re.seed(std::chrono::system_clock::now().time_since_epoch().count());
}

/*static*/ RandMaths& RandMaths::get_instance()
{
    static RandMaths instance;
    return instance;
}

void RandMaths::set_specific_seed(long seed)
{
    re.seed(seed);
}

void RandMaths::set_random_seed()
{
    re.seed(std::chrono::system_clock::now().time_since_epoch().count());
}

bool RandMaths::rand_bit()
{
    static std::uniform_int_distribution<int> bit_gen(0, 1);
    // implicity convert 0 or 1 to bool
    return bit_gen(re);
}

int RandMaths::rand_int(int low, int high)
{
    if (low > high)
    {
        throw Exception("low is > high");
    }
    using Dist = std::uniform_int_distribution<int>;
    static Dist uid {};
    return uid(re, Dist::param_type{low,high-1});
}

double RandMaths::rand_real(double low /*= 0.0*/, double high /*= 1.0*/)
{
    if (low > high)
    {
        throw Exception("low is > high");
    }
    using Dist = std::uniform_real_distribution<double>;
    static Dist urd {};
    return urd(re, Dist::param_type{low, high});
}

long RandMaths::rand_poisson(double mean)
{
    if (mean <= 0)
    {
        throw Exception("mean is <= 0 for Poisson distribution");
    }
    using Dist = std::poisson_distribution<long>;
    static Dist pd {};
    return pd(re, Dist::param_type{mean});
}

std::set<int> RandMaths::sample_without_replacement(int low, int high, int m)
{
    if (low > high)
    {
        throw Exception("low is > high");
    }
    if (m < 0)
    {
        throw Exception("sample size is < 0");
    }
    std::set<int> s;
    while(s.size() != m)
    {
        s.insert(rand_int(low, high));
    }
    return s;
}

std::pair<int, int> RandMaths::sample_distinct_pair(int low, int high)
{
    if (high - low <= 1)
    {
        throw Exception("Cannot sample distinct values in such a small range");
    }
    int a = rand_int(low, high);
    int b = a;
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

int RandMaths::choose_event(double * events, long num_events)
{
    double rand_num = rand_real();
    double running_total = 0;
    for (long i=0; i<num_events; ++i)
    {
        running_total += events[i];
        if (running_total >= rand_num) return i;
    }
    throw Exception("Event probabilities do not add up to at least 1");
}
