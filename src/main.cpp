#include <iostream>

#include "script.h"
#include "world.h"

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "usage: mig <world path>" << std::endl;
        return 1;
    }

    mig::script_env script;

    mig::world world;
    if (!world.open(argv[1])) {
        std::cerr << "unable to open world" << std::endl;
        return 1;
    }


    mig::block_position center(0, 0, 0);
    std::vector<uint8_t> data;
    if (world.get_block(center, data)) {
        std::cout << int(data[0]) << std::endl;
    }
}
