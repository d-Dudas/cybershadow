#pragma once

#include <string>
#include <vector>
#include <optional>

std::vector<std::string> parseDirectory(const std::string& path, std::optional<int> depth);
