#!/bin/bash

rm -rf build
conan install . -s build_type=Debug --build=missing
cmake -DBUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=./Debug/generators/conan_toolchain.cmake -B build
cmake --build build --target ball_sort_tests
