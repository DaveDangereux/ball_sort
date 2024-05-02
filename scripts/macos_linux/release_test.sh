#!/bin/bash

set -e

command -v ccache >/dev/null 2>&1 || {
	echo >&2 "ccache is required but it's not installed. Aborting."
	exit 1
}

rm -rf build bin
cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER_LAUNCHER=ccache
cmake --build build
./bin/ball_sort_tests
