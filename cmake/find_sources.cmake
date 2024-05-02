# -----------------------------------------------------------------------------
# find_sources()
#
# Depends on these local variables: NAME - set by make_names() macro
#
# Sets these variables:
# SOURCES - all .cpp files exclusive of .test.cpp and /tests/*.cpp
# UNIT_TEST_SOURCES - all .test.cpp files
# INTEGRATION_TEST_SOURCES - all .cpp files in /tests
# TEST_SOURCES - all source and test files excluding main.cpp
# -----------------------------------------------------------------------------
macro(find_sources)
    # Find files
    file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
    file(GLOB_RECURSE UNIT_TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.test.cpp")
    file(GLOB_RECURSE INTEGRATION_TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
    set(TEST_SOURCES "${UNIT_TEST_SOURCES}" "${INTEGRATION_TEST_SOURCES}")

    # Remove tests from main sources
    list(REMOVE_ITEM SOURCES ${TEST_SOURCES})

    # Add main sources to unit test sources, minus main.cpp
    if(TEST_SOURCES)
        list(APPEND TEST_SOURCES "${SOURCES}")
        list(FILTER TEST_SOURCES EXCLUDE REGEX "main.cpp")
    endif()
endmacro()
