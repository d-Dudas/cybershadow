#include "FileTypeReader.hpp"
#include "json.hpp"

#include <fstream>

namespace
{
std::vector<std::uint8_t> parsehex(const std::string& hex)
{
    std::vector<std::uint8_t> bytes;
    for(size_t i{0}; i < hex.size(); i += 3)
    {
        auto byteString{hex.substr(i, 2)};
        auto byte{static_cast<std::uint8_t>(std::stoi(byteString, nullptr, 16))};

        bytes.push_back(byte);
    }

    return bytes;
}
} // namespace 

std::optional<std::string> FileTypeReader::readFileSigs(const std::string& fileTypeMapFile)
{
    std::ifstream file(fileTypeMapFile);
    if (not file)
    {
        return "Error opening file type map: " + fileTypeMapFile;
    }

    nlohmann::json j;
    file >> j;

    if (not j.contains("filesigs") or not j["filesigs"].is_array())
    {
        return "Invalid file type map format.";
    }

    for (const auto& entry : j["filesigs"])
    {
        if (not entry.contains("Header (hex)") or not entry.contains("File extension"))
        {
            return "Invalid entry in file type map.";
        }

        std::vector<std::uint8_t> signature{parsehex(entry["Header (hex)"])};
        std::string fileType{entry["File extension"]};
        std::string description{entry["File description"]};

        fileTypeMap[signature] = {fileType, description};
    }

    return std::nullopt;
}

std::string FileTypeReader::getFileType(const std::string& filename) const
{
    std::ifstream
    file(filename, std::ios::binary);
    if (not file)
    {
        throw std::runtime_error("Error opening file: " + filename);
    }

    std::vector<std::uint8_t> header(8);
    file.read(reinterpret_cast<char*>(header.data()), header.size());
    header.resize(file.gcount());

    return getFileType(header);
}

std::string FileTypeReader::getFileType(const std::vector<std::uint8_t>& header) const
{
    for (const auto& [signature, details] : fileTypeMap)
    {
        if (header.size() >= signature.size() && std::equal(signature.begin(), signature.end(), header.begin()))
        {
            return details.type + " (" + details.description + ")";
        }
    }
    return "Unknown";
}