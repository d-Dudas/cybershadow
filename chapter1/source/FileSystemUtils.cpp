#include "FileSystemUtils.hpp"

#include <filesystem>
#include <iostream>

namespace
{
bool isDirectory(const std::string& path)
{
    return std::filesystem::is_directory(path);
}

bool isRegularFile(const std::string& path)
{
    return std::filesystem::is_regular_file(path);
}
}

/*
 * Parses a directory and returns a list of file paths.
 * 
 * If the path is a regular file, it returns a vector containing that file's path.
 * 
 * If the path is a directory, it recursively lists all files within that directory.
 * 
 * If a depth is specified, it limits the recursion to that depth. Otherwise, it lists
 * all files in the directory and its subdirectories.
 */
std::vector<std::string> parseDirectory(const std::string& path, std::optional<int> depth)
{
    if(isRegularFile(path))
    {
        return {path};
    }

    if(not isDirectory(path))
    {
        std::cerr << "Error: " << path << " is not a directory.\n";
        return {};
    }

    std::vector<std::string> files;
    try
    {
        for (const auto& entry : std::filesystem::directory_iterator(path))
        {
            if (entry.is_regular_file())
            {
                files.push_back(entry.path().string());
                continue;
            }

            if (entry.is_directory())
            {
                if (depth && *depth <= 0)
                {
                    continue;
                }

                auto subFiles{parseDirectory(entry.path().string(), depth ? std::make_optional(*depth - 1) : std::nullopt)};
                files.insert(files.end(), subFiles.begin(), subFiles.end());
            }
        }
            
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cerr << "Error accessing directory: " << e.what() << '\n';
    }

    return files;
}
