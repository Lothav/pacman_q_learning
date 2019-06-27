#include <fstream>
#include <memory>
#include "Field.hpp"

namespace PacMaze
{
    Field::Field(field_t&& field) : field_(field) {};

    bool Field::isValidState(const state_t& state) const
    {
        // Check lower boundaries.
        if(state[0] < 0 || state[1] < 0)
            return false;
        // Check upper boundaries.
        if(state[0] > (field_.size() - 1) || state[1] > (field_[0].size() - 1))
            return false;
        // Check if it's a wall.
        if(field_[state[0]][state[1]].type == WALL)
            return false;

        // Valid move!
        return true;
    }

    bool Field::isEmptyState(const state_t& state) const
    {
        return field_[state[0]][state[1]].type == EMPTY_PATH;
    }

    state_t Field::performAction(const state_t& state, field_action action) const
    {
        std::array<int, 2> movement = field_state_movement[action];
        state_t new_state = {state[0] + movement[0], state[1] + movement[1]};
        return isValidState(new_state) ? new_state : state;
    }

    double Field::getQ(const state_t& state, field_action action)
    {
        return field_[state[0]][state[1]].Q[action];
    }

    void Field::updateQ(const state_t& state, field_action action, double new_val)
    {
        field_[state[0]][state[1]].Q[action] = new_val;
    }

    bool Field::isFinalState(const state_t& state) const
    {
        field_cell_type type = field_[state[0]][state[1]].type;
        return type == PELLET || type == GHOST;
    }

    int32_t Field::getStateReward(const state_t& state)
    {
        return field_[state[0]][state[1]].R;
    }

    std::array<uint32_t, 2> Field::getFieldSize()
    {
        return {static_cast<uint32_t>(field_.size()), static_cast<uint32_t>(field_[0].size())};
    }

    std::pair<field_action, double> Field::getMaxQ(const state_t &state)
    {
        field_action max_q_action = LEFT;

        double max_value = INT32_MIN;
        Q_t q = field_[state[0]][state[1]].Q;

        for (auto& q_it : q) {
            if(q_it.second > max_value){
                max_q_action = q_it.first;
                max_value    = q_it.second;
            }
        }

        if(max_value == INT32_MIN)
            throw "Invalid Q!";

        return {max_q_action, max_value};
    }

    std::string Field::getStringQ() const
    {
        std::stringstream s;

        for (uint i = 0; i < field_.size(); i++)
        {
            for (uint j = 0; j < field_[i].size(); j++)
            {
                auto field_cell = field_[i][j];
                if(field_cell.type != EMPTY_PATH) continue;

                for (uint k = 0; k < field_action_list.size(); k++)
                {
                    std::ostringstream q_stream_format;
                    q_stream_format << std::fixed;
                    q_stream_format << std::setprecision(3);
                    q_stream_format << field_cell.Q[field_action_list[k]];

                    auto prefix = std::array<char, 4>{'R', 'L', 'U', 'D'}[k];
                    s << std::to_string(i) << ',' << std::to_string(j) << ',';
                    s << prefix << ',' << q_stream_format.str() << std::endl;
                }
            }
        }

        return s.str();
    }

    std::string Field::getStringPolicy()
    {
        std::stringstream s;

        for (uint i = 0; i < field_.size(); i++)
        {
            for (uint j = 0; j < field_[i].size(); j++)
            {
                auto cell = field_[i][j];

                if(cell.type == EMPTY_PATH)
                {
                    auto max_q = this->getMaxQ({i, j});
                    s << static_cast<char>(max_q.first);
                    continue;
                }

                s << static_cast<char>(cell.type);
            }

            s << std::endl;
        }

        return s.str();
    }
}