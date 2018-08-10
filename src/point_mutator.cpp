#include "point_mutation_models.h"
#include "point_mutator.h"
#include "rand_maths.h"
#include "sequence.h"

using namespace rcombinator;

PointMutator::PointMutator(std::string model, long n,
                           long num_sensitive_posns, double inactive_probability)
{
    if (model == "GTR")
    {
        point_mutation_model = new GTRModel();
    }
    else if (model == "T93")
    {
        point_mutation_model = new T93Model();
    }
    else if (model == "HKY85")
    {
        point_mutation_model = new HKY85Model();
    }
    else if (model == "F81")
    {
        point_mutation_model = new F81Model();
    }
    else if (model == "K80")
    {
        point_mutation_model = new K80Model();
    }
    else if (model == "JC69")
    {
        point_mutation_model = new JC69Model();
    }
    else
    {
        throw Exception("Pick a valid point mutation model");
    }
    lethal_mutation_probs.assign(n, 0);

    auto sensitive_posns = RNG.sample_without_replacement(0, n, num_sensitive_posns);
    for (auto sensitive_posn : sensitive_posns)
    {
        lethal_mutation_probs[sensitive_posn] = inactive_probability;
    }
}

PointMutator::~PointMutator()
{
    delete point_mutation_model;
}

void PointMutator::mutate_sequence(Sequence& s, double timestep) const
{
    auto tr_mat = point_mutation_model->get_transition_matrix(timestep);

    long len = s.get_length();
    for (long i=0; i<len; ++i)
    {
        int mutation_index = RNG.choose_event(tr_mat[Consts::NUC_CHAR2INT(s.char_at(i))],
                                              Consts::NUC_COUNT);
        bool is_lethal = RNG.test_event(lethal_mutation_probs[i]);
        s.point_mutate(i, Consts::NUC_INT2CHAR(mutation_index), is_lethal);
    }
}
