#include <list>
#include <iterator>
#include "utilities.h"

using namespace retrocombinator;

namespace retrocombinator::Utils
{
    double cluster_dist(const dist_type& dist, size_type,
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
        if (n < 2)
        {
            throw Exception("Can't split a set of size < 2 into clusters");
        }

        // Create n individual clusters
        std::list<cluster_type> all_clusters;
        for (size_type i=0; i<n; ++i)
        {
            cluster_type ind_cluster;
            ind_cluster.insert(i);
            all_clusters.push_back(ind_cluster);
        }

        while (all_clusters.size() > 2)
        {
            // initialize the two to-be-joined clusters with the first two
            // clusters we can access
            auto join_1 = all_clusters.begin();
            auto join_2 = std::next(join_1);
            double min_so_far = cluster_dist(dist, n, *join_1, *join_2);

            for (auto it = all_clusters.begin(); it != all_clusters.end(); ++it)
            {
                for (auto jt = std::next(it); jt != all_clusters.end(); ++jt)
                {
                    auto this_dist = cluster_dist(dist, n, *it, *jt);
                    // two clusters are closer to each other than the ones we
                    // have so far
                    if (this_dist < min_so_far)
                    {
                        join_1 = it;
                        join_2 = jt;
                        min_so_far = this_dist;
                    }
                }
            }

            auto smaller = join_1;
            auto bigger  = join_2;
            if (join_1->size() > join_2->size())
            {
                smaller = join_2;
                bigger  = join_1;
            }

            // add the smaller cluster to the bigger cluster to union-ise them
            for (auto elem : *smaller)
            {
                bigger->insert(elem);
            }
            all_clusters.erase(smaller);
        }
        // return the smaller cluster
        if (all_clusters.front().size() < all_clusters.back().size())
        {
            return (all_clusters.front());
        }
        else
        {
            return(all_clusters.back());
        }
    }
}
