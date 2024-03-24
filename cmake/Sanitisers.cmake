# -----------------------------------------------------------------------------
# add_sanitiser_flags()
# -----------------------------------------------------------------------------
function(add_sanitiser_flags)
    if(NOT ENABLE_SANITISE_ADDRESS
       AND NOT ENABLE_SANITISE_THREAD
       AND NOT ENABLE_SANITISE_UNDEFINED)
        return()
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES
                                                "GNU")

        add_compile_options("-fno-omit-frame-pointer")
        add_link_options("-fno-omit-frame-pointer")

        if(ENABLE_SANITISE_ADDRESS)
            message(STATUS "[SANITISERS] Address sanitiser active")
            add_compile_options("-fsanitize=address")
            add_link_options("-fsanitize=address")
        endif()

        if(ENABLE_SANITISE_THREAD)
            if(ENABLE_SANITISE_ADDRESS)
                message(
                    WARNING
                        "Thread sanitiser does not work with address sanitiser")
            else()
                message(STATUS "[SANITISERS] Thread sanitiser active")
                add_compile_options("-fsanitize=thread")
                add_link_options("-fsanitize=thread")
            endif()
        endif()

        if(ENABLE_SANITISE_UNDEFINED)
            message(STATUS "[SANITISERS] Undefined behaviour sanitiser active")
            add_compile_options("-fsanitize=undefined")
            add_link_options("-fsanitize=undefined")
        endif()

    elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")

        if(ENABLE_SANITISE_ADDRESS)
            message(STATUS "[SANITISERS] Address sanitiser active")
            add_compile_options("/fsanitize=address")
        endif()

        if(ENABLE_SANITISE_UNDEFINED)
            message(
                WARNING "Undefined behaviour sanitiser not implemented for MSVC"
            )
        endif()

        if(ENABLE_SANITISE_THREAD)
            message(WARNING "Thread sanitiser not implemented for MSVC")
        endif()

    else()
        message(WARNING "Compiler not supported for sanitisers")
    endif()
endfunction()
