set(SOURCES
    source/stfd.cpp
    source/Args.cpp
    source/FileTypeReader.cpp
    source/FileSystemUtils.cpp
)
add_executable(sftd ${SOURCES})
include_directories(include)

if (WIN32)
    target_compile_definitions(sftd PRIVATE WINDOWS_PLATFORM)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(sftd PRIVATE -Wall -Wextra -pedantic)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(sftd PRIVATE /W4)
    endif()
endif()
