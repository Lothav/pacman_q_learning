#ifndef PACMAN_Q_LEARNING_FIELD_HPP
#define PACMAN_Q_LEARNING_FIELD_HPP

#include <array>
#include <vector>
#include <cstdint>
#include <unordered_map>

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

    const std::array<field_action, 4> field_action_list = { UP, DOWN, LEFT, RIGHT };
    static std::unordered_map<field_action, std::array<int, 2>> field_state_movement =
    {
        {UP, {0, -1}}, {DOWN, {0, 1}}, {LEFT, {-1, 0}}, {RIGHT, {1, 0}}
    };

    class Field
    {
    private:
        field_t  field_;

    public:
        explicit Field(field_t&& field) : field_(field)
        {}

        bool isValidMove(const state_t& new_state_pos) const
        {
            // Check lower boundaries.
            if(new_state_pos[0] < 0 || new_state_pos[1] < 0)
                return false;
            // Check upper boundaries.
            if(new_state_pos[0] > (field_.size() - 1) || new_state_pos[1] > (field_[0].size() - 1))
                return false;
            // Check if it's a wall.
            if(field_[new_state_pos[0]][new_state_pos[1]].type == WALL)
                return false;

            // Valid move!
            return true;
        }

        state_t getNewState(const state_t& state, field_action action) const
        {
            std::array<int, 2> movement = field_state_movement[action];
            state_t new_state = {state[0] + movement[0], state[1] + movement[1]};
            return isValidMove(new_state) ? new_state : state;
        }

        double getQ(const state_t& state, field_action action)
        {
            return field_[state[0]][state[1]].Q[action];
        }

        void updateQ(const state_t& state, field_action action, double new_val)
        {
            field_[state[0]][state[1]].Q[action] = new_val;
        }

        bool isFinalState(const state_t& state) const
        {
            field_cell_type type = field_[state[0]][state[1]].type;
            return type == PELLET || type == GHOST;
        }

        int32_t getStateReward(const state_t& state)
        {
            return field_[state[0]][state[1]].R;
        }

        std::pair<field_action, double> maxQ(const state_t& state)
        {
            field_action max_q_action = LEFT;

            double max_value = INT32_MIN;
            Q_t q = field_[state[0]][state[1]].Q;

            for (auto& q_it : q) {
                if(q_it .second > max_value){
                    max_q_action = q_it.first;
                    max_value    = q_it.second;
                }
            }

            if(max_value == INT32_MIN)
                throw "Action error!";

            return {max_q_action, max_value};
        }
    };
}

#endif //PACMAN_Q_LEARNING_FIELD_HPP
