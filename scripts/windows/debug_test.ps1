if (-not (Test-Path $(Get-Command ccache -ErrorAction SilentlyContinue))) {
    Write-Error "ccache is required but it's not installed. Aborting."
    exit 1
}

Remove-Item -Recurse -Force build, bin -ErrorAction SilentlyContinue
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER_LAUNCHER=ccache
cmake --build build
.\bin\Debug\ball_sort_tests.exe
