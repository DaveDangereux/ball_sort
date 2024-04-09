Remove-Item -Recurse -Force build, bin -ErrorAction SilentlyContinue
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
cd bin
cd Debug
.\ball_sort.exe
