#include <gtest/gtest.h>
#include "Args.hpp"

TEST(ArgsTests, ParseShouldReturnErrorMessageIfInputPathIsMissing)
{
    char* argv[] = { "program", "--sigs", "fileTypeMap.txt" };
    int argc = sizeof(argv) / sizeof(argv[0]);
    
    args::Args arguments;
    auto result = arguments.parse(argc, argv);
    
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "Input path is required.");
}

TEST(ArgsTests, ParseShouldReturnErrorMessageIfFileTypeMapPathIsMissing)
{
    char* argv[] = { "program", "--input", "input.txt" };
    int argc = sizeof(argv) / sizeof(argv[0]);
    
    args::Args arguments;
    auto result = arguments.parse(argc, argv);
    
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "File type map path is required.");
}

TEST(ArgsTests, ParseShouldReturnEmptyOptionalIfBothPathsAreProvided)
{
    char* argv[] = { "program", "--input", "input.txt", "--sigs", "fileTypeMap.txt" };
    int argc = sizeof(argv) / sizeof(argv[0]);
    
    args::Args arguments;
    auto result = arguments.parse(argc, argv);
    
    EXPECT_FALSE(result.has_value());
    EXPECT_EQ(arguments.getInputPath(), "input.txt");
    EXPECT_EQ(arguments.getFileTypeMapPath(), "fileTypeMap.txt");
    EXPECT_EQ(arguments.getDepth(), std::nullopt);
}

TEST(ArgsTests, ParseShouldReadAllArgumentsCorrectly)
{
    char* argv[] = { "program", "--input", "input.txt", "--sigs", "fileTypeMap.txt", "--depth", "2" };
    int argc = sizeof(argv) / sizeof(argv[0]);
    
    args::Args arguments;
    auto result = arguments.parse(argc, argv);
    
    EXPECT_FALSE(result.has_value());
    EXPECT_EQ(arguments.getInputPath(), "input.txt");
    EXPECT_EQ(arguments.getFileTypeMapPath(), "fileTypeMap.txt");
    EXPECT_EQ(arguments.getDepth(), 2);
}

TEST(ArgsTests, ParseShouldHandleNegativeDepth)
{
    char* argv[] = { "program", "--input", "input.txt", "--sigs", "fileTypeMap.txt", "--depth", "-1" };
    int argc = sizeof(argv) / sizeof(argv[0]);
    
    args::Args arguments;
    auto result = arguments.parse(argc, argv);
    
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "Depth cannot be negative.");
}

TEST(ArgsTests, ParseShouldHandleNonNumericDepth)
{
    char* argv[] = { "program", "--input", "input.txt", "--sigs", "fileTypeMap.txt", "--depth", "abc" };
    int argc = sizeof(argv) / sizeof(argv[0]);
    
    args::Args arguments;
    auto result = arguments.parse(argc, argv);
    
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "Invalid depth value. It should be an integer.");
}
