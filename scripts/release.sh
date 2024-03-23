#!/bin/bash

safe() {
	$@
	if [ $? -ne 0 ]; then
		echo "Build error"
		exit 1
	fi
}

rm -rf build
safe conan install . -s build_type=Release --build=missing -s compiler.cppstd=20
safe cmake --preset conan-release
safe cmake --build --preset conan-release
