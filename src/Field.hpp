#ifndef PACMAN_Q_LEARNING_FIELD_HPP
#define PACMAN_Q_LEARNING_FIELD_HPP

#include <vector>

enum field_cell_t
{
    WALL       = '#',
    EMPTY_PATH = '-',
    GHOST      = '&',
    PELLET     = '0'
};

typedef std::vector<std::vector<field_cell_t>> field_t;

class Field
{

private:
    field_t field_;

public:
    explicit Field(field_t&& field) : field_(field)
    {

    }
};

#endif //PACMAN_Q_LEARNING_FIELD_HPP
