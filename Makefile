default:
	make clean
	npx nodemon -e cpp,h,hpp --watch app --watch src --watch include -x "make -B build && clear && ./bin/ball_sort || exit 1"

build:
	cmake -B build
	cmake --build build

clean:
	rm -rf build
