/**
 * @file
 *
 * \brief To mutate sequences using a point mutation model.
 *
 * Includes a class which has methods for modifying sequences in place according
 * to some point mutation model.
 */
#ifndef POINT_MUTATOR_HPP
#define POINT_MUTATOR_HPP

#include <string>
#include <vector>

namespace rcombinator
{
    class PointMutationModel;
    class Sequence;

    /** A class that can mutate a given sequence according to a specified point
     *  mutation model.
     *  We need to specify how long the sequence has evolved for.
     */
    class PointMutator
    {
    private:
        /// Which point mutation model this mutator coressponds to
        PointMutationModel * point_mutation_model;
        /** What is the probability that a mutation at a given position results
         *  in inactivity
         */
        std::vector<double> lethal_mutation_probs;

    public:
        /** Constructor that chooses a point mutation model and the
         *  probabilities for lethal mutations at each position in the sequence
         */
        PointMutator(std::string model, long n,
                     long num_sensitive_posns, double inactive_probability);

        /// Destructor that frees up memory
        ~PointMutator();

        /// Mutates a sequence according to a given transition matrix
        void mutate_sequence(Sequence& s, double timestep) const;
    };
}

#endif //POINT_MUTATOR_HPP
