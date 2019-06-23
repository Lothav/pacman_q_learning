
#ifndef PACMAN_Q_LEARNING_QLEARNING_HPP
#define PACMAN_Q_LEARNING_QLEARNING_HPP

#include <memory>
#include <iostream>
#include "Field.hpp"
#include <random>       /* time */
#include <cmath>

namespace PacMaze
{
    struct QLearningConfig
    {
        std::unique_ptr<Field>  field;
        double                  learning_rate;
        double                  e_greedy;
        double                  discount_factor;
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
            uint32_t num_executions = config_->num_executions;

            while(num_executions--)
            {
                state_t state = {1, 1};

                while(true)
                {
                    field_action action;
                    double rand = dist_r_0_to_1_(generator_);
                    if(rand < config_->e_greedy)
                        // Random action.
                        action = field_action_list[dist_ui_0_to_4_(generator_)];
                    else
                        // Get action that maximize Q(s, a).
                        action = config_->field->maxQ(state).first;

                    state_t new_state = config_->field->getNewState(state, action);
                    double max_q_val = config_->field->maxQ(new_state).second;
                    int32_t state_reward = config_->field->getStateReward(new_state);

                    double old_q_val = config_->field->getQ(state, action);

                    auto new_q_val =
                        old_q_val + config_->e_greedy * ((state_reward + config_->discount_factor * max_q_val) - old_q_val);

                    config_->field->updateQ(state, action, new_q_val);

                    state = new_state;

                    if(config_->field->isFinalState(state))
                        break;
                }
            }
        }
    };
}

#endif //PACMAN_Q_LEARNING_QLEARNING_HPP
