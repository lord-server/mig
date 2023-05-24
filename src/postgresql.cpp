#include <iostream>
#include <vector>

// for htonl()
#include <netinet/in.h>

#include <libpq-fe.h>

#include "postgresql.h"

namespace mig {

static const char* get_block_sql = R"(
    select data
    from blocks
    where posx=$1::int
      and posy=$2::int
      and posz=$3::int)";

std::optional<postgresql_backend> postgresql_backend::connect(const char* connection_string)
{
    postgresql_backend backend;

    backend.m_conn = PQconnectdb(connection_string);
    if (PQstatus(backend.m_conn) != CONNECTION_OK) {
        std::cerr << "unable to connect to postgresql: " << PQerrorMessage(backend.m_conn) << std::endl;
        return {};
    }

    std::cout << "connected to postgres (database `" << PQdb(backend.m_conn) << "`)" << std::endl;

    auto result = PQprepare(backend.m_conn, "get_block", get_block_sql, 3, nullptr);
    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        std::cerr << "unable to prepare SQL request: " << PQerrorMessage(backend.m_conn) << std::endl;
        return {};
    }

    return backend;
}

postgresql_backend::~postgresql_backend()
{
    PQfinish(m_conn);
}

bool postgresql_backend::get_block(block_position pos, std::vector<uint8_t>& data)
{
    auto posx = htonl(int32_t(pos.x));
    auto posy = htonl(int32_t(pos.y));
    auto posz = htonl(int32_t(pos.z));

    const char* params[] = {
        reinterpret_cast<const char*>(&posx),
        reinterpret_cast<const char*>(&posy),
        reinterpret_cast<const char*>(&posz),
    };
    const int lengths[] = { sizeof(posx), sizeof(posy), sizeof(posz) };
    const int formats[] = { 1, 1, 1 };

    auto result = PQexecPrepared(m_conn, "get_block", 3, params, lengths, formats, 1);
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        std::cerr << "unable to get block: " << PQerrorMessage(m_conn) << std::endl;
        return false;
    }

    if (PQntuples(result) < 1) {
        return false;
    }

    auto ptr = PQgetvalue(result, 0, 0);
    auto size = PQgetlength(result, 0, 0);

    data.resize(size);
    std::copy(ptr, ptr + size, data.begin());

    return true;
}
}
