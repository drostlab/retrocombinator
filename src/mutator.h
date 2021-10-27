/**
 * @file
 */
#ifndef MUTATOR_H
#define MUTATOR_H

#include "constants.h"
#include "sequence.h"

#include <string>
#include <vector>

namespace retrocombinator
{
    class PointMutationModel;

    /** A class that can mutate a given sequence according to a specified point
     *  mutation model.
     */
    class Mutator
    {
    private:
        /// Which point mutation model this mutator corresponds to
        PointMutationModel * point_mutation_model;

    public:
        /** Chooses a point mutation model.
         *  Can be "JC69", "K80", "F81", "HKY85", "TN93" or "GTR", but note that
         *  "GTR" is not yet implemented
         */
        Mutator(std::string model);

        /// Destructor that frees up memory
        ~Mutator();

        /// Mutates a sequence according to a given transition matrix
        void mutate_sequence(Sequence& s, double time_per_step) const;
    };
}

#endif //MUTATOR_H
