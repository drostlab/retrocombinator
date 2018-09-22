#include "utilities.h"

using namespace rcombinator;

namespace rcombinator::Utils
{
    double cluster_dist(const dist_type& dist, size_type n,
                        const cluster_type& C1,
                        const cluster_type& C2)
    {
        double total_dist = 0;

        for (const auto& a1 : C1)
        {
            for (const auto& a2 : C2)
            {
                total_dist += dist[a1][a2];
            }
        }
        double num_pairs = C1.size() * C2.size();
        return (total_dist/num_pairs);
    }

    cluster_type cluster(const dist_type& dist, size_type n)
    {
        return cluster_type();
    }
}
