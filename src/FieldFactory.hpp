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

    static std::unique_ptr<Field> create(std::stringstream s, uint32_t field_width, uint32_t field_height)
    {
        std::vector<std::vector<field_cell_t>> table = {};
        table.resize(field_height);

        std::vector<char> line = {};
        line.resize(field_width);

        for (int i = 0; i < field_height; ++i)
        {
            table[i].resize(field_width);
            s.getline(line.data(), field_width + 1);
            for (int j = 0; j < line.size(); ++j)
            {
                switch (line[j])
                {
                    case WALL:
                        table[i][j] = WALL;
                        break;
                    case EMPTY_PATH:
                        table[i][j] = EMPTY_PATH;
                        break;
                    case GHOST:
                        table[i][j] = GHOST;
                        break;
                    case PELLET:
                        table[i][j] = PELLET;
                        break;
                    default:
                        throw std::string("Unknown field cell: ") + line[j];
                }
            }
        }

        return std::make_unique<Field>(std::move(table));
    }
};

#endif //PACMAN_Q_LEARNING_FIELDFACTORY_HPP
