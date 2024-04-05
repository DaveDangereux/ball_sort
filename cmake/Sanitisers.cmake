# -----------------------------------------------------------------------------
# target_add_address_sanitiser(<target>)
# -----------------------------------------------------------------------------
function(target_add_address_sanitiser TARGET)
    if(NOT ENABLE_SANITISE_ADDRESS)
        return()
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        target_compile_options(${TARGET} PRIVATE "-fno-omit-frame-pointer")
        target_link_options(${TARGET} PRIVATE "-fno-omit-frame-pointer")

        target_compile_options(${TARGET} PRIVATE "-fsanitize=address")
        target_link_options(${TARGET} PRIVATE "-fsanitize=address")

        message(STATUS "[${TARGET}] Address sanitiser active")

    elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        message(STATUS "[${TARGET}] Address sanitiser active")
        target_add_compile_options(${TARGET} PRIVATE "/fsanitize=address")

    else()
        message(WARNING "Compiler not supported for sanitisers")

    endif()

endfunction()

# -----------------------------------------------------------------------------
# target_add_undefined_behaviour_sanitiser()
# -----------------------------------------------------------------------------
function(target_add_undefined_behaviour_sanitiser TARGET)
    if(NOT ENABLE_SANITISE_UNDEFINED)
        return()
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        target_compile_options(${TARGET} PRIVATE "-fno-omit-frame-pointer")
        target_link_options(${TARGET} PRIVATE "-fno-omit-frame-pointer")

        message(STATUS "[${TARGET}] Undefined behaviour sanitiser active")
        target_compile_options(${TARGET} PRIVATE "-fsanitize=undefined")
        target_link_options(${TARGET} PRIVATE "-fsanitize=undefined")

    elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        message(WARNING "Undefined behaviour sanitiser not implemented for MSVC")

    else()
        message(WARNING "Compiler not supported for sanitisers")

    endif()
endfunction()

# -----------------------------------------------------------------------------
# target_add_thread_sanitiser(<target>)
# -----------------------------------------------------------------------------
function(target_add_thread_sanitiser TARGET)
    if(NOT ENABLE_SANITISE_THREAD)
        return()
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        target_compile_options(${TARGET} PRIVATE "-fno-omit-frame-pointer")
        target_link_options(${TARGET} PRIVATE "-fno-omit-frame-pointer")

        if(ENABLE_SANITISE_ADDRESS)
            message(WARNING "Thread sanitiser does not work with address sanitiser")
        else()
            message(STATUS "[${TARGET}] Thread sanitiser active")
            add_compile_options("-fsanitize=thread")
            add_link_options("-fsanitize=thread")
        endif()

    elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        message(WARNING "Thread sanitiser not implemented for MSVC")

    else()
        message(WARNING "Compiler not supported for sanitisers")

    endif()
endfunction()
