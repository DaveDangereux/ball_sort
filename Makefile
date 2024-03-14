PROJECT_NAME := ball_sort
TEST_EXECUTABLE := ball_sort_tests

GOD_MODE_WIDTH := 50%
TEST_PANE_HEIGHT := 75%
CMAKE_PANE_WIDTH := 20%

default:
	npx nodemon -e cpp,hpp --ignore build --ignore tests -x "clear && make -B build && clear && ./bin/$(PROJECT_NAME) || exit 1"

test:
	npx nodemon -e cpp,hpp --ignore build -x "make build-tests && clear && (cd build && ./bin/$(TEST_EXECUTABLE)) || exit 1"

cmake:
	npx nodemon -e txt --ignore build -x "clear && cmake -B build || exit 1"

build:
	cmake --build build --target $(PROJECT_NAME)

build-tests:
	cmake --build build --target $(TEST_EXECUTABLE)

god-mode:
	tmux resize-pane -x $(GOD_MODE_WIDTH)
	tmux split-window -v
	tmux resize-pane -y $(TEST_PANE_HEIGHT)
	tmux select-pane -t -
	tmux split-window -h
	tmux resize-pane -x $(CMAKE_PANE_WIDTH)
	tmux send-keys -t - "clear && make" Enter
	tmux select-pane -t +
	tmux send-keys -t - "clear && make cmake" Enter
	tmux send-keys "clear && make test" Enter

clean:
	rm -rf build
