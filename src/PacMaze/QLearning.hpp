
#ifndef PACMAN_Q_LEARNING_QLEARNING_HPP
#define PACMAN_Q_LEARNING_QLEARNING_HPP

#include <memory>
#include <iostream>
#include "Field.hpp"
#include <random>       /* time */

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
        std::default_random_engine generator_;
        std::uniform_real_distribution<double> dist_r_0_to_1_;
        std::uniform_int_distribution<int> dist_ui_0_to_4_;

    public:
        explicit QLearning(std::unique_ptr<QLearningConfig> config) : config_(std::move(config))
        {
            std::random_device rd;
            generator_      = std::default_random_engine(rd());
            dist_r_0_to_1_  = std::uniform_real_distribution<double>(0.0, 1.0);
            dist_ui_0_to_4_ = std::uniform_int_distribution<int>(0, 3);
        }

        void train()
        {
            std::array<uint32_t, 2> state = {0, 0};
            uint32_t num_executions = config_->num_executions;

            double rand = dist_r_0_to_1_(generator_);
            if(rand < config_->e_greedy)
            {
                auto random_action = field_action_list[dist_ui_0_to_4_(generator_)];
            }
        }
    };
}

#endif //PACMAN_Q_LEARNING_QLEARNING_HPP
