#include <cmath>

#include "point_mutation_models.h"

using namespace retrocombinator;

const double (*PointMutationModel::get_Q())[Consts::NUC_COUNT]
{
    return Q;
}

PointMutationModel::PointMutationModel(double scale) :
    scale(scale), t_stored(0)
{
    for(int i=0; i<Consts::NUC_COUNT; ++i)
    {
        for(int j=0; j<Consts::NUC_COUNT; ++j)
        {
            Q[i][j] = 0;
            P[i][j] = i == j ? 1: 0;
        }
    }
}

const double (*PointMutationModel::get_transition_matrix(double t))[Consts::NUC_COUNT]
{
    // compute the transition matrix only if required
    if (t_stored != t)
    {
        t_stored = t;
        compute_transition_matrix();
    }
    return P;
}

GTRModel::GTRModel(
    double pi_T, double pi_C, double pi_A, double pi_G,
    double T2C, double T2A, double T2G,
    double C2A, double C2G,
    double A2G,
    double scale): PointMutationModel(scale),
    pi_T(pi_T), pi_C(pi_C), pi_A(pi_A), pi_G(pi_G)
{
    double C2T = T2C;
    double A2T = T2A;
    double G2T = T2G;
    double A2C = C2A;
    double G2C = C2G;
    double G2A = A2G;

    Q[Consts::T][Consts::T] = - T2C*pi_C - T2A*pi_A - T2G*pi_G;
    Q[Consts::T][Consts::C] = T2C * pi_C;
    Q[Consts::T][Consts::A] = T2A * pi_A;
    Q[Consts::T][Consts::G] = T2G * pi_G;

    Q[Consts::C][Consts::C] = - C2T*pi_T - C2A*pi_A - C2G*pi_G;
    Q[Consts::C][Consts::T] = C2T * pi_T;
    Q[Consts::C][Consts::A] = C2A * pi_A;
    Q[Consts::C][Consts::G] = C2G * pi_G;

    Q[Consts::A][Consts::A] = - A2T*pi_T - A2C*pi_C - A2G*pi_G;
    Q[Consts::A][Consts::T] = A2T * pi_T;
    Q[Consts::A][Consts::C] = A2C * pi_C;
    Q[Consts::A][Consts::G] = A2G * pi_G;

    Q[Consts::G][Consts::G] = - G2T*pi_T - G2C*pi_C - G2A*pi_A;
    Q[Consts::G][Consts::T] = G2T * pi_T;
    Q[Consts::G][Consts::C] = G2C * pi_C;
    Q[Consts::G][Consts::A] = G2A * pi_A;
}

void GTRModel::compute_transition_matrix()
{
    // TODO: Implement this
    throw Exception("To be implemented");
}

TN93Model::TN93Model(double pi_T, double pi_C, double pi_A, double pi_G,
                   double k1, double k2, double scale):
    GTRModel(pi_T, pi_C, pi_A, pi_G,
             /*T2C=*/k1, /*T2A=*/1, /*T2G=*/1,
             /*C2A=*/1,  /*C2G=*/1,
             /*A2G=*/k2,
             scale),
    k1(k1), k2(k2)
{
}

void TN93Model::compute_transition_matrix()
{
    double t = t_stored;

    // Reference- Molecular Evolution: A Statistical Approach, Ziheng Yang
    // Section 1.2.3.1

    double alpha1 = k1*scale*t;
    double alpha2 = k2*scale*t;
    double beta   = scale*t;

    double pi_Y = pi_T + pi_C;
    double pi_R = pi_A + pi_G;

    double e2 = exp(-beta);
    double e3 = exp(-pi_R*alpha2 - pi_Y*beta);
    double e4 = exp(-pi_Y*alpha1 - pi_R*beta);

    P[Consts::T][Consts::T] = pi_T + pi_T*pi_R*e2/pi_Y + pi_C*e4/pi_Y;
    P[Consts::C][Consts::T] = pi_T + pi_T*pi_R*e2/pi_Y - pi_T*e4/pi_Y;
    P[Consts::A][Consts::T] = pi_T * (1-e2);
    P[Consts::G][Consts::T] = pi_T * (1-e2);

    P[Consts::T][Consts::C] = pi_C + pi_C*pi_R*e2/pi_Y - pi_C*e4/pi_Y;
    P[Consts::C][Consts::C] = pi_C + pi_C*pi_R*e2/pi_Y + pi_T*e4/pi_Y;
    P[Consts::A][Consts::C] = pi_C * (1-e2);
    P[Consts::G][Consts::C] = pi_C * (1-e2);

    P[Consts::T][Consts::A] = pi_A * (1-e2);
    P[Consts::C][Consts::A] = pi_A * (1-e2);
    P[Consts::A][Consts::A] = pi_A + pi_A*pi_Y*e2/pi_R + pi_G*e3/pi_R;
    P[Consts::G][Consts::A] = pi_A + pi_A*pi_Y*e2/pi_R - pi_A*e3/pi_R;

    P[Consts::T][Consts::G] = pi_G * (1-e2);
    P[Consts::C][Consts::G] = pi_G * (1-e2);
    P[Consts::A][Consts::G] = pi_G + pi_G*pi_Y*e2/pi_R - pi_G*e3/pi_R;
    P[Consts::G][Consts::G] = pi_G + pi_G*pi_Y*e2/pi_R + pi_A*e3/pi_R;
}

HKY85Model::HKY85Model(double pi_T, double pi_C, double pi_A, double pi_G,
                       double k, double scale):
    TN93Model(pi_T, pi_C, pi_A, pi_G, k, k, scale)
{}

F81Model::F81Model(double pi_T, double pi_C, double pi_A, double pi_G,
                   double scale):
    HKY85Model(pi_T, pi_C, pi_A, pi_G, 1, scale)
{}

void F81Model::compute_transition_matrix()
{
    double t = t_stored;

    // Reference- Type the following into Wolfram Alpha:
    // matrixexp({{-C-A-G,C,A,G},{T,-T-A-G,A,G},{T,C,-T-C-G,G},{T,C,A,-T-C-A}})

    double pt = t*scale*pi_T;
    double pc = t*scale*pi_C;
    double pa = t*scale*pi_A;
    double pg = t*scale*pi_G;

    double sum = pt + pc + pa + pg;
    double to_t = (pt - pt*exp(-sum))/sum;
    double to_c = (pc - pc*exp(-sum))/sum;
    double to_a = (pa - pa*exp(-sum))/sum;
    double to_g = (pg - pg*exp(-sum))/sum;

    P[Consts::C][Consts::T] = to_t;
    P[Consts::A][Consts::T] = to_t;
    P[Consts::G][Consts::T] = to_t;

    P[Consts::T][Consts::C] = to_c;
    P[Consts::A][Consts::C] = to_c;
    P[Consts::G][Consts::C] = to_c;

    P[Consts::T][Consts::A] = to_a;
    P[Consts::C][Consts::A] = to_a;
    P[Consts::G][Consts::A] = to_a;

    P[Consts::T][Consts::G] = to_g;
    P[Consts::C][Consts::G] = to_g;
    P[Consts::A][Consts::G] = to_g;

    P[Consts::T][Consts::T] = 1.0 - to_c - to_a - to_g;
    P[Consts::C][Consts::C] = 1.0 - to_t - to_a - to_g;
    P[Consts::A][Consts::A] = 1.0 - to_t - to_c - to_g;
    P[Consts::G][Consts::G] = 1.0 - to_t - to_c - to_a;
}

K80Model::K80Model(double k, double scale):
    HKY85Model(0.25, 0.25, 0.25, 0.25, k, scale)
{}

void K80Model::compute_transition_matrix()
{
    double t = t_stored;

    // effective alpha and beta for this time_per_step
    double alpha = t*scale*Q[Consts::T][Consts::C];
    double beta  = t*scale*Q[Consts::T][Consts::G];

    // Reference- Molecular Evolution: A Statistical Approach, Ziheng Yang
    // Section 1.2.2
    double diag =
        0.25 + 0.25*exp(-4.0*beta) + 0.5*exp(-2*(alpha+beta));
    double transitions =
        0.25 + 0.25*exp(-4.0*beta) - 0.5*exp(-2*(alpha+beta));
    double transversions =
        0.25 - 0.25*exp(-4.0*beta);

    P[Consts::T][Consts::T] = diag;
    P[Consts::C][Consts::C] = diag;
    P[Consts::A][Consts::A] = diag;
    P[Consts::G][Consts::G] = diag;

    P[Consts::T][Consts::C] = transitions;
    P[Consts::C][Consts::T] = transitions;
    P[Consts::A][Consts::G] = transitions;
    P[Consts::G][Consts::A] = transitions;

    P[Consts::T][Consts::A] = transversions;
    P[Consts::T][Consts::G] = transversions;
    P[Consts::C][Consts::A] = transversions;
    P[Consts::C][Consts::G] = transversions;
    P[Consts::A][Consts::T] = transversions;
    P[Consts::A][Consts::C] = transversions;
    P[Consts::G][Consts::T] = transversions;
    P[Consts::G][Consts::C] = transversions;
}

JC69Model::JC69Model(double scale) : K80Model(1, scale) {}
