#include "Args.hpp"

#include <stdexcept>

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
/*
 * Parses command line arguments.
 * Returns an error message if parsing fails, or std::nullopt if successful.
 */
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
            try
            {
                depth = std::stoi(argv[++i]);
            }
            catch(...)
            {
                return "Invalid depth value. It should be an integer.";
            }
            
        }
    }

    if(inputPath.empty())
    {
        return "Input path is required.";
    }

    if(fileTypeMapFile.empty())
    {
        return "File type map path is required.";
    }

    if(depth.has_value() && *depth < 0)
    {
        return "Depth cannot be negative.";
    }

    return std::nullopt;
}

/**
 * Returns the input path.
 */
std::string Args::getInputPath() const
{
    return inputPath;
}

/**
 * Returns the file type map path.
 */
std::string Args::getFileTypeMapPath() const
{
    return fileTypeMapFile;
}

/**
 * Returns the depth value, if set.
 * If not set, returns std::nullopt.
 */
std::optional<int> Args::getDepth() const
{
    return depth;
}
} // namespace args
