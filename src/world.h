#pragma once

#include <memory>
#include <string_view>

namespace mig {
struct block_position {
    int16_t x;
    int16_t y;
    int16_t z;

    block_position(int16_t x, int16_t y, int16_t z)
        : x(x), y(y), z(z)
    {}
};

class world_backend {
public:
    virtual bool get_block(block_position pos) = 0;
};

class world {
public:
    bool open(std::string_view path);

private:
    std::unique_ptr<world_backend> m_backend;
};
}
