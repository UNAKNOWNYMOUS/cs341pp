cmake_minimum_required(VERSION 3.20)

project(cs341pp LANGUAGES CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# clangd + also used for Neovim sanity: compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable testing infrastructure (ctest)
include(CTest)
enable_testing()

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

# Build the playground
# add_subdirectory(testing_tools)
add_subdirectory(assignments)
