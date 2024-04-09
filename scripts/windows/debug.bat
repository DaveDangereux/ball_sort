rmdir /S /Q build
rmdir /S /Q bin
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DENABLE_TESTS=OFF
cmake --build build
