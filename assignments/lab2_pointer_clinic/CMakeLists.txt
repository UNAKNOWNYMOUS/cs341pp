add_library(lab2_lib
  src/pointer_clinic.cc
)
target_include_directories(lab2_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(lab2_lib PUBLIC cxx_std_17)
target_compile_options(lab2_lib PRIVATE -Wall -Wextra -Wpedantic)

add_executable(lab2_unit_tests tests/unit_pointer_clinic_test.cc)
target_link_libraries(lab2_unit_tests PRIVATE lab2_lib GTest::gtest_main)
target_compile_options(lab2_unit_tests PRIVATE -Wall -Wextra -Wpedantic)

add_executable(lab2_autograder_tests tests/autograder_pointer_clinic_test.cc)
target_link_libraries(lab2_autograder_tests PRIVATE lab2_lib GTest::gtest_main)
target_compile_options(lab2_autograder_tests PRIVATE -Wall -Wextra -Wpedantic)

option(LAB2_ENABLE_SANITIZERS "Enable ASan/UBSan for Lab 2" ON)
if (LAB2_ENABLE_SANITIZERS AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  foreach(t lab2_lib lab2_unit_tests lab2_autograder_tests)
    target_compile_options(${t} PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(${t} PRIVATE -fsanitize=address,undefined)
  endforeach()
endif()

include(GoogleTest)
gtest_discover_tests(lab2_unit_tests)
gtest_discover_tests(lab2_autograder_tests)
