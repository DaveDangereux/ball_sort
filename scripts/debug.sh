#!/bin/bash

safe() {
	$@
	if [ $? -ne 0 ]; then
		echo "Build error"
		exit 1
	fi
}

rm -rf build
safe conan install . -s build_type=Debug --build=missing -s compiler.cppstd=20
safe cmake -DENABLE_WARNINGS=ON -DENABLE_WARNINGS_AS_ERRORS=ON --preset conan-debug
safe cmake --build --preset conan-debug
