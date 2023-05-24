#pragma once

#include <memory>
#include <string_view>

#include "backend.h"

namespace mig {
class world {
public:
    bool open(std::string_view path);
    bool get_block(block_position pos, std::vector<uint8_t>& data);

private:
    std::unique_ptr<world_backend> m_backend;
};
}
