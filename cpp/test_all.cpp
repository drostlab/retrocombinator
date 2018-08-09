#include <iostream>
#include <cassert>
#include "rand_maths.h"
#include "sequence.h"

using namespace std;
using namespace rcombinator;

int test_sequence()
{
    cout << "TESTING SEQUENCES MODULE" << endl
         << "---" << endl;

    // Check that random string generation works
    cout << endl << "TESTING: string generation" << endl;

    RNG.set_specific_seed(0);
    Sequence S0(10);
    cout << "Sequence0 is: " << S0.as_string() << endl;
    assert (S0.as_string() == "TAACGCACAT");

    // Check that conversion between string and sequence works
    cout << endl << "TESTING: string conversion" << endl;

    std::string seq_string1("TCGATCGATCGA");
    Sequence S1(seq_string1);

    cout << "String1 is: " << seq_string1 << endl;
    cout << "Sequence1 is: " << S1.as_string() << endl;
    assert (S1.as_string() == seq_string1);

    // Check that point mutation works
    cout << endl << "TESTING: point mutation conversion" << endl;

    std::string seq_string2("TTTTTTTTTTTT");
    Sequence S2(seq_string2);

    cout << "Sequence 2 is: " << S2.as_string() << endl;
    S2.point_mutate(2, 'C');
    cout << "Sequence 2 mutated is: " << S2.as_string() << endl;
    assert (S2.as_string() == "TTCTTTTTTTTT");
    S2.point_mutate(4, 'A');
    cout << "Sequence 2 mutated is: " << S2.as_string() << endl;
    assert (S2.as_string() == "TTCTATTTTTTT");

    // Check that sequence comparison works
    cout << endl << "TESTING: sequence comparison" << endl;

    std::string seq_string3("TTTTTTTTTTTT");
    Sequence S3(seq_string3);

    cout << "Sequence 2 is: " << S2.as_string() << endl;
    cout << "Sequence 3 is: " << S3.as_string() << endl;
    auto diff = S2*S3;
    cout << "Their difference is " << diff << endl;
    assert (diff == 2);

    // Checking that recombining works
    cout << endl << "TESTING: recombination" << endl;

    RNG.set_specific_seed(0);
    std::string seq_string4("AAAAAAAAAAAA");
    Sequence S4(seq_string4);
    std::string seq_string5("GGGGGGGGGGGG");
    Sequence S5(seq_string5);

    cout << "Sequence 4 is: " << S4.as_string() << endl;
    cout << "Sequence 5 is: " << S5.as_string() << endl;

    Sequence S6(S4, S5, 1);
    cout << "Recombining them with num_switches = 1 " << S6.as_string() << endl;
    assert (S6.as_string() == "AAGGGGGGGGGG");

    Sequence S7(S4, S5, 2);
    cout << "Recombining them with num_switches = 2 " << S7.as_string() << endl;
    assert (S7.as_string() == "GGGAAAGGGGGG");

    Sequence S8(S4, S5, 3);
    cout << "Recombining them with num_switches = 3 " << S8.as_string() << endl;
    assert (S8.as_string() == "AAAAAGGGAAAG");

    // Done testing
    cout << endl << "---" << endl
        << "TESTED SEQUENCES MODULE" << endl;

    return 0;
}

int main()
{
    test_sequence();
}
