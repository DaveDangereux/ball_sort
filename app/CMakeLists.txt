file(GLOB SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/**/*.cpp)

add_executable(${PROJECT_NAME} app.cpp ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

if(CMAKE_BUILD_TYPE MATCHES Debug)
  if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
    target_compile_options(
      ${PROJECT_NAME}
      PRIVATE -g
              -Wall
              -Wextra
              -Wshadow
              -Wconversion
              -Wpedantic
              -Werror)
  endif()
endif()
