rmdir /s /q .\bin
rmdir /s /q .\build
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
.\bin\Debug\ball_sort_tests.exe
