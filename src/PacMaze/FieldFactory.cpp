#include "FieldFactory.hpp"

namespace PacMaze
{
    std::unique_ptr<Field> FieldFactory::create(std::stringstream s, uint32_t field_width, uint32_t field_height)
    {
        field_t table = {};
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
                        table[i][j].type = WALL;
                        table[i][j].R    = -1;
                        break;
                    case EMPTY_PATH:
                        table[i][j].type = EMPTY_PATH;
                        table[i][j].R    = -1;
                        break;
                    case GHOST:
                        table[i][j].type = GHOST;
                        table[i][j].R    = -10;
                        break;
                    case PELLET:
                        table[i][j].type = PELLET;
                        table[i][j].R    = 10;
                        break;
                    default:
                        throw std::string("Unknown field cell: ") + line[j];
                }

                table[i][j].Q[UP]    = 0;
                table[i][j].Q[DOWN]  = 0;
                table[i][j].Q[LEFT]  = 0;
                table[i][j].Q[RIGHT] = 0;
            }
        }

        return std::make_unique<Field>(std::move(table));
    }
}