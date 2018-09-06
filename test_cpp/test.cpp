#include <iostream>

#include "test_sequence.h"
#include "test_point_mutation_models.h"
#include "test_point_mutator.h"
#include "test_output.h"
#include "test_evolution_without_flags.h"
#include "test_evolution_with_flags.h"

using namespace std;
using namespace rcombinator;

int main()
{
    cout << "Testing Modules (0 is success)" << endl;
    cout << "Testing Sequence: " << endl;
    cout << test_sequence() << endl;
    cout << "Testing Point Mutation Models: " << endl;
    cout << test_point_mutation_models() << endl;
    cout << "Testing Point Mutator: " << endl;
    cout << test_point_mutator() << endl;
    cout << "Testing Output: " << endl;
    cout << test_output() << endl;
    cout << "Testing Evolution Without Flags: " << endl;
    cout << test_evolution_without_flags() << endl;
    cout << "Testing Evolution With Flags: " << endl;
    cout << test_evolution_with_flags() << endl;

    return 0;
}
