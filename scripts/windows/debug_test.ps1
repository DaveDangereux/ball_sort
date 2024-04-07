Remove-Item -Recurse -Force build, bin -ErrorAction SilentlyContinue
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./bin/Debug/ball_sort_tests.exe
