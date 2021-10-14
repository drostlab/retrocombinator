/**
 * @file
 *
 * \brief Declaration of the global random number generator.
 *
 * Used for basic methods in statistics and probability.
 * RNG is the global instance name.
 */
#ifndef RAND_MATHS_H
#define RAND_MATHS_H

#include "constants.h"

#include <chrono>
#include <random>
#include <set>
#include <vector>

namespace retrocombinator
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
        std::mt19937 re;

        /** Last seed for the random engine, either by the user or by the
         *  system.
         *  Note that this does not reflect the internal state of the random
         *  engine at all points as once random number generation begins, this
         *  value is not touched.
         */
        size_type last_seed;

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
        void set_specific_seed(size_type seed);

        /** Uses system time to seed the RNG.
         *  This can be undone by calling \p set_specific_seed()
         */
        void set_random_seed();

        /** Gets the last set seed.
         *  Look at the definition of last_seed for more details.
         */
        size_type get_last_seed() const { return last_seed; }

        /** Generates a random true/false value.
         */
        bool rand_bit();

        /** Generates a random integer within a range.
         *  The bounds are [inclusive_low, exclusive_high).
         */
        size_type rand_int(size_type low, size_type high);

        /** Generates a random real number within a range.
         *  The bounds are [inclusive_low, exclusive high).
         */
        double rand_real(double low = 0.0, double high = 1.0);

        /** Chooses a number sampled from a Poisson distribution.
         *  Takes the mean as a parameter.
         */
        size_type rand_poisson(double mean);

        /** Samples \a m integers within a range, without replacement.
         *  The bounds are [inclusive_low, exclusive high).
         *  The integers are returned in ascending order.
         */
        std::set<size_type> sample_without_replacement(size_type low,
                                                       size_type high,
                                                       size_type m);

        /** Samples a non-diagonal pair (2 distinct values) within a range.
         *  The bounds for each value are [inclusive_low, exclusive high).
         */
        std::pair<size_type, size_type> sample_distinct_pair(size_type low,
                                                             size_type high);

        /** Tests whether or not an event happened.
         *  Takes the probability of an event as parameter, and then compares it
         *  to a random value in [0, 1).
         */
        bool test_event(double event_probability);

        /** Chooses an event from a list of possible events.
         *  Takes the probabilities of each of the events as input.  Throws an
         *  exception if the probabilities do not add up to at least 1.
         *
         *  This does not check if the array is valid, i.e. if the probabilities
         *  add up to 1.
         */
        size_type choose_event(const double events[], size_type num_events);

        /** Chooses an event from a list of possible events.
         *  Takes the *relative* probabilities of each of the events as input
         */
        template<typename T>
        size_type choose_event(const std::vector<T> events)
        {
            if(events.size() <= 0) {
                throw Exception("Number of events needs to be strictly positive");
            }
            double rand_num = rand_real();
            // some proportion of the overall sum
            double target = rand_num * std::accumulate(events.begin(), events.end(), 0);
            double running_total = 0;
            for (size_type i=0; i<events.size(); ++i)
            {
                running_total += events[i];
                if (running_total >= target) return i;
            }
            // it is the last event if say target rounded down from the total sum
            return (events.size()-1);

        }

        /** Chooses many events from a list of possible events, with
         *  replacement.
         *
         *  Returns a vector \p picks of the same size as events, where
         *      \a picks_i is the number of times event \p i was chosen.
         *
         *  Takes the *relative* probabilities of each of the events as input.
         */
        template<typename T>
        std::vector<size_type> choose_events(std::vector<T> events,
                                             size_type num_picks)
        {
            if(events.size() <= 0) {
                throw Exception("Number of events needs to be strictly positive");
            }
            // Make the (relative) probabilities cumulative
            std::vector<double> events_cum(events.size(), 0);
            double running_total = 0;
            for (size_type i=0; i<events.size(); ++i) {
                events_cum[i] = events[i] + running_total;
                running_total = events_cum[i];
            }

            // running_total now contains the sum of all (relative) probabilities

            std::vector<size_type> picks(events_cum.size(), 0);

            for (size_type i=0; i<num_picks; ++i) {
                double target = rand_real() * running_total;

                // binary search on the sorted array to see which event was chosen
                size_type beg = 0;
                size_type end = events_cum.size() - 1;
                size_type mid;

                while (beg <= end) {
                    mid = (beg + end) / 2;

                    if(target > events_cum[mid]) {
                        // mid *must* be < end
                        beg = mid + 1;
                    } else {
                        if (mid == 0) {
                            picks[0] += 1;
                            break;
                        }
                        else if (target > events_cum[mid-1]) {
                            // Need strictly bigger, if equal then P(mid) was 0
                            picks[mid] += 1;
                            break;
                        }
                        else {
                            end = mid - 1;
                        }
                    }
                }
            }

            return picks;
        }

        /** Chooses (without replacement) a given number of items randomly from
         *  a list of distinct types, where each type has some number of items to
         *  begin with.
         *
         *  Returns a vector \p picks of the same size as items, where
         *      \a picks_i is the number of times item \a i was chosen, and
         *      \a picks_i <= \p item_i
         *
         *  If the number of items to be picked is larger than we have
         *  available, all items are picked and so we just return the original
         *  list given to us.
         */
        std::vector<size_type> choose_items(std::vector<size_type> items,
                                            size_type num_picks);
    };

    // Global random number generator
    extern RandMaths& RNG;
}

#endif // RAND_MATHS_H
