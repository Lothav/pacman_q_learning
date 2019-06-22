#ifndef PACMAN_Q_LEARNING_FIELD_HPP
#define PACMAN_Q_LEARNING_FIELD_HPP

#include <array>
#include <vector>
#include <cstdint>

namespace PacMaze
{
    enum field_cell_type
    {
        WALL       = '#',
        EMPTY_PATH = '-',
        GHOST      = '&',
        PELLET     = '0'
    };

    typedef std::vector<std::vector<field_cell_type>>   field_t;
    typedef std::vector<std::vector<int32_t>>           rewards_t;

    class Field
    {
    private:
        field_t  field_;
        rewards_t rewards_;

    public:
        explicit Field(field_t&& field, rewards_t&& rewards) : field_(field), rewards_(rewards)
        {}

        bool isValidMove(std::array<int32_t, 2> new_state_pos)
        {
            // Check lower boundaries.
            if(new_state_pos[0] < 0 || new_state_pos[1] < 0)
                return false;
            // Check upper boundaries.
            if(new_state_pos[0] > (field_.size() - 1) || new_state_pos[1] > (field_[0].size() - 1))
                return false;
            // Check if it's a wall.
            if(field_[new_state_pos[0]][new_state_pos[1]] == WALL)
                return false;

            // Valid move!
            return true;
        }
    };
}

#endif //PACMAN_Q_LEARNING_FIELD_HPP
