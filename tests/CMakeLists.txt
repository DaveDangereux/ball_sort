find_package(GTest REQUIRED)

enable_testing()

file(GLOB_RECURSE TEST_SOURCE_FILES CONFIGURE_DEPENDS
     ${CMAKE_SOURCE_DIR}/tests/*.cpp)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(${TEST_EXECUTABLE_NAME} ${TEST_SOURCE_FILES} ${SOURCE_FILES})

target_include_directories(${TEST_EXECUTABLE_NAME}
                           PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${TEST_EXECUTABLE_NAME} gtest::gtest fmt::fmt)

if(CMAKE_BUILD_TYPE MATCHES Debug)
  if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
    target_compile_options(
      ${TEST_EXECUTABLE_NAME}
      PRIVATE -g
              -Wall
              -Wextra
              -Wshadow
              -Wconversion
              -Wpedantic
              -Werror)
  endif()
endif()

include(GoogleTest)
gtest_discover_tests(${TEST_EXECUTABLE_NAME})
