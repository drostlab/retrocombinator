#include <iostream>

#include "rand_maths.h"
#include "utilities.h"

using namespace rcombinator;
using namespace std;

static RandMaths& r = RandMaths::initializeRandMaths(1);

double test_main()
{
    auto ans = r.rand_real();
    return ans;
}

double test_other()
{
    auto ans = is_in_range(10, 11, 14);
    return ans;
}

double test_new()
{
    auto ans = r.rand_int(10, 100);
    return ans;
}

int main()
{
    cout << test_main() << endl;
    cout << test_other() << endl;
    cout << test_new() << endl;
}
