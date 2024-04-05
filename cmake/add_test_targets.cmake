# -----------------------------------------------------------------------------
# Get main target properties
# -----------------------------------------------------------------------------
get_target_property(INCLUDE_DIRS ${NAME} INCLUDE_DIRECTORIES)
get_target_property(LINK_LIBS ${NAME} LINK_LIBRARIES)

if(NOT INCLUDE_DIRS)
    set(INCLUDE_DIRS "")
endif()

if(NOT LINK_LIBS)
    set(LINK_LIBS "")
endif()

# -----------------------------------------------------------------------------
# Test executable settings
# -----------------------------------------------------------------------------
if(ENABLE_TESTS AND TEST_SOURCES)
    add_executable(${TEST_NAME})
    target_sources(${TEST_NAME} PRIVATE ${TEST_SOURCES})
    target_include_directories(${TEST_NAME} PRIVATE "${INCLUDE_DIRS}")
    target_link_libraries(${TEST_NAME} PRIVATE ${LINK_LIBS} ${TEST_DEPS})
    target_set_warnings(${TEST_NAME})
    target_add_address_sanitiser(${TEST_NAME})
    target_add_undefined_behaviour_sanitiser(${TEST_NAME})
endif()
