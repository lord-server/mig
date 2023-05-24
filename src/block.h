#pragma once

#include <cstdint>
#include <vector>

namespace mig {
class block {
public:
    block() = default;

    static block parse(const std::vector<uint8_t>& data);

    block(const block&) = delete;
    block& operator=(const block&) = delete;

private:
    std::vector<uint8_t> m_data;
};
}
