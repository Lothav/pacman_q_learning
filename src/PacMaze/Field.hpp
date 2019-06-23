#ifndef PACMAN_Q_LEARNING_FIELD_HPP
#define PACMAN_Q_LEARNING_FIELD_HPP

#include <array>
#include <vector>
#include <cstdint>
#include <unordered_map>

namespace PacMaze
{
    enum field_action { UP, DOWN, LEFT, RIGHT };
    const std::array<field_action, 4> field_action_list = {UP, DOWN, LEFT, RIGHT};

    enum field_cell_type
    {
        WALL       = '#',
        EMPTY_PATH = '-',
        GHOST      = '&',
        PELLET     = '0'
    };

    struct FieldCell
    {
        field_cell_type                             type;
        int32_t                                     R;      // Reward Table
        std::unordered_map<field_action, int32_t>   Q;      // Q Table
    };

    typedef std::vector<std::vector<FieldCell>>   field_t;

    class Field
    {
    private:
        field_t  field_;

    public:
        explicit Field(field_t&& field) : field_(field)
        {}

        bool isValidMove(std::array<int32_t, 2>&& new_state_pos) const
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
    };
}

#endif //PACMAN_Q_LEARNING_FIELD_HPP
