cmake_minimum_required(VERSION 3.10)

project(Cybershadow VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include(GoogleTest)

set(SOURCES
    source/stfd.cpp
    source/Args.cpp
    source/FileTypeReader.cpp
    source/FileSystemUtils.cpp
)

add_executable(stfd ${SOURCES})
include_directories(include)

if (WIN32)
    target_compile_definitions(stfd PRIVATE WINDOWS_PLATFORM)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(stfd PRIVATE -Wall -Wextra -pedantic)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(stfd PRIVATE /W4)
    endif()
endif()

add_subdirectory(tests)
