add_library(mp1_lib
  src/camel_caser.cc
)

target_include_directories(mp1_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(mp1_lib PUBLIC cxx_std_17)
target_compile_options(mp1_lib PRIVATE -Wall -Wextra -Wpedantic)

add_executable(mp1_tests
  tests/camel_caser_test.cc
)
target_link_libraries(mp1_tests PRIVATE mp1_lib GTest::gtest_main)
target_compile_options(mp1_tests PRIVATE -Wall -Wextra -Wpedantic)

add_executable(mp1_detail_tests
  tests/detail_helpers_test.cc
)
target_link_libraries(mp1_detail_tests PRIVATE mp1_lib GTest::gtest_main)
target_compile_options(mp1_detail_tests PRIVATE -Wall -Wextra -Wpedantic)

option(MP1_ENABLE_SANITIZERS "Enable ASan/UBSan for MP1" ON)
if (MP1_ENABLE_SANITIZERS AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(mp1_lib PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
  target_link_options(mp1_lib PRIVATE -fsanitize=address,undefined)

  target_compile_options(mp1_tests PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
  target_link_options(mp1_tests PRIVATE -fsanitize=address,undefined)

  target_compile_options(mp1_detail_tests PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
  target_link_options(mp1_detail_tests PRIVATE -fsanitize=address,undefined)
endif()

include(GoogleTest)
# gtest_discover_tests(mp1_tests)
gtest_discover_tests(mp1_detail_tests)
