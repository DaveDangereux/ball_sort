#!/bin/bash

set -e

rm -rf build
conan install . -s build_type=Debug --build=missing -s compiler.cppstd=20
cmake -DENABLE_SANITISE_ADDRESS=ON -DENABLE_SANITISE_UNDEFINED=ON -DENABLE_TESTING=ON --preset conan-debug
cmake --build --preset conan-debug --target ball_sort_tests
