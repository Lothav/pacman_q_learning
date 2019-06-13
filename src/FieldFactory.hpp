#ifndef PACMAN_Q_LEARNING_FIELDFACTORY_HPP
#define PACMAN_Q_LEARNING_FIELDFACTORY_HPP

#include <memory>
#include <vector>
#include <sstream>
#include "Field.hpp"

class FieldFactory
{
public:

    FieldFactory() = delete;
    static std::unique_ptr<Field> create(std::stringstream s, uint32_t field_width, uint32_t field_height);
};

#endif //PACMAN_Q_LEARNING_FIELDFACTORY_HPP
