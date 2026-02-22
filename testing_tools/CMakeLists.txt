include(FetchContent)

# ---- Library target (your code) ----
add_library(test_tools_lib
  src/add.cc
  src/string_util.cc
)

target_include_directories(test_tools_lib
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(test_tools_lib PUBLIC cxx_std_17)

# ---- App target (a runnable binary) ----
add_executable(hello_app
  apps/hello_app.cc
)

target_link_libraries(hello_app PRIVATE test_tools_lib)

# Drill 2
add_executable(repeat_app
  apps/repeat_app.cc
)

target_link_libraries(repeat_app PRIVATE test_tools_lib)

# ---- GoogleTest dependency ----
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# Avoid overriding parent project's compiler/linker settings on Windows;
# harmless on Linux, but standard practice.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# ---- Test targets ----
add_executable(add_test tests/add_test.cc)
target_link_libraries(add_test PRIVATE test_tools_lib GTest::gtest_main)

add_executable(string_util_test tests/string_util_test.cc)
target_link_libraries(string_util_test PRIVATE test_tools_lib GTest::gtest_main)

include(GoogleTest)
#gtest_discover_tests(add_test)
#gtest_discover_tests(string_util_test)
