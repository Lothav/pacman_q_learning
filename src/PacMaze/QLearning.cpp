#include "QLearning.hpp"

namespace PacMaze
{
    QLearning::QLearning(std::unique_ptr<QLearningConfig> config) : config_ (std::move(config))
    {
        std::random_device rd;
        generator_ = std::default_random_engine(rd());
        dist_r_0_to_1_ = std::uniform_real_distribution<double>(0.0, 1.0);
        dist_ui_0_to_4_ = std::uniform_int_distribution<int>(0, 3);
    }

    void QLearning::train()
    {
        uint32_t num_executions = config_->num_executions;

        while (num_executions--) {
            state_t state;

            // Randomize an initial state
            while (true) {
                auto i = dist_r_0_to_1_(generator_);
                auto j = dist_r_0_to_1_(generator_);

                // Generate random numbers...
                auto field_size = config_->field->getFieldSize();
                state = {static_cast<uint32_t>(field_size[0] * i), static_cast<uint32_t>(field_size[1] * j)};
                // ... until we get an valid and empty state.
                if (config_->field->isValidState(state) && config_->field->isEmptyState(state))
                    break;
            }

            while (true) {
                field_action action;
                double rand = dist_r_0_to_1_(generator_);
                if (rand < config_->e_greedy)
                    // Random action.
                    action = field_action_list[dist_ui_0_to_4_(generator_)];
                else
                    // Get action that maximize Q(s, a).
                    action = config_->field->getMaxQ(state).first;

                // Retrieve Q val for current state/action Q(s, a)
                double old_q_val = config_->field->getQ(state, action);
                // Perform action and get the new state
                state_t new_state = config_->field->performAction(state, action);
                // Calc argmax Q(s', a) val for the new state
                double max_q_val = config_->field->getMaxQ(new_state).second;
                // Get reward by performing action 'a'
                int32_t action_reward = config_->field->getStateReward(new_state);

                // Update Q(s, a) = Q(s, a) + alpha * (R(s, a) + y*max{Q(s', a')} - Q(s, a))
                auto new_q_val =
                    old_q_val +
                    config_->learning_rate * ((action_reward + config_->discount_factor * max_q_val) - old_q_val);
                config_->field->updateQ(state, action, new_q_val);

                // S = S'
                state = new_state;

                // Check if new_state is the final state then break
                if (config_->field->isFinalState(state))
                    break;
            }
        }
    }

    std::string QLearning::getStringQ() const
    {
        return config_->field->getStringQ();
    }

    std::string QLearning::getStringPolicy() const
    {
        return config_->field->getStringPolicy();
    }
}