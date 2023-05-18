#pragma once

#include <cstdint>
#include <vector>

namespace mig {
struct block_position {
    int16_t x;
    int16_t y;
    int16_t z;

    block_position(int16_t x, int16_t y, int16_t z)
        : x(x)
        , y(y)
        , z(z)
    {
    }
};

class world_backend {
public:
    virtual bool get_block(block_position pos, std::vector<uint8_t>& data) = 0;
};
}
