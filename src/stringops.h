#pragma once

#include <string>
#include <vector>

namespace mig {
std::vector<std::string> split_once(const std::string& input, char split);
void trim(std::string& s);
}
