#include "representative.h"


namespace retrocombinator
{
    // Start counting from representative 1 by setting this to 0 and always
    // incrementing before assigning a new tag
    tag_type Representative::global_representative_count = 0;
}

using namespace retrocombinator;

Representative::Representative(std::string raw_sequence,
        size_type num_mutations, size_type creation_timestep):
    tag(Representative::global_representative_count + 1),
    raw_sequence(raw_sequence), num_mutations(num_mutations),
    creation_timestep(creation_timestep)
{
    ++Representative::global_representative_count;
}
