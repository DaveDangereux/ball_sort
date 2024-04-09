where sccache >nul 2>&1
if errorlevel 1 (
    echo sccache is required but it's not installed. Aborting.
    exit /b 1
)

rmdir /S /Q build
rmdir /S /Q bin
cmake -B build -DCMAKE_BUILD_TYPE=Release -DENABLE_TESTS=OFF -DCMAKE_CXX_COMPILER_LAUNCHER=sccache
cmake --build build
