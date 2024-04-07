# -----------------------------------------------------------------------------
# target_set_flags(<target>)
# -----------------------------------------------------------------------------
function(target_set_flags TARGET)
    if(ENABLE_WARNINGS)
        target_set_warnings(TARGET ${TARGET} ENABLE ${ENABLE_WARNINGS} AS_ERRORS ${WARNINGS_AS_ERRORS})
    endif()
endfunction()
