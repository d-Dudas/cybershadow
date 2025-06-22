#include "Args.hpp"

namespace
{
bool isInputPathFlag(const std::string& arg)
{
    return arg == "--input" || arg == "-i";
}

bool isFileTypeMapFileFlag(const std::string& arg)
{
    return arg == "--sigs" || arg == "-s";
}

bool isDepthFlag(const std::string& arg)
{
    return arg == "--depth" || arg == "-d";
}
}

namespace args
{
std::optional<std::string> Args::parse(int argc, char* argv[])
{
    for(int i = 1; i < argc; i++)
    {
        std::string arg{argv[i]};
        if(isInputPathFlag(arg) && i + 1 < argc)
        {
            inputPath = argv[++i];
        }
        else if(isFileTypeMapFileFlag(arg) && i + 1 < argc)
        {
            fileTypeMapFile = argv[++i];
        }
        else if(isDepthFlag(arg) && i + 1 < argc)
        {
            depth = std::stoi(argv[++i]);
        }
    }

    if(inputPath.empty())
    {
        return "Input path is required.";
    }

    if(fileTypeMapFile.empty())
    {
        return "File type map file is required.";
    }

    return std::nullopt;
}

std::string Args::getInputPath() const
{
    return inputPath;
}

std::string Args::getFileTypeMapFile() const
{
    return fileTypeMapFile;
}

std::optional<int> Args::getDepth() const
{
    return depth;
}
}