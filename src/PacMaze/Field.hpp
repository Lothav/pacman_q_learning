#ifndef PACMAN_Q_LEARNING_FIELD_HPP
#define PACMAN_Q_LEARNING_FIELD_HPP

#include <array>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace PacMaze
{
    enum field_action { UP, DOWN, LEFT, RIGHT };

    enum field_cell_type
    {
        WALL       = '#',
        EMPTY_PATH = '-',
        GHOST      = '&',
        PELLET     = '0'
    };

    typedef std::unordered_map<field_action, double> Q_t;
    struct FieldCell
    {
        field_cell_type type;
        int32_t         R;      // Reward Table
        Q_t             Q;      // Q Table
    };

    typedef std::vector<std::vector<FieldCell>>   field_t;
    typedef std::array<uint32_t, 2>               state_t;

    const std::array<field_action, 4> field_action_list = { RIGHT, LEFT, UP, DOWN };
    static std::unordered_map<field_action, std::array<int, 2>> field_state_movement =
        {
            {UP, {-1, 0}}, {DOWN, {1, 0}}, {LEFT, {0, -1}}, {RIGHT, {0, 1}}
        };

    class Field
    {
    private:
        field_t  field_;

    public:

        explicit Field(field_t&& field);
        bool isValidState(const state_t& state) const;
        bool isEmptyState(const state_t& state) const;
        state_t performAction(const state_t& state, field_action action) const;
        double getQ(const state_t& state, field_action action);
        void updateQ(const state_t& state, field_action action, double new_val);
        bool isFinalState(const state_t& state) const;
        int32_t getStateReward(const state_t& state);
        std::array<uint32_t, 2> getFieldSize();
        std::pair<field_action, double> getMaxQ(const state_t &state);
        void printQ();
    };
}

#endif //PACMAN_Q_LEARNING_FIELD_HPP
