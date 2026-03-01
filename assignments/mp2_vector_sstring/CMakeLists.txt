add_library(mp2_lib
  src/sstring.cc
)

target_include_directories(mp2_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(mp2_lib PUBLIC cxx_std_17)
target_compile_options(mp2_lib PRIVATE -Wall -Wextra -Wpedantic)

add_executable(mp2_stage_tests tests/mp2_stage_test.cc)
target_link_libraries(mp2_stage_tests PRIVATE mp2_lib GTest::gtest_main)

add_executable(mp2_unit_tests tests/unit_mp2_test.cc)
target_link_libraries(mp2_unit_tests PRIVATE mp2_lib GTest::gtest_main)

add_executable(mp2_autograder_tests tests/autograder_mp2_test.cc)
target_link_libraries(mp2_autograder_tests PRIVATE mp2_lib GTest::gtest_main)

add_executable(mp2_unit_vector_tests tests/unit_vector_test.cc)
target_link_libraries(mp2_unit_vector_tests PRIVATE mp2_lib GTest::gtest_main)

add_executable(mp2_unit_sstring_tests tests/unit_sstring_test.cc)
target_link_libraries(mp2_unit_sstring_tests PRIVATE mp2_lib GTest::gtest_main)

add_executable(mp2_autograder_vector_tests tests/autograder_vector_test.cc)
target_link_libraries(mp2_autograder_vector_tests PRIVATE mp2_lib GTest::gtest_main)

add_executable(mp2_autograder_sstring_tests tests/autograder_sstring_test.cc)
target_link_libraries(mp2_autograder_sstring_tests PRIVATE mp2_lib GTest::gtest_main)

add_executable(mp2_death_tests tests/death_test.cc)
target_link_libraries(mp2_death_tests PRIVATE mp2_lib GTest::gtest_main)

option(MP2_ENABLE_SANITIZERS "Enable ASan/UBSan for MP2" ON)
if (MP2_ENABLE_SANITIZERS AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  foreach(t mp2_lib
            mp2_unit_vector_tests mp2_unit_sstring_tests
            mp2_autograder_vector_tests mp2_autograder_sstring_tests
            mp2_death_tests
            mp2_unit_tests
            mp2_autograder_tests
            mp2_stage_tests)
    target_compile_options(${t} PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(${t} PRIVATE -fsanitize=address,undefined)
  endforeach()
endif()

include(GoogleTest)
# gtest_discover_tests(mp2_stage_tests)
# gtest_discover_tests(mp2_unit_tests)
# gtest_discover_tests(mp2_autograder_tests)
# gtest_discover_tests(mp2_unit_vector_tests)
# gtest_discover_tests(mp2_unit_sstring_tests)
### gtest_discover_tests(mp2_autograder_vector_tests)
# gtest_discover_tests(mp2_autograder_sstring_tests)
gtest_discover_tests(mp2_death_tests)
