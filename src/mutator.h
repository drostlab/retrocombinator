/**
 * @file
 *
 * \brief To mutate sequences by point mutation using a model
 *
 * Includes a class which has methods for modifying sequences in place according
 * to some point mutation model
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
     *  We need to specify how long the sequence has evolved for.
     */
    class Mutator
    {
    private:
        /// Which point mutation model this mutator corresponds to
        PointMutationModel * point_mutation_model;

    public:
        /** Constructor that chooses a point mutation model and the
         *  probabilities for critical mutations at each position in the sequence
         */
        Mutator(std::string model);

        /// Destructor that frees up memory
        ~Mutator();

        /// Mutates a sequence according to a given transition matrix
        void mutate_sequence(Sequence& s, double time_per_step) const;
    };
}

#endif //MUTATOR_H
