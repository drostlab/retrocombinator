/**
 * @file
 *
 * \brief To test the functionality of the Sequence class.
 *
 */
#ifndef TEST_SEQUENCE_H
#define TEST_SEQUENCE_H

#include "test_header.h"
#include "sequence.h"

namespace retrocombinator
{
    /// Tests the Sequence class
    int test_sequence()
    {
        test_initialize();
        Sequence::renumber_sequences(0);

        // Testing string to bool conversion
        std::string seq_string1("TCGATCGATCGA");
        Sequence S0(seq_string1);

        assert (S0.as_string() == seq_string1);

        // Testing random sequence generation
        Sequence S1(10);
        assert (S1.as_string() == "GGGGCATAAT");

        // Testing non-lethal point mutations
        std::string seq_string2("TTTTTTTTTTTT");
        Sequence S2(seq_string2);
        assert (S2.num_mutations() == 0);

        S2.point_mutate(2, 'C');
        assert (S2.as_string() == "TTCTTTTTTTTT");
        assert (S2.num_mutations() == 1);

        S2.point_mutate(4, 'A');
        assert (S2.as_string() == "TTCTATTTTTTT");
        assert (S2.num_mutations() == 2);

        // Testing lethal point mutations
        assert (S2.is_active());
        S2.point_mutate(8, 'G', true);
        assert (S2.as_string() == "TTCTATTTGTTT");
        assert (S2.num_mutations() == 3);
        // Testing sequence similarity as a percentage
        assert (S2.init_seq_similarity() == 0.75);
        assert (!S2.is_active());

        // Testing diff operator
        std::string seq_string3("TTTTTTTTTTTT");
        Sequence S3(seq_string3);

        assert (S2 * S3 == 3);
        assert (S2 % S3 == 0.25);
        assert (S2 * "TTTTTTTTTTTT" == 3);
        assert (S2 % "TTTTTTTTTTTT" == 0.25);

        // Testing recombination
        std::string seq_string4("AAAAAAAAAAAA");
        Sequence S4(seq_string4);

        std::string seq_string5("GGGGGGGGGGGG");
        Sequence S5(seq_string5);

        Sequence S6(S4, S5, 1);
        Sequence S7(S4, S5, 2);
        Sequence S8(S4, S5, 3);

        assert (S6.as_string() == "GGGGGGGGGAAA");
        assert (S7.as_string() == "GGGGGGAGGGGG");
        assert (S8.as_string() == "AGGGGGGGGGAG");

        // Testing individual sequence tagging
        assert (S0.get_tag() == 0);
        assert (S1.get_tag() == 1);
        assert (S8.get_tag() == 8);

        // Testing parent tagging
        assert (S0.get_parent_tags().first  == Sequence::INIT &&
                S0.get_parent_tags().second == Sequence::INIT);
        assert (S1.get_parent_tags().first  == Sequence::RAND &&
                S1.get_parent_tags().second == Sequence::RAND);
        assert (S7.get_parent_tags().first  == S4.get_tag() &&
                S7.get_parent_tags().second == S5.get_tag());

        return 0;
    }
}
#endif //TEST_SEQUENCE_H
