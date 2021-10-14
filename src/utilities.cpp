#include <limits>
#include <list>
#include <iterator>
#include "utilities.h"

using namespace retrocombinator;

namespace retrocombinator {
    std::vector<Utils::cluster_type> Utils::cluster_slink(
            dist_type dist, size_type n, size_type join_threshold_max)
    {
        typedef std::pair<size_type, size_type> edge_type;
        size_type INFTY = std::numeric_limits<size_type>::max();

        // Initially, each cluster is just the number
        std::vector<cluster_type> clusters;
        for (size_type i=0; i<n; ++i) {
            clusters.emplace_back(cluster_type { i });
        }

        // Get the nearest neighbour for each cluster
        std::vector<edge_type> nearest;
        for (size_type i=0; i<n; ++i) {
            size_type cur_nearest = -1;
            size_type cur_dist = INFTY;
            for (size_type j=0; j<n; ++j) {
                if (j != i && dist[i][j] < cur_dist) {
                    cur_nearest = j;
                    cur_dist = dist[i][j];
                }
            }
            nearest.emplace_back(edge_type{cur_nearest, cur_dist});
        }

        // Start at 1 so we only do n-1 steps
        for(size_type loop = 1; loop < n; ++loop) {

            // 1) Find the nearest distance between clusters
            size_type best = 0;
            size_type best_dist = INFTY;
            for (size_type i=0; i<n; ++i) {
                if (nearest[i].second < best_dist) {
                    best = i;
                    best_dist = nearest[i].second;
                }
            }
            if(best_dist >= join_threshold_max) { break; }

            // 2) Join the 'next' cluster to the 'best' cluster
            size_type next = nearest[best].first;
            clusters[best].insert(clusters[next].begin(), clusters[next].end());
            clusters[next].clear();

            // 3) Recompute distances
            nearest[next].first = -1;
            nearest[next].second = INFTY;

            size_type best_update = -1;
            size_type best_update_dist = INFTY;
            for (size_type i=0; i<n; ++i) {
                if (i == best || i == next) { continue; }
                if (dist[best][i] < best_update_dist) {
                    best_update = i;
                    best_update_dist = dist[best][i];
                }
                if (dist[next][i] < best_update_dist) {
                    best_update = i;
                    best_update_dist = dist[next][i];
                }
            }
            nearest[best].first = best_update;
            nearest[best].second = best_update_dist;

            for(size_type i=0; i<n; ++i) {
                dist[next][i] = INFTY;
                dist[i][next] = INFTY;
            }
        }

        std::vector<cluster_type> non_empty_clusters;
        for (size_type i=0; i<clusters.size(); ++i) {
            if (!clusters[i].empty()) {
                non_empty_clusters.push_back(clusters[i]);
            }
        }
        return non_empty_clusters;
    }

    std::vector<size_type>
    Utils::select_representatives(std::vector<Utils::cluster_type> clusters) {
        std::vector<size_type> representatives;
        for (const auto& cluster: clusters) {
            representatives.push_back(*cluster.begin());
        }
        return representatives;
    }
}
