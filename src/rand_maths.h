/**
 * @file
 *
 * \brief Declaration of RandMaths, a random number generator
 *
 * Used for random number generation, and basic methods in statistics and
 * probability.
 */
#ifndef RAND_MATHS_HPP
#define RAND_MATHS_HPP

#include <chrono>
#include <random>
#include <set>

#include "exception.h"

namespace rcombinator
{
    /** For all maths helper functions that use random number generation.
     *  This is implemented as a singleton that can either be specifically
     *  seeded (for testing and debugging) or can be randomly seeded (for
     *  simulations).
     */
    class RandMaths
    {
    private:
        /** Engine that produces random numbers for all functions that require
         *  them.
         *  This is seeded during initialisation of the class, and once set,
         *  its RNG is shared by all other parts of the code that require it.
         */
        std::default_random_engine re;

        /** The initial seed for the engine that generates random numbers.
         *  If it is set to the special value 0 during construction, the seed is
         *  randomly chosen using system time.
         */
        const long seed;

        /** Constructor, which seeds the random engine.
         *  If the seed is 0, the random engine is seeded with system time.
         *  Any non-zero seed is directly used as the seed for the engine.
         */
        RandMaths(long seed = 0);

    public:
        /** Returns an instance of a RandMaths class, after seeding it.
         *  Can be done only once as we want to share the random number
         *  generation among all other classes, and seed only once for
         *  controlling the numbers that are generated.
         *  If the seed is set to the special value 0 during construction, the
         *  seed is randomly chosen using system time.
         */
        static RandMaths& initializeRandMaths(long seed = 0);

        //@{
        /** Delete copy constructors as want RandMaths to be a singleton.
         *  The reason these are public is because most compilers check for
         *  private-ness before they check to see if functions are deleted, and
         *  we want our error messages to be helpful if we create a new
         *  RandMaths object by mistake.
         */
        RandMaths(RandMaths const&) = delete;
        void operator=(RandMaths const&) = delete;
        //@}

        /** Generates a random integer within a range.
         *  The bounds are [inclusive_low, exclusive_high).
         */
        int rand_int(int low, int high);

        /** Generates a random real number within a range.
         *  The bounds are [inclusive_low, exclusive high).
         */
        double rand_real(double low = 0.0, double high = 1.0);

        /** Chooses a number sampled from a Poisson distribution.
         *  Takes the mean as a parameter.
         */
        long rand_poisson(double mean);

        /** Samples \a m integers within a range, without replacement.
         *  The bounds are [inclusive_low, exclusive high).
         *  The integers are returned in ascending order.
         */
        std::set<int> sample_without_replacement(int low, int high, int m);

        /** Samples a non-diagonal pair (2 distinct values) within a range.
         *  The bounds for each value are [inclusive_low, exclusive high).
         */
        std::pair<int, int> sample_distinct_pair(int low, int high);

        /** Tests whether or not an event happened.
         *  Takes the probability of an event as paramter, and then compares it to a
         *  random value in [0, 1).
         */
        inline bool test_event(double event_probability);

        /** Chooses an event from a list of possible events.
         *  Takes the probabilities of each of the events as input.
         *  Throws an exception if the probabilites do not add up to at least 1.
         *
         *  \todo Make this a safe pointer rather than a raw one, or use a vector
         *  rather than a raw array.
         *
         *  \todo Throw an exception even if probabilities add up to something
         *  greater than 1.
         */
        int choose_event(double * events, long num_events);
    };
}
#endif // RAND_MATHS_HPP
