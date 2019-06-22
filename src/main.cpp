#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "FieldFactory.hpp"

int main(int argc, char* argv[])
{
    if(argc != 5) {
        std::cerr << "Invalid number of arguments!" << std::endl;
        std::cerr << "Arguments must be <input-file> <learning-rate> <e-greedy> <num-executions>" << std::endl;
        return EXIT_FAILURE;
    }

    std::stringstream s;
    uint32_t w = 0, h = 0;

    {
        std::ifstream f;
        f.open(argv[1]);
        if(!f.is_open()) throw "Cannot open file!";

        // Read field width and height
        f >> h;
        f >> w;
        // ignore rest of the line
        f.ignore();

        // Copy field data to a buffer and close input file
        s << f.rdbuf();
        f.close();
    }

    auto field = FieldFactory::create(std::move(s), w, h);

    double learning_rate = std::atof(argv[2]);
    double e_greedy      = std::atof(argv[3]);
    auto num_executions  = static_cast<uint32_t>(std::atoi(argv[4]));

    return EXIT_SUCCESS;
}