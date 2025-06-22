#pragma once

#include <string>
#include <optional>

namespace args
{
class Args
{
public:
    std::optional<std::string> parse(int argc, char* argv[]);

    std::string getInputPath() const;
    std::string getFileTypeMapPath() const;
    std::optional<int> getDepth() const;

private:
    std::string inputPath;
    std::string fileTypeMapFile;
    std::optional<int> depth;
};
}
