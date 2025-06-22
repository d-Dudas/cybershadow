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
