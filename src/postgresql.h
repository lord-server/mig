#pragma once

#include <optional>
#include <utility>
#include <vector>

#include <libpq-fe.h>

#include "backend.h"

namespace mig {
class postgresql_backend : public world_backend {
public:
    postgresql_backend() = default;
    ~postgresql_backend();

    static std::optional<postgresql_backend> connect(const char* connection_string);

    bool get_block(block_position pos, std::vector<uint8_t> &data) override;

    postgresql_backend(const postgresql_backend&) = delete;
    postgresql_backend& operator=(const postgresql_backend&) = delete;

    postgresql_backend(postgresql_backend &&other)
    {
        std::swap(m_conn, other.m_conn);
    }

    postgresql_backend& operator=(postgresql_backend &&other)
    {
        std::swap(m_conn, other.m_conn);
        return *this;
    }

private:
    PGconn* m_conn = nullptr;
};

}
