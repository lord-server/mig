#include <iostream>

#include "world.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cerr << "usage: mig <world path>" << std::endl;
        return 1;
    }

    mig::world world;
    if (!world.open(argv[1])) {
        std::cerr << "couldn't open world" << std::endl;
        return 1;
    }
}
