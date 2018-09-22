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
        return 0;
    }
}

#endif // TEST_UTILITIES_H

