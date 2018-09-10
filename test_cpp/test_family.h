/**
 * @file
 *
 * \brief
 *
 */
#ifndef TEST_FAMILY_H
#define TEST_FAMILY_H

#include "test_header.h"
#include "family.h"

namespace rcombinator
{
    int test_family()
    {
        try
        {
            test_initialize();
            Sequence::renumber_sequences(0);
            Family::renumber_families(0);

            std::vector<Family> fs;
            fs.emplace_back(Consts::INIT_FAMILY_COUNT);
            assert (fs[0].get_parent_tag() == -1);
            assert (fs[0].get_tag() == 0);

            fs[0].seqs.emplace_back(4);
            fs[0].seqs.emplace_back("TTTT");
            fs[0].seqs.emplace_back(fs[0].seqs[0], fs[0].seqs[1], 1);
            assert(fs[0].seqs[2].get_tag() == 2);

            fs.emplace_back(fs[0].get_tag());
            fs[1].seqs.emplace_back("AAAA");

            assert (fs[1].get_parent_tag() == fs[0].get_tag());
            assert (fs[1].get_tag() == 1);
            assert(fs[1].seqs[0].get_tag() == 3);

            return 0;
        }
        catch (Exception e)
        {
            std::cout << e.what() << std::endl;
            return 1;
        }
    }
}

#endif // TEST_FAMILY_H

