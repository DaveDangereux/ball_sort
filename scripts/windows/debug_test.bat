rmdir -r -q build
rmdir -r -q bin
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
bin\Debug\ball_sort_tests
