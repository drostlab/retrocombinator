#include "family.h"

namespace rcombinator
{
    tag_type Family::global_family_count = -1;
}

using namespace rcombinator;

void Family::renumber_families(tag_type new_start_tag)
{
    Family::global_family_count = new_start_tag - 1;
}

Family::Family(tag_type parent_tag):
    parent_tag(parent_tag)
{
    ++Family::global_family_count;
    this->tag = Family::global_family_count;
}
