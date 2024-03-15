#!/bin/bash

project_name=ball_sort
test_executable=ball_sort_tests

if [ $# -eq 0 ]; then
	echo "Usage: $0 <command>"
	exit 1
fi

command=$1

case "$command" in
"build-cmake")
	cmake -B build
	;;
"build-main")
	cmake --build build --target $project_name
	;;
"build-tests")
	cmake --build build --target $test_executable
	;;
"clean")
	rm -rf build
	;;
esac

exit 0
