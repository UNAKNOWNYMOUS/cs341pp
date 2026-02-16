#!/bin/bash

cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
# 'cmake' runs the CMake "configure" step.
# '-S .' means source directory is right in this directory.
# '-B build' means put all generated output in './build'.
# '-G Ninja' means generate Ninja files, not Makefiles.
# '-DCMAKE_BUILD_TYPE=Debug' means use debug flags

ln -sf build/compile_commands.json compile_commands.json

cmake --build build # Same as ninja -C build
# Compile + Link
# Can use '--verbose' to see exact compiler commands.

# Useful Ninja Commands:
# ninja -C build            -- build everything default
# ninja -C build hello_app  -- build just one target
# ninja -C build -v         -- verbose (shows compile/link commands)

ctest --test-dir build --output-on-failure
# 'ctest' is CMake's test runner.
# '--test-dir build' tells it where your test metadata is.
# '--output-on-failure' prints failure details instead of hiding them.

# More useful commands for ctest
# ctest --test-dir build              -- run all tests
# ctest --test-dir build -N           -- list tests (don't run)
# ctest --test-dir build -R AddTest   -- run matching tests by regex
