find_package(GTest REQUIRED)
include(GoogleTest)

file(GLOB_RECURSE TEST_SOURCE_FILES CONFIGURE_DEPENDS
     ${CMAKE_SOURCE_DIR}/tests/*.cpp)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(${TEST_EXECUTABLE_NAME} ${TEST_SOURCE_FILES} ${SOURCE_FILES})
target_link_libraries(${TEST_EXECUTABLE_NAME} gtest::gtest fmt::fmt)
target_include_directories(${TEST_EXECUTABLE_NAME}
                           PRIVATE ${CMAKE_SOURCE_DIR}/include)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET ${TEST_EXECUTABLE_NAME} ENABLE ${ENABLE_WARNINGS} AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

gtest_discover_tests(${TEST_EXECUTABLE_NAME})
