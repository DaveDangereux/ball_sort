# -----------------------------------------------------------------------------
# Generate variables
# -----------------------------------------------------------------------------
make_names() # generate target names from directory name
find_sources() # find all source files for main and test targets

# -----------------------------------------------------------------------------
# Main target settings
# -----------------------------------------------------------------------------
add_executable(${NAME})
target_sources(${NAME} PRIVATE ${SOURCES})
target_include_directories(${NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(${NAME} PRIVATE fmt::fmt)
target_set_warnings(${NAME})
target_add_sanitisers(${NAME})

include(add_test_targets)
