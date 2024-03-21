find_package(GTest REQUIRED)

enable_testing()

file(GLOB_RECURSE TEST_SOURCE_FILES CONFIGURE_DEPENDS
     ${CMAKE_SOURCE_DIR}/tests/*.cpp)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(${TEST_EXECUTABLE_NAME} ${TEST_SOURCE_FILES} ${SOURCE_FILES})

target_include_directories(${TEST_EXECUTABLE_NAME}
                           PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${TEST_EXECUTABLE_NAME} gtest::gtest)

include(GoogleTest)
gtest_discover_tests(${TEST_EXECUTABLE_NAME})
