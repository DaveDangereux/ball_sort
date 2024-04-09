# -----------------------------------------------------------------------------
# Basic project settings
# -----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.28)

project(ball_sort VERSION 1.0.0 LANGUAGES CXX)

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# -----------------------------------------------------------------------------
# Options
# -----------------------------------------------------------------------------
option(ENABLE_WARNINGS "Add warnings to targets" ON)
option(WARNINGS_AS_ERRORS "Treat warnings as errors" ON)
option(ENABLE_TESTS "Build test executables" ON)
option(ENABLE_SANITISER_ADDRESS "Enable address sanitiser" OFF)
option(ENABLE_SANITISER_LEAK "Enable leak sanitiser" OFF)
option(ENABLE_SANITISER_MEMORY "Enable memory sanitiser" OFF)
option(ENABLE_SANITISER_THREAD "Enable thread sanitiser" OFF)
option(ENABLE_SANITISER_UNDEFINED_BEHAVIOUR "Enable undefined behaviour sanitiser" OFF)

# -----------------------------------------------------------------------------
# Global variables
# -----------------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(CPM_SOURCE_CACHE ${CMAKE_SOURCE_DIR}/.cache/CPM)
set(TEST_DEPS GTest::gtest_main GTest::gmock_main)

# -----------------------------------------------------------------------------
# CMake modules
# -----------------------------------------------------------------------------
include(CPM)
include(add_subdirectories)
include(find_sources)
include(make_names)
include(print)
include(target_add_sanitisers)
include(target_set_flags)
include(target_set_warnings)

# -----------------------------------------------------------------------------
# External dependencies
# -----------------------------------------------------------------------------
cpmaddpackage("gh:fmtlib/fmt#10.2.1")

if(ENABLE_TESTS)
    cpmaddpackage("gh:google/googletest@1.14.0")
endif()

# -----------------------------------------------------------------------------
# Find and add all subdirectories containing a CMakeLists.txt file
# -----------------------------------------------------------------------------
add_subdirectories()
