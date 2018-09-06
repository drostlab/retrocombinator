#include <cmath>

#include "point_mutation_models.h"

using namespace rcombinator;

const double (*PointMutationModel::get_Q())[Consts::NUC_COUNT]
{
    return Q_mat;
}

PointMutationModel::PointMutationModel(double scale) :
    scale(scale), t_stored(0)
{
    for(int i=0; i<Consts::NUC_COUNT; ++i)
    {
        for(int j=0; j<Consts::NUC_COUNT; ++j)
        {
            Q_mat[i][j] = 0;
            T_mat[i][j] = 0;
        }
    }
}

GTRModel::GTRModel(
    double pi_T, double pi_C, double pi_A, double pi_G,
    double T2C, double T2A, double T2G,
    double C2A, double C2G,
    double A2G,
    double scale): PointMutationModel(scale)
{
    double C2T = T2C;
    double A2T = T2A;
    double G2T = T2G;
    double A2C = C2A;
    double G2C = C2G;
    double G2A = A2G;

    Q_mat[Consts::T][Consts::T] = - T2C*pi_C - T2A*pi_A - T2G*pi_G;
    Q_mat[Consts::T][Consts::C] = T2C * pi_C;
    Q_mat[Consts::T][Consts::A] = T2A * pi_A;
    Q_mat[Consts::T][Consts::G] = T2G * pi_G;

    Q_mat[Consts::C][Consts::C] = - C2T*pi_T - C2A*pi_A - C2G*pi_G;
    Q_mat[Consts::C][Consts::T] = C2T * pi_T;
    Q_mat[Consts::C][Consts::A] = C2A * pi_A;
    Q_mat[Consts::C][Consts::G] = C2G * pi_G;

    Q_mat[Consts::A][Consts::A] = - A2T*pi_T - A2C*pi_C - A2G*pi_G;
    Q_mat[Consts::A][Consts::T] = A2T * pi_T;
    Q_mat[Consts::A][Consts::C] = A2C * pi_C;
    Q_mat[Consts::A][Consts::G] = A2G * pi_G;

    Q_mat[Consts::G][Consts::G] = - G2T*pi_T - G2C*pi_C - G2A*pi_A;
    Q_mat[Consts::G][Consts::T] = G2T * pi_T;
    Q_mat[Consts::G][Consts::C] = G2C * pi_C;
    Q_mat[Consts::G][Consts::A] = G2A * pi_A;
}

const double (*GTRModel::get_transition_matrix(double))[Consts::NUC_COUNT]
{
    throw Exception("To be implemented");
}

T93Model::T93Model(double pi_T, double pi_C, double pi_A, double pi_G,
                   double k1, double k2, double scale):
    GTRModel(pi_T, pi_C, pi_A, pi_G,
             /*T2C=*/k2, /*T2A=*/1, /*T2G=*/1,
             /*C2A=*/1,  /*C2G=*/1,
             /*A2G=*/k1,
             scale)
{}

const double (*T93Model::get_transition_matrix(double))[Consts::NUC_COUNT]
{
    throw Exception("To be implemented");
}

HKY85Model::HKY85Model(double pi_T, double pi_C, double pi_A, double pi_G,
                       double k, double scale):
    T93Model(pi_T, pi_C, pi_A, pi_G, k, k, scale)
{}

const double (*HKY85Model::get_transition_matrix(double))[Consts::NUC_COUNT]
{
    throw Exception("To be implemented");
}

F81Model::F81Model(double pi_T, double pi_C, double pi_A, double pi_G,
                   double scale):
    HKY85Model(pi_T, pi_C, pi_A, pi_G, 1, scale)
{}

const double (*F81Model::get_transition_matrix(double))[Consts::NUC_COUNT]
{
    throw Exception("To be implemented");
}

K80Model::K80Model(double k, double scale):
    HKY85Model(0.25, 0.25, 0.25, 0.25, k, scale)
{}

const double (*K80Model::get_transition_matrix(double t))[Consts::NUC_COUNT]
{
    if (t_stored == t) { return T_mat; }

    // effective alpha and beta for this timestep
    double alpha = t*scale*Q_mat[Consts::T][Consts::C];
    double beta  = t*scale*Q_mat[Consts::T][Consts::G];

    // Reference- Molecular Evolution: A Statistical Approach, Ziheng Yang
    double diag =
        0.25 + 0.25*exp(-4.0*beta) + 0.5*exp(-2*(alpha+beta));
    double transitions =
        0.25 + 0.25*exp(-4.0*beta) - 0.5*exp(-2*(alpha+beta));
    double transversions =
        0.25 - 0.25*exp(-4.0*beta);

    T_mat[Consts::T][Consts::T] = diag;
    T_mat[Consts::C][Consts::C] = diag;
    T_mat[Consts::A][Consts::A] = diag;
    T_mat[Consts::G][Consts::G] = diag;

    T_mat[Consts::T][Consts::C] = transitions;
    T_mat[Consts::C][Consts::T] = transitions;
    T_mat[Consts::A][Consts::G] = transitions;
    T_mat[Consts::G][Consts::A] = transitions;

    T_mat[Consts::T][Consts::A] = transversions;
    T_mat[Consts::T][Consts::G] = transversions;
    T_mat[Consts::C][Consts::A] = transversions;
    T_mat[Consts::C][Consts::G] = transversions;
    T_mat[Consts::A][Consts::T] = transversions;
    T_mat[Consts::A][Consts::C] = transversions;
    T_mat[Consts::G][Consts::T] = transversions;
    T_mat[Consts::G][Consts::C] = transversions;

    // we have now computed the matrix, no need to compute it again
    t_stored = t;
    return T_mat;
}

JC69Model::JC69Model(double scale) : K80Model(1, scale) {}
