# -----------------------------------------------------------------------------
# make_names()
#
# Sets these variables: NAME - derived from the parent directory of the CMakeLists.txt file UNIT_TEST_NAME - as NAME,
# suffixed with "_unit_tests" INTEGRATION_TEST_NAME - as NAME, suffixed with "_integration_tests"
# -----------------------------------------------------------------------------
macro(make_names)
    get_filename_component(NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
    set(TEST_NAME "${NAME}_tests")
endmacro()
