file(GLOB SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/**/*.cpp)

add_executable(${PROJECT_NAME} app.cpp ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wshadow
                                               -Wconversion -Wpedantic -Werror)
