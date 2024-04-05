# -----------------------------------------------------------------------------
# add_subdirectories(EXCLUDE <folder1> <folder2> ...)
# -----------------------------------------------------------------------------
function(add_subdirectories)
    set(multi_value_keywords EXCLUDE)
    cmake_parse_arguments(
        ADD_SUBDIRECTORIES
        ""
        ""
        "${multi_value_keywords}"
        ${ARGN})

    file(GLOB CHILDREN ${CMAKE_SOURCE_DIR}/*)
    foreach(CHILD ${CHILDREN})
        if(IS_DIRECTORY "${CHILD}" AND EXISTS "${CHILD}/CMakeLists.txt")
            get_filename_component(NAME "${CHILD}" NAME)
            if(NOT NAME IN_LIST ADD_SUBDIRECTORIES_EXCLUDE)
                add_subdirectory("${CHILD}")
            endif()
        endif()
    endforeach()
endfunction()
