
#ifndef PACMAN_Q_LEARNING_QLEARNING_HPP
#define PACMAN_Q_LEARNING_QLEARNING_HPP

#include <memory>
#include "Field.hpp"

struct QLearningParams
{
    std::unique_ptr<Field>  field;
    double                  learning_rate;
    double                  e_greedy;
    uint32_t                num_executions;
};

class QLearning
{
public:
    explicit QLearning(QLearningParams&& params)
    {
    }
};

#endif //PACMAN_Q_LEARNING_QLEARNING_HPP
