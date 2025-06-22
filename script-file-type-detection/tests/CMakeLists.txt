add_executable(stfd_tests
  ArgsTests.cpp
  ../source/Args.cpp
)

target_link_libraries(stfd_tests
  PRIVATE
    gtest
    gtest_main
)
