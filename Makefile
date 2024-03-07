default:
	make clean
	npx nodemon -e cpp,h,hpp --watch app --watch src -x "make -B build && clear && ./bin/ball_sort"

build:
	cmake -B build
	cmake --build build

clean:
	rm -rf build
