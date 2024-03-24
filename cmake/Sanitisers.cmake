# -----------------------------------------------------------------------------
# add_sanitiser_flags()
# -----------------------------------------------------------------------------
function(add_sanitiser_flags)
    if(NOT ENABLE_SANITISE_ADDRESS AND NOT ENABLE_SANITISE_UNDEFINED)
        message("[SANITISERS] Sanitisers not active")
        return()
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES
                                                "GNU")

        add_compile_options("-fno-omit-frame-pointer")
        add_link_options("-fno-omit-frame-pointer")

        if(ENABLE_SANITISE_ADDRESS)
            message("[SANITISERS] Address sanitiser active")
            add_compile_options("-fsanitize=address")
            add_link_options("-fsanitize=address")
        endif()

        if(ENABLE_SANITISE_THREAD)
            if(ENABLE_SANITISE_ADDRESS OR ENABLE_SANITISE_LEAK)
                message(
                    WARNING
                        "Thread sanitiser does not work with address or leak sanitisers"
                )
            else()
                message("[SANITISERS] Thread sanitiser active")
                add_compile_options("-fsanitize=thread")
                add_link_options("-fsanitize=thread")
            endif()
        endif()

        if(ENABLE_SANITISE_UNDEFINED)
            message("[SANITISERS] Undefined behaviour sanitiser active")
            add_compile_options("-fsanitize=undefined")
            add_link_options("-fsanitize=undefined")
        endif()

    elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")

        if(ENABLE_SANITISE_ADDRESS)
            message("[SANITISERS] Address sanitiser active")
            add_compile_options("/fsanitize=address")
        endif()

        if(ENABLE_SANITISE_UNDEFINED)
            message(
                "[NOTE] Undefined behaviour sanitiser not implemented for MSVC")
        endif()

        if(ENABLE_SANITISE_THREAD)
            message("[NOTE] Thread sanitiser not implemented for MSVC")
        endif()

    else()
        message(ERROR "Compiler not supported for sanitisers")

    endif()
endfunction()
