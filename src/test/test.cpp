#include <iostream>

#include "test_rand_maths.h"
#include "test_activity_tracker.h"
#include "test_sequence.h"
#include "test_point_mutation_models.h"
#include "test_mutator.h"
#include "test_pool.h"
#include "test_simulation.h"
#include "test_utilities.h"

using namespace std;
using namespace retrocombinator;

int main()
{
    cout << "Testing Modules (0 is success)" << endl;

    cout << "Testing Rand Maths: " << endl;
    cout << test_rand_maths() << endl;

    cout << "Testing Utilities: " << endl;
    cout << test_utilities() << endl;

    cout << "Testing Activity Tracker: " << endl;
    cout << test_activity_tracker() << endl;

    cout << "Testing Sequence: " << endl;
    cout << test_sequence() << endl;

    cout << "Testing Point Mutation Models: " << endl;
    cout << test_point_mutation_models() << endl;

    cout << "Testing Mutator: " << endl;
    cout << test_mutator() << endl;

    cout << "Testing Pool (& Burster): " << endl;
    cout << test_pool() << endl;

    cout << "Testing Simulation: " << endl;
    cout << test_simulation() << endl;

    return 0;
}
