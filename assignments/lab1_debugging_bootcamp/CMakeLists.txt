cmake_minimum_required(VERSION 3.20)

project(lab1_debugging_bootcamp LANGUAGES CXX)

add_library(lab1_lib
  src/buggy.cc
)

target_include_directories(lab1_lib
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(lab1_lib PUBLIC cxx_std_17)

# Warnings (good hygiene)
target_compile_options(lab1_lib PRIVATE -Wall -Wextra -Wpedantic)

# ----- Tests -----
add_executable(lab1_tests
  tests/buggy_test.cc
)

target_link_libraries(lab1_tests
  PRIVATE
    lab1_lib
    GTest::gtest_main
)

target_compile_options(lab1_tests PRIVATE -Wall -Wextra -Wpedantic)

# Sanitizers toggle (ON by default in Debug)
option(LAB1_ENABLE_SANITIZERS "Enable ASan/UBSan for Lab 1" ON)

if (LAB1_ENABLE_SANITIZERS AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(lab1_lib PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
  target_link_options(lab1_lib PRIVATE -fsanitize=address,undefined)

  target_compile_options(lab1_tests PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
  target_link_options(lab1_tests PRIVATE -fsanitize=address,undefined)
endif()

include(GoogleTest)
gtest_discover_tests(lab1_tests)
