/**
 * @file
 *
 */

#ifndef TEST_UTILITIES_H
#define TEST_UTILITIES_H

#include "test_header.h"
#include "../utilities.h"

namespace retrocombinator
{
    void print_cluster(std::vector<Utils::cluster_type> clusters) {
        for(auto& clust: clusters) {
            for (auto& elem: clust) {
                std::cout << elem << ",";
            }
            std::cout << std::endl;
        }
    }

    bool check_clusters_equal(std::vector<Utils::cluster_type> c_a,
            std::vector<Utils::cluster_type> c_b) {
        if(c_a.size() != c_b.size()) { return false; }
        for (size_type i = 0; i < c_a.size(); ++i) {
            if (c_a[i] != c_b[i]) { return false; }
        }
        return true;
    }

    int test_utilities()
    {
        test_initialize();
        try {

            size_type n_1 = 5;
            dist_type mat_1 = {
                dist_row_type {  0, 17, 21, 31, 23 },
                dist_row_type { 17,  0, 30, 34, 21 },
                dist_row_type { 21, 30,  0, 28, 39 },
                dist_row_type { 31, 34, 28,  0, 43 },
                dist_row_type { 23, 21, 39, 43,  0 }
            };

            assert(check_clusters_equal(
                Utils::cluster_slink(mat_1, n_1, 20),
                std::vector<Utils::cluster_type> {
                    Utils::cluster_type {0, 1},
                    Utils::cluster_type {2},
                    Utils::cluster_type {3},
                    Utils::cluster_type {4},
                }
            ));

            size_type n_2 = 7;
            dist_type mat_2 = {
                //               a   b   c   d   e   f   g
                dist_row_type {  0, 11, 91, 91, 93, 34, 94 }, // a
                dist_row_type { 11,  0, 21, 94, 91, 94, 94 }, // b
                dist_row_type { 91, 21,  0, 12, 99, 94, 94 }, // c
                dist_row_type { 91, 94, 12,  0, 52, 94, 94 }, // d
                dist_row_type { 93, 91, 99, 52,  0, 17, 94 }, // e
                dist_row_type { 34, 94, 94, 94, 17,  0, 94 }, // f
                dist_row_type { 94, 94, 94, 94, 94, 94,  0 }, // g
            };

            assert(check_clusters_equal(
                Utils::cluster_slink(mat_2, n_2, 20),
                std::vector<Utils::cluster_type> {
                    Utils::cluster_type {0, 1},
                    Utils::cluster_type {2, 3},
                    Utils::cluster_type {4, 5},
                    Utils::cluster_type {6},
                }
            ));

            assert(check_clusters_equal(
                Utils::cluster_slink(mat_2, n_2, 30),
                std::vector<Utils::cluster_type> {
                    Utils::cluster_type {0, 1, 2, 3},
                    Utils::cluster_type {4, 5},
                    Utils::cluster_type {6},
                }
            ));

            assert(check_clusters_equal(
                Utils::cluster_slink(mat_2, n_2, 40),
                std::vector<Utils::cluster_type> {
                    Utils::cluster_type {0, 1, 2, 3, 4, 5},
                    Utils::cluster_type {6},
                }
            ));

            size_type n_3 = 7;
            dist_type mat_3 = {
                //               a   b   c   d   e   f   g
                dist_row_type {  0, 15, 91, 10, 93, 94, 11 }, // a
                dist_row_type { 15,  0, 31, 94, 94, 94, 94 }, // b
                dist_row_type { 91, 31,  0, 92, 12, 34, 94 }, // c
                dist_row_type { 10, 94, 92,  0, 94, 92, 97 }, // d
                dist_row_type { 93, 91, 12, 94,  0, 27, 90 }, // e
                dist_row_type { 94, 94, 34, 92, 27,  0, 64 }, // f
                dist_row_type { 11, 94, 94, 97, 90, 64,  0 }, // g
            };

            assert(check_clusters_equal(
                Utils::cluster_slink(mat_3, n_3, 10),
                std::vector<Utils::cluster_type> {
                    Utils::cluster_type {0},
                    Utils::cluster_type {1},
                    Utils::cluster_type {2},
                    Utils::cluster_type {3},
                    Utils::cluster_type {4},
                    Utils::cluster_type {5},
                    Utils::cluster_type {6},
                }
            ));

            assert(check_clusters_equal(
                Utils::cluster_slink(mat_3, n_3, 11),
                std::vector<Utils::cluster_type> {
                    Utils::cluster_type {0, 3},
                    Utils::cluster_type {1},
                    Utils::cluster_type {2},
                    Utils::cluster_type {4},
                    Utils::cluster_type {5},
                    Utils::cluster_type {6},
                }
            ));

            assert(check_clusters_equal(
                Utils::cluster_slink(mat_3, n_3, 20),
                std::vector<Utils::cluster_type> {
                    Utils::cluster_type {0, 1, 3, 6},
                    Utils::cluster_type {2, 4},
                    Utils::cluster_type {5},
                }
            ));

            assert((Utils::select_representatives(Utils::cluster_slink(mat_3, n_3, 20)) ==
                    std::vector<size_type> { 0, 2, 5 }));

            assert(check_clusters_equal(
                Utils::cluster_slink(mat_3, n_3, 30),
                std::vector<Utils::cluster_type> {
                    Utils::cluster_type {0, 1, 3, 6},
                    Utils::cluster_type {2, 4, 5},
                }
            ));

            assert(check_clusters_equal(
                Utils::cluster_slink(mat_3, n_3, 32),
                std::vector<Utils::cluster_type> {
                    Utils::cluster_type {0, 1, 2, 3, 4, 5, 6},
                }
            ));

            return 0;
        }
        catch (Exception e)
        {
            std::cout << e.what() << std::endl;
            return 1;
        }
    }
}

#endif // TEST_UTILITIES_H

