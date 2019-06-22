
#ifndef PACMAN_Q_LEARNING_QLEARNING_HPP
#define PACMAN_Q_LEARNING_QLEARNING_HPP

#include <memory>
#include <iostream>
#include "Field.hpp"

namespace PacMaze
{
    struct QLearningConfig
    {
        std::unique_ptr<Field>  field;
        double                  learning_rate;
        double                  e_greedy;
        uint32_t                num_executions;
    };

    class QLearning
    {
    private:
        std::unique_ptr<QLearningConfig> config_;

    public:
        explicit QLearning(std::unique_ptr<QLearningConfig> config) : config_(std::move(config))
        {}
    };
}

#endif //PACMAN_Q_LEARNING_QLEARNING_HPP
