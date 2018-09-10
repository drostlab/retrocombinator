/**
 * @file
 *
 * \brief To test the functionality of the Point Mutation Models.
 *
 */
#ifndef TEST_POINT_MUTATION_MODELS_H
#define TEST_POINT_MUTATION_MODELS_H

#include "test_header.h"
#include "point_mutation_models.h"

#include <iostream>
#include <limits>

namespace rcombinator
{
    bool matrix_equal(const double mat1[][Consts::NUC_COUNT],
                             const double mat2[][Consts::NUC_COUNT])
    {
        for (int i=0; i<Consts::NUC_COUNT; ++i)
        {
            for (int j=0; j<Consts::NUC_COUNT; ++j)
            {
                if (fabs(mat1[i][j] - mat2[i][j]) > Consts::DOUBLE_TOLERANCE)
                {
                    return false;
                }
            }
        }
        return true;
    }

    void print_matrix(const double mat[][Consts::NUC_COUNT])
    {
        std::cout.precision(std::numeric_limits<double>::max_digits10);
        for (int i=0; i<Consts::NUC_COUNT; ++i)
        {
            for (int j=0; j<Consts::NUC_COUNT; ++j)
            {
                std::cout << std::fixed << mat[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    int test_point_mutation_models()
    {
        const double (*mat)[Consts::NUC_COUNT];

        GTRModel gtr_model(2, 3, 5, 7,
                           11, 13, 17,
                           19, 23,
                           29,
                           10);
        mat = gtr_model.get_Q();

        double e_gtr_model_Q[][4] = {
            { -33-65-119, 3*11, 5*13, 7*17 },
            { 2*11, -22-95-161, 5*19, 7*23},
            { 2*13, 3*19, -26-57-203, 7*29},
            { 2*17, 3*23, 5*29, -34-69-145}
        };
        assert (matrix_equal(mat, e_gtr_model_Q));

        K80Model k80model;
        mat = k80model.get_transition_matrix(1);
        double e_k80_model_T[][4] = {
            { 0.97075503241403394,0.02426988446055012,0.00248754156270797,0.00248754156270797},
            { 0.02426988446055012,0.97075503241403394,0.00248754156270797,0.00248754156270797},
            { 0.00248754156270797,0.00248754156270797,0.97075503241403394,0.02426988446055012},
            { 0.00248754156270797,0.00248754156270797,0.02426988446055012,0.97075503241403394},
        };
        assert (matrix_equal(mat, e_k80_model_T));

        return 0;
    }
}
#endif //TEST_POINT_MUTATION_MODELS_H
