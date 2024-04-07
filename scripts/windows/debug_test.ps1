Remove-Item -Recurse -Force build, bin -ErrorAction SilentlyContinue
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
dir bin
dir bin\Debug
# .\bin\Debug\ball_sort_tests.exe
