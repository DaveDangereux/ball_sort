include(FetchContent)

set(TEST_EXECUTABLE ball_sort_tests)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG b479e7a3c161d7087113a05f8cb034b870313a55)

FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB_RECURSE TEST_SOURCE_FILES CONFIGURE_DEPENDS
     ${CMAKE_SOURCE_DIR}/tests/*.cpp)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(${TEST_EXECUTABLE} ${TEST_SOURCE_FILES} ${SOURCE_FILES})

target_include_directories(${TEST_EXECUTABLE}
                           PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${TEST_EXECUTABLE} GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${TEST_EXECUTABLE})
