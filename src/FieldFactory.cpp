#include "FieldFactory.hpp"

std::unique_ptr<Field> FieldFactory::create(std::stringstream s, uint32_t field_width, uint32_t field_height)
{
    field_t table = {};
    table.resize(field_height);

    reward_t rewards = {};
    rewards.resize(field_height);

    std::vector<char> line = {};
    line.resize(field_width);

    for (int i = 0; i < field_height; ++i)
    {
        table[i].resize(field_width);
        rewards[i].resize(field_width);
        s.getline(line.data(), field_width + 1);
        for (int j = 0; j < line.size(); ++j)
        {
            switch (line[j])
            {
                case WALL:
                    table[i][j] = WALL;
                    rewards[i][j] = -1;
                    break;
                case EMPTY_PATH:
                    table[i][j] = EMPTY_PATH;
                    rewards[i][j] = -1;
                    break;
                case GHOST:
                    table[i][j] = GHOST;
                    rewards[i][j] = -10;
                    break;
                case PELLET:
                    table[i][j] = PELLET;
                    rewards[i][j] = 10;
                    break;
                default:
                    throw std::string("Unknown field cell: ") + line[j];
            }
        }
    }

    return std::make_unique<Field>(std::move(table), std::move(rewards));
}