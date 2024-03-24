file(GLOB SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/**/*.cpp)

add_executable(${EXECUTABLE_NAME} app.cpp ${SOURCE_FILES})
target_link_libraries(${EXECUTABLE_NAME} PRIVATE fmt::fmt)
target_include_directories(${EXECUTABLE_NAME}
                           PRIVATE ${CMAKE_SOURCE_DIR}/include)

if(${ENABLE_WARNINGS})
    target_set_warnings(TARGET ${EXECUTABLE_NAME} ENABLE ${ENABLE_WARNINGS}
                        AS_ERRORS ${ENABLE_WARNINGS_AS_ERRORS})
endif()
