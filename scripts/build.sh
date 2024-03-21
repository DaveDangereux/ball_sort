#!/bin/bash

rm -rf build
conan install . -s build_type=Release --build=missing
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=./Release/generators/conan_toolchain.cmake -B build
cmake --build build
