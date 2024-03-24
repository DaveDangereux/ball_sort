#!/bin/bash

source $(dirname "$0)")/safe.sh

rm -rf build
safe conan install . -s build_type=Debug --build=missing -s compiler.cppstd=20
safe cmake -DENABLE_SANITISE_ADDRESS=ON -DENABLE_SANITISE_UNDEFINED=ON --preset conan-debug
safe cmake --build --preset conan-debug
