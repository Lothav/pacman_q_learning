#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

std::vector<std::vector<char>> readTable(const std::string& path)
{
    std::ifstream f;
    f.open(path);

    std::vector<std::vector<char>> table = {};

    if(f.is_open())
    {
        uint32_t w = 0, h = 0;
        f >> h;
        f >> w;
        f.ignore();

        table.resize(h);

        for (int i = 0; i < h; ++i)
        {
            table[i].resize(w);
            f.getline(table[i].data(), w + 1);
        }
    } else {
        throw "Cannot open file!";
    }

    f.close();

    return table;
}

int main(int argc, char* argv[])
{
    if(argc != 5) {
        std::cerr << "Invalid number of arguments!" << std::endl;
        std::cerr << "Arguments must be <input-file> <learning-rate> <e-greedy> <num-executions>" << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<std::vector<char>> table = readTable(argv[1]);
    double learning_rate = std::atof(argv[2]);
    double e_greedy      = std::atof(argv[3]);
    auto num_executions  = static_cast<uint32_t>(std::atoi(argv[4]));


    return EXIT_SUCCESS;
}