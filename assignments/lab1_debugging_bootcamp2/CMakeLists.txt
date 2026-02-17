cmake_minimum_required(VERSION 3.20)

project(lab1_debugging_bootcamp2 LANGUAGES CXX)

add_library(lab1b2_lib
  src/buggy2.cc
)

target_include_directories(lab1b2_lib
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(lab1b2_lib PUBLIC cxx_std_17)

target_compile_options(lab1b2_lib PRIVATE -Wall -Wextra -Wpedantic)

add_executable(lab1b2_tests
  tests/buggy2_test.cc
)

target_link_libraries(lab1b2_tests
  PRIVATE
    lab1b2_lib
    GTest::gtest_main
)

target_compile_options(lab1b2_tests PRIVATE -Wall -Wextra -Wpedantic)

option(LAB1B2_ENABLE_SANITIZERS "Enable ASan/UBSan for Lab1B2" ON)

if (LAB1B2_ENABLE_SANITIZERS AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(lab1b2_lib PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
  target_link_options(lab1b2_lib PRIVATE -fsanitize=address,undefined)

  target_compile_options(lab1b2_tests PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
  target_link_options(lab1b2_tests PRIVATE -fsanitize=address,undefined)
endif()

include(GoogleTest)
gtest_discover_tests(lab1b2_tests)
