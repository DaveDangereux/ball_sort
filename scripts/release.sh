#!/bin/bash

source $(dirname "$0)")/safe.sh

rm -rf build
safe conan install . -s build_type=Release --build=missing -s compiler.cppstd=20
safe cmake -DENABLE_WARNINGS_AS_ERRORS=OFF --preset conan-release
safe cmake --build --preset conan-release
