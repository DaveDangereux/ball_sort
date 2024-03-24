#!/bin/bash

set -e

rm -rf build
conan install . -s build_type=Release --build=missing -s compiler.cppstd=20
cmake -DENABLE_WARNINGS_AS_ERRORS=OFF --preset conan-release
cmake --build --preset conan-release
