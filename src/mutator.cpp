#include "point_mutation_models.h"
#include "mutator.h"
#include "rand_maths.h"
#include "sequence.h"

using namespace retrocombinator;

Mutator::Mutator(std::string model)
{
    if (model == "GTR")
    {
        point_mutation_model = new GTRModel();
    }
    else if (model == "TN93")
    {
        point_mutation_model = new TN93Model();
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
}

Mutator::~Mutator()
{
    delete point_mutation_model;
}

void Mutator::mutate_sequence(Sequence& s, double time_per_step) const
{
    auto tr_mat = point_mutation_model->get_transition_matrix(time_per_step);

    size_type n = s.get_length();
    for (size_type i=0; i<n; ++i)
    {
        int mutation_index = RNG.choose_event(tr_mat[Consts::NUC_CHAR2INT(s.char_at(i))],
                                              Consts::NUC_COUNT);
        s.point_mutate(i, Consts::NUC_INT2CHAR(mutation_index));
    }
}

