#ifndef PACMAN_Q_LEARNING_FIELD_HPP
#define PACMAN_Q_LEARNING_FIELD_HPP

#include <vector>
#include <cstdint>

namespace PacMaze
{
    enum field_cell_t
    {
        WALL       = '#',
        EMPTY_PATH = '-',
        GHOST      = '&',
        PELLET     = '0'
    };

    typedef std::vector<std::vector<field_cell_t>> field_t;
    typedef std::vector<std::vector<int32_t>>      reward_t;

    class Field
    {
    private:
        field_t  field_;
        reward_t rewards_;

    public:
        explicit Field(field_t&& field, reward_t&& rewards) : field_(field), rewards_(rewards)
        {}
    };
}

#endif //PACMAN_Q_LEARNING_FIELD_HPP
