#include <algorithm>
#include <sstream>

#include "stringops.h"

namespace mig {
std::vector<std::string> split_once(const std::string& input, char split)
{
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(input);

    if (std::getline(ss, token, split)) {
        tokens.push_back(token);
    }

    std::getline(ss, token);
    tokens.push_back(token);

    return tokens;
}

static void trim_left(std::string& s) {
    auto first_non_space = std::find_if(s.begin(), s.end(), [](char c) { return !std::isspace(c); });
    s.erase(s.begin(), first_non_space);
}

static void trim_right(std::string &s) {
    auto last_non_space = std::find_if(s.rbegin(), s.rend(), [](char c) { return !std::isspace(c); });
    s.erase(last_non_space.base(), s.end());
}

void trim(std::string &s) {
    trim_left(s);
    trim_right(s);
}
}
