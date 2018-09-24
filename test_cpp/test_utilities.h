/**
 * @file
 *
 * \brief To test the functionality of the Utility functions.
 *
 */
#ifndef TEST_UTILITIES_H
#define TEST_UTILITIES_H

#include "test_header.h"
#include "utilities.h"

//TODO: remove
#include <iostream>
using namespace std;

namespace rcombinator
{
    int test_utilities()
    {
        size_type N = 8;
        cluster_type C0   { 0 };
        cluster_type C1   { 1 };
        cluster_type C23  { 2, 3 };
        cluster_type C456 { 4, 5, 6 };
        cluster_type C7   { 7 };
        dist_type D1 =
        {
            //    0,1,2,3,4,5,6,7
            /*0*/{0,3,6,5,6,2,6,8},/*0*/
            /*1*/{3,0,7,3,2,7,0,7},/*1*/
            /*2*/{6,7,0,5,9,0,6,9},/*2*/
            /*3*/{5,3,5,0,1,9,2,2},/*3*/
            /*4*/{6,2,9,1,0,3,6,0},/*4*/
            /*5*/{2,7,0,9,3,0,1,2},/*5*/
            /*6*/{6,0,6,2,6,1,0,3},/*6*/
            /*7*/{8,7,9,2,0,2,3,0},/*7*/
            //    0,1,2,3,4,5,6,7
        };
        assert (Utils::cluster_dist(D1, N, C0, C1) == 3);
        assert (Utils::cluster_dist(D1, N, C0, C7) == 8);
        assert (Utils::cluster_dist(D1, N, C1, C7) == 7);
        assert (Utils::cluster_dist(D1, N, C1, C23) == 5);
        assert (Utils::cluster_dist(D1, N, C1, C456) == 3);
        assert (Utils::cluster_dist(D1, N, C23, C456) == 4.5);

        // Location of points corresponding to D2
        //                        3
        //              5
        //
        //
        //        6
        //
        //
        //  7                 2
        //  4
        //
        //
        //                    1
        //  0
        dist_type D2 =
        {
            {0,9.05539,10.2956,16.2788,4,12.53,8.544,5},
            {9.05539,0,4,11.1803,9.48683,10.4403,9.21954,9.84886},
            {10.2956,4,0,7.28011,9.05539,6.7082,6.7082,9},
            {16.2788,11.1803,7.28011,0,13.6015,5.09902,8.94427,13.0384},
            {4,9.48683,9.05539,13.6015,0,9.21954,5,1},
            {12.53,10.4403,6.7082,5.09902,9.21954,0,4.24264,8.48528},
            {8.544,9.21954,6.7082,8.94427,5,4.24264,0,4.24264},
            {5,9.84886,9,13.0384,1,8.48528,4.24264,0},
        };

        auto clus1 = Utils::cluster(D2, N);
        cluster_type expected_clust({0, 4, 7});
        assert (expected_clust == clus1);
        return 0;
    }
}

#endif // TEST_UTILITIES_H

