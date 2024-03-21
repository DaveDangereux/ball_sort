cmake_minimum_required(VERSION 3.28)

project(ball_sort LANGUAGES CXX)
set(TEST_EXECUTABLE_NAME ball_sort_tests)

find_package(fmt REQUIRED)

option(BUILD_TESTS "Build the test executable" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(app)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()
