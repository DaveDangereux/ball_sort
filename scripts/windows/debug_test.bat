rmdir /S /Q build
rmdir /S /Q bin
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
bin\Debug\ball_sort_tests.exe
