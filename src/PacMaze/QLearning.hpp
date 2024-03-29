#include <utility>


#ifndef PACMAN_Q_LEARNING_QLEARNING_HPP
#define PACMAN_Q_LEARNING_QLEARNING_HPP

#include <memory>
#include <iostream>
#include "Field.hpp"
#include <random>       /* time */
#include <cmath>
#include <fstream>

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

        /**
         * Q learning config data
         */
        std::unique_ptr<QLearningConfig>        config_;

        /**
         * Random generation data
         */
        std::default_random_engine              generator_;
        std::uniform_real_distribution<double>  dist_r_0_to_1_;
        std::uniform_int_distribution<int>      dist_ui_0_to_4_;

    public:

        explicit QLearning(std::unique_ptr<QLearningConfig> config);

        /**
         * Perform a training using given parameters.
         */
        void train();

        /**
         * toString() matrices functions.
         * @return string
         */
        std::string getStringQ() const;
        std::string getStringPolicy() const;
    };
}

#endif //PACMAN_Q_LEARNING_QLEARNING_HPP
