/**
 * @file
 *
 * \brief To test the functionality of the Sequence class.
 *
 */
#ifndef TEST_SEQUENCE_H
#define TEST_SEQUENCE_H

#include "test_header.h"
#include "../sequence.h"

namespace retrocombinator
{
    /// Tests the Sequence class
    int test_sequence()
    {
        test_initialize();

        try {
            ActivityTracker at(12, 2, 1.0);

            Sequence::renumber_sequences();
            Sequence::set_activity_tracker(at);

            // Testing string to bool conversion
            std::string seq_string1("TCGATCGATCGA");
            Sequence S1(seq_string1);

            assert (S1.as_string() == seq_string1);

            // Testing random sequence generation
            Sequence S2;
            assert (S2.as_string() == "GGGGCATAATGA");

            // Testing non-lethal point mutations
            std::string seq_string3("TTTTTTTTTTTT");
            Sequence S3(seq_string3);
            assert (S3.num_mutations() == 0);

            S3.point_mutate(2, 'C');
            assert (S3.as_string() == "TTCTTTTTTTTT");
            assert (S3.num_mutations() == 1);

            S3.point_mutate(4, 'A');
            assert (S3.as_string() == "TTCTATTTTTTT");
            assert (S3.num_mutations() == 2);

            // Testing lethal point mutations
            assert (S3.is_active());
            S3.point_mutate(1, 'G');
            assert (S3.as_string() == "TGCTATTTTTTT");
            assert (S3.num_mutations() == 3);
            // Testing sequence similarity as a percentage
            assert (S3.init_seq_similarity() == 0.75);
            assert (!S3.is_active());

            // Testing diff operator
            std::string seq_string4("TTTTTTTTTTTT");
            Sequence S4(seq_string4);

            assert (S3 * S4 == 3);
            assert (S3 % S4 == 0.25);
            assert (S3 * "TTTTTTTTTTTT" == 3);
            assert (S3 % "TTTTTTTTTTTT" == 0.25);

            // Testing recombination
            std::string seq_string5("AAAAAAAAAAAA");
            Sequence S5(seq_string5);

            std::string seq_string6("GGGGGGGGGGGG");
            Sequence S6(seq_string6);

            Sequence S7(S5, S6, 1);
            Sequence S8(S5, S6, 2);
            Sequence S9(S5, S6, 3);

            assert (S7.as_string() == "GGGGGGGGGGAA");
            assert (S8.as_string() == "AGGGAAAAAAAA");
            assert (S9.as_string() == "AGGGGAAAGGGG");

            // Testing individual sequence tagging
            assert (S1.get_tag() == 1);
            assert (S2.get_tag() == 2);
            assert (S9.get_tag() == 9);

            // Testing parent tagging
            assert (S1.get_parent_tags().first  ==
                    Consts::SEQUENCE_INITIALISED_EXTERNALLY_TAG &&
                    S1.get_parent_tags().second ==
                    Consts::SEQUENCE_INITIALISED_EXTERNALLY_TAG);
            assert (S2.get_parent_tags().first  ==
                    Consts::SEQUENCE_CREATED_RANDOMLY_TAG &&
                    S2.get_parent_tags().second ==
                    Consts::SEQUENCE_CREATED_RANDOMLY_TAG);
            assert (S8.get_parent_tags().first  == S5.get_tag() &&
                    S8.get_parent_tags().second == S6.get_tag());

            return 0;
        }
        catch (Exception e)
        {
            std::cout << e.what() << std::endl;
            return 1;
        }
    }
}
#endif //TEST_SEQUENCE_H
