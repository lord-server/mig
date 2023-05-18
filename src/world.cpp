#include <fstream>
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "stringops.h"
#include "world.h"

namespace mig {
namespace fs = std::filesystem;

class metadata_file {
public:
    static std::optional<metadata_file> parse(fs::path file_path)
    {
        std::ifstream ifs(file_path);

        if (!ifs.is_open()) {
            return {};
        }

        metadata_file meta;

        std::string line;
        while (std::getline(ifs, line)) {
            auto s = split_once(line, '=');

            if (s.size() != 2) {
                continue;
            }

            trim(s[0]);
            trim(s[1]);

            meta.m_values[s[0]] = s[1];
        }

        return meta;
    }

    std::optional<std::string> postgresql_connection() const
    {
        auto it = m_values.find("pgsql_connection");

        if (it == m_values.end()) {
            return {};
        }

        return it->second;
    }

private:
    std::unordered_map<std::string, std::string> m_values;
};

bool world::open(std::string_view path)
{
    auto metadata_path = fs::path(path) / "world.mt";
    auto metadata = metadata_file::parse(metadata_path);

    if (!metadata) {
        std::cerr << "failed to read world.mt" << std::endl;
        return false;
    }

    auto postgresql_connection = metadata->postgresql_connection();

    if (!postgresql_connection) {
        std::cerr << "world.mt doesn't specify postgresql connection" << std::endl;
        return false;
    }

    std::cout << "postgresql connection: " << *postgresql_connection << std::endl;

    return true;
}
}
