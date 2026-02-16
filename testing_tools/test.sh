#!/bin/bash

ctest --test-dir build --output-on-failure

# 'ctest' is CMake's test runner.
# '--test-dir build' tells it where your test metadata is.
# '--output-on-failure' prints failure details instead of hiding them.
