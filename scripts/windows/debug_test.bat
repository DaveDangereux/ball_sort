rmdir /S /Q build
rmdir /S /Q bin
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
echo "Hello meow"
bin\Debug\ball_sort_tests.exe > output.txt 2>&1
type output.txt
