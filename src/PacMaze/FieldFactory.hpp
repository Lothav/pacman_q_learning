#ifndef PACMAN_Q_LEARNING_FIELDFACTORY_HPP
#define PACMAN_Q_LEARNING_FIELDFACTORY_HPP

#include <memory>
#include <vector>
#include <sstream>
#include "Field.hpp"

namespace PacMaze
{
    class FieldFactory
    {
    public:

        FieldFactory() = delete;

        /**
         * Field Factory method pattern.
         * Create and returns a Field object.
         * @param s
         * @param field_width
         * @param field_height
         * @return
         */
        static std::unique_ptr<Field> create(std::stringstream s, uint32_t field_width, uint32_t field_height);
    };
}

#endif //PACMAN_Q_LEARNING_FIELDFACTORY_HPP
