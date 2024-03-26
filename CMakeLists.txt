cmake_minimum_required(VERSION 3.28)

project(
    ball_sort
    VERSION 1.0.0
    LANGUAGES CXX)

# Global CMake variables
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Options
option(ENABLE_WARNINGS "Enable to add warnings to a target" ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable to treat warnings as errors" ON)
option(ENABLE_TESTING "Enable a Unit Testing build" OFF)
option(ENABLE_SANITISE_ADDRESS "Enable address sanitiser" OFF)
option(ENABLE_SANITISE_THREAD "Enable thread sanitiser" OFF)
option(ENABLE_SANITISE_UNDEFINED "Enable undefined behaviour sanitiser" OFF)

# Project / Library Names
set(EXECUTABLE_NAME ${PROJECT_NAME})
set(TEST_EXECUTABLE_NAME "${PROJECT_NAME}_tests")

# CMake Modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(Print)

if(ENABLE_WARNINGS)
    include(Warnings)
endif()

if(ENABLE_SANITISE_ADDRESS
   OR ENABLE_SANITISE_THREAD
   OR ENABLE_SANITISE_UNDEFINED)
    include(Sanitisers)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        add_compile_options(-Zi)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        add_compile_options(-g)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU
  ")
        add_compile_options(-g)
    endif()
endif()

# External Libraries
find_package(fmt REQUIRED)

# Subdirectories
add_subdirectory(app)
if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
