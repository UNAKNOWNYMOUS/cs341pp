#!/bin/bash

cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
# 'cmake' runs the CMake "configure" step.
# '-S .' means source directory is right in this directory.
# '-B build' means put all generated output in './build'.
# '-G Ninja' means generate Ninja files, not Makefiles.
# '-DCMAKE_BUILD_TYPE=Debug' means use debug flags
