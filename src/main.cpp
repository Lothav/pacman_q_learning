#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

int main(int argc, char* argv[])
{
    std::ifstream f;
    f.open("test.txt");

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

    return EXIT_SUCCESS;
}