#include <iostream>
#include <vector>

#include <libpq-fe.h>

#include "postgresql.h"

namespace mig {


std::optional<postgresql_backend> postgresql_backend::connect(const char* connection_string)
{
    postgresql_backend backend;

    backend.m_conn = PQconnectdb(connection_string);
    if (PQstatus(backend.m_conn) != CONNECTION_OK) {
        std::cerr << "unable to connect to postgresql: " << PQerrorMessage(backend.m_conn) << std::endl;
        return {};
    }

    std::cout << "connected to postgres (database `" << PQdb(backend.m_conn) << "`)" << std::endl;

    return backend;
}

postgresql_backend::~postgresql_backend()
{
    PQfinish(m_conn);
}

bool postgresql_backend::get_block(block_position pos, std::vector<uint8_t> &data)
{
    return false;
}
}
