#include <iostream>
#include <vector>
#include <cstdint>
#include <fstream>
#include <json.hpp>

#include "Args.hpp"
#include "FileTypeReader.hpp"
#include "FileSystemUtils.hpp"

void printUsage(const std::string& programName)
{
    std::cout << "Usage: " << programName << " -s <path_to_file_type_map> -i <path_to_input_file> [-d <depth>]\n"
              << "Options:\n"
              << "  -i, --input <path>       Specify the input file path\n"
              << "  -s, --sigs <file>        Specify the file type map file/directory\n"
              << "  -d, --depth <depth>      Specify the search depth (when input path is a directory)\n"
              << "  -h, --help               Show this help message\n";
}

int main(int argc, char* argv[])
{
    args::Args args{};
    if(auto error{args.parse(argc, argv)})
    {
        std::cerr << "Error: " << *error << std::endl;
        printUsage(argv[0]);
        return 1;
    }

    FileTypeReader fileTypeReader{};
    if(auto error{fileTypeReader.readFileSigs(args.getFileTypeMapPath())})
    {
        std::cerr << "Error reading file type map: " << *error << std::endl;
        return 1;
    }


    auto files{parseDirectory(args.getInputPath(), args.getDepth())};
    std::cout << "Found " << files.size() << " files to process.\n";
    for (const auto& inputPath : files)
    {
        try
        {
            auto fileType{fileTypeReader.getFileType(inputPath)};
            std::cout << "File type for '" << inputPath << "': " << fileType << '\n';
        }
        catch(const std::exception& e)
        {
            std::cerr << "Failed to determine file type for '" << inputPath << "': " << e.what() << '\n';
            return 1;
        }
    }
    

    return 0;
}
