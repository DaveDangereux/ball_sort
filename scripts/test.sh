#!/bin/bash

set -e

rm -rf build
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER_LAUNCHER=ccache -DENABLE_TESTING=ON
cmake --build build
