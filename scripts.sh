#!/bin/bash

project_name=ball_sort
test_executable=ball_sort_tests

god_mode_width=50%
test_pane_height=75%
cmake_pane_width=20%

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
"watch-cmake")
	npx nodemon -e txt --ignore ./build -x "./scripts.sh build-cmake || exit 1"
	;;
"watch-main")
	npx nodemon -e cpp,hpp --ignore ./build -x "clear && ./scripts.sh build-main && ./bin/$project_name || exit 1"
	;;
"watch-tests")
	npx nodemon -e cpp,hpp --ignore ./build -x "clear && ./scripts.sh build-tests && ./bin/$test_executable || exit 1"
	;;
"clean")
	rm -rf build
	;;
"god-mode")
	./scripts.sh build-cmake
	tmux resize-pane -x $god_mode_width
	tmux split-window -v
	tmux resize-pane -y $test_pane_height
	tmux select-pane -t -
	tmux split-window -h
	tmux resize-pane -x $cmake_pane_width
	tmux send-keys -t - "./scripts.sh watch-main" Enter
	tmux select-pane -t +
	tmux send-keys -t - "./scripts.sh watch-cmake" Enter
	tmux send-keys "./scripts.sh watch-tests" Enter
	;;
esac

exit 0
