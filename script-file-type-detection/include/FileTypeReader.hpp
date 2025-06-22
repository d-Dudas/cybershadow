#pragma once

#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include <optional>

class FileTypeReader
{
public:
    std::optional<std::string> readFileSigs(const std::string& fileTypeMapFile);
    std::string getFileType(const std::string& filename) const;

private:

    std::string getFileType(const std::vector<std::uint8_t>& header) const;
    

    struct FileDetails
    {
        std::string type;
        std::string description;
    };
    using FileTypeMagicNumber = std::vector<std::uint8_t>;

    std::map<FileTypeMagicNumber, FileDetails> fileTypeMap{};

};
