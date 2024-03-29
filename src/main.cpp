#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "PacMaze/FieldFactory.hpp"
#include "PacMaze/QLearning.hpp"

int main(int argc, char* argv[])
{
    if(argc != 5)
    {
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

    // Build QLearning Params
    auto params = std::make_unique<PacMaze::QLearningConfig>();
    params->field           = PacMaze::FieldFactory::create(std::move(s), w, h);
    params->learning_rate   = std::atof(argv[2]);
    params->e_greedy        = std::atof(argv[3]);
    params->discount_factor = 0.9;
    params->num_executions  = static_cast<uint32_t>(std::atoi(argv[4]));
    //
    auto ql = std::make_unique<PacMaze::QLearning>(std::move(params));
    ql->train();

    // Open 'q.txt' and 'pi.txt'
    std::ofstream log_q;
    std::ofstream log_policy;
    log_q.open("q.txt");
    log_policy.open("pi.txt");

    // Write Q data into 'q.txt'
    log_q << ql->getStringQ();
    // Write Policy into 'pi.txt'
    log_policy << ql->getStringPolicy();

    // Close log files
    log_q.close();
    log_policy.close();

    return EXIT_SUCCESS;
}