/**
 * @file
 *
 * \brief Declaration of the global random number generator.
 *
 * Used for basic methods in statistics and probability.
 * RNG is the global instance name.
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

        /** Constructor, which seeds the random engine with system time.
         *  Is private because we want this to be a singleton.
         */
        RandMaths();

    public:
        /** Returns an instance of a RandMaths class, after seeding it with
         *  system time.
         *  Can be done only once as we want to share the random number
         *  generation among all other classes, and seed only once for
         *  controlling the numbers that are generated.
         */
        static RandMaths& get_instance();

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

        /** Uses a user-specified seed for RNG.
         *  This can be undone by calling \p set_random_seed()
         */
        void set_specific_seed(long seed);

        /** Uses system time to seed the RNG.
         *  This can be undone by calling \p set_specific_seed()
         */
        void set_random_seed();

        /** Generates a random true/false value.
         */
        bool rand_bit();

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
        bool test_event(double event_probability);

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

    // Global random number generator
    extern RandMaths& RNG;
}

#endif // RAND_MATHS_HPP
