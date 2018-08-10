/**
 * @file
 *
 * \brief To store different models of DNA evolution.
 *
 * Declares an interface for defintion of different point mutation models.
 */
#ifndef POINT_MUTATION_MODELS_HPP
#define POINT_MUTATION_MODELS_HPP

#include <cmath>

#include "constants.h"

namespace rcombinator
{
    /// To represent a model of DNA evolution through point mutations
    class PointMutationModel
    {
    protected:
        double ** Q_mat;  ///< The transition rate matrix
        double scale;     ///< How much to scale Q by in the differential equation
        double t_stored;  ///< The timestep by which we jump in our simulation
        double ** T_mat;  ///< The transition matrix for timestep \a t

    public:
        /// Constructor that allocates memory for transition matrix
        PointMutationModel(double scale = 0.25);

        /** Destructor that allocates memory for transition matrix.
         *  Is virtual because we want all specific point mutation models to
         *  derive from this class.
         */
        virtual ~PointMutationModel();

        /** Returns a rate matrix for the mutations.
         *  After \a t years have passed, the probability is exp(rate*t).
         */
        double** get_Q() { return Q_mat; }

        /** Returns a transition matrix to represent the probabilities of
         *  mutations from each nucleotide to the other.
         *  \a t is the time that has passed.
         *  P(A to B) is matrix(A, B).
         */
        virtual double** get_transition_matrix(double t) = 0;
    };

    /// General Time Reversible Model, Tavare 1986
    class GTRModel : public PointMutationModel
    {
    public:
        /// \todo Use the defaults from constants.h
        GTRModel(double pi_T=0.25, double pi_C=0.25,
                 double pi_A=0.25, double pi_G=0.25,
                 double T2C=0.1, double T2A=0.1, double T2G=0.1,
                 double C2A=0.1, double C2G=0.1,
                 double A2G=0.1,
                 double scale=0.25);

        /// To be computed using exponentiation of Q
        double** get_transition_matrix(double t) override;
    };

    /// Tamura ane Nei 1983 Model
    class T93Model : public GTRModel
    {
    public:
        /// \todo Use the defaults from constants.h
        T93Model(double pi_T=0.25, double pi_C=0.25,
                 double pi_A=0.25, double pi_G=0.25,
                 double k1=0.1, double k2=0.1,
                 double scale=0.25);

        /// To be computed using exponentiation of Q
        double** get_transition_matrix(double t) override;
    };

    /// Hasegawa, Kishino and Yano 1985 Model
    class HKY85Model : public T93Model
    {
    public:
        /// \todo Use the defaults from constants.h
        HKY85Model(double pi_T=0.25, double pi_C=0.25,
                   double pi_A=0.25, double pi_G=0.25,
                   double k=0.1, double scale=0.25);

        /// To be computed using exponentiation of Q
        double** get_transition_matrix(double t) override;
    };

    /// Felsenstein 1981 Model
    class F81Model : public HKY85Model
    {
    public:
        /// \todo Use the defaults from constants.h
        F81Model(double pi_T=0.25, double pi_C=0.25,
                 double pi_A=0.25, double pi_G=0.25,
                 double scale=0.25);

        /// To be computed using exponentiation of Q
        double** get_transition_matrix(double t) override;
    };

    /// Kimura 2 Parameter Model, 1980
    class K80Model : public HKY85Model
    {
    public:
        /// \todo Use the defaults from constants.h
        K80Model(double k=1, double scale=0.25);

        /// The K-80 transition matrix
        double** get_transition_matrix(double t) override;
    };

    /// Jules and Cantor, 1969
    class JC69Model : public K80Model
    {
    public:
        /// \todo Use the defaults from constants.h
        JC69Model(double scale=0.25);
    };
}

#endif //POINT_MUTATION_MODELS_HPP
