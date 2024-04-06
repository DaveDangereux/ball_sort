# -----------------------------------------------------------------------------
# target_add_sanitisers(<target>)
# -----------------------------------------------------------------------------
function(target_add_sanitisers TARGET)
    set(SANITISERS "")

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        if(ENABLE_SANITISER_ADDRESS)
            list(APPEND SANITISERS "address")
            message(STATUS "Address sanitiser active")
        endif()

        if(ENABLE_SANITISER_LEAK)
            list(APPEND SANITISERS "leak")
            message(STATUS "Leak sanitiser active")
        endif()

        if(ENABLE_SANITISER_UNDEFINED_BEHAVIOUR)
            list(APPEND SANITISERS "undefined")
            message(STATUS "Undefined behaviour sanitiser active")
        endif()

        if(ENABLE_SANITISER_THREAD)
            if("address" IN_LIST SANITISERS OR "leak" IN_LIST SANITISERS)
                message(WARNING "Thread sanitiser is incompatible with address or leak sanitisers")
            else()
                list(APPEND SANITISERS "thread")
                message(STATUS "Thread sanitiser active")
            endif()
        endif()

        if(ENABLE_SANITISER_MEMORY)
            message(
                WARNING
                    "Memory sanitiser requires all code (including libc++) to be MSan-instrumented otherwise it reports false positives"
            )
            if("address" IN_LIST SANITISERS
               OR "thread" IN_LIST SANITISERS
               OR "leak" IN_LIST SANITISERS)
                message(WARNING "Memory sanitiser is incompatible with address, thread or leak sanitisers")
            else()
                list(APPEND SANITISERS "memory")
                message(STATUS "Memory sanitiser active")
            endif()
        endif()

    elseif(MSVC)
        if(ENABLE_SANITISER_ADDRESS)
            list(APPEND SANITISERS "address")
            message(STATUS "Address sanitiser active")
        endif()

        if(ENABLE_SANITISER_LEAK
           OR ENABLE_SANITISER_THREAD
           OR ENABLE_SANITISER_MEMORY
           OR ENABLE_SANITISER_UNDEFINED_BEHAVIOUR)
            message(WARNING "MSVC only supports address sanitiser")
        endif()
    endif()

    list(JOIN SANITISERS "," LIST_OF_SANITISERS)

    if(LIST_OF_SANITISERS)
        if(NOT MSVC)
            target_compile_options(${TARGET} PRIVATE -fno-omit-frame-pointer -fsanitize=${LIST_OF_SANITISERS})
            target_link_options(${TARGET} PRIVATE -fno-omit-frame-pointer -fsanitize=${LIST_OF_SANITISERS})
        else()
            target_compile_options(${TARGET} PRIVATE /fsanitize=${LIST_OF_SANITISERS} /Zi /INCREMENTAL:NO)
            target_compile_definitions(${TARGET} PRIVATE _DISABLE_VECTOR_ANNOTATION _DISABLE_STRING_ANNOTATION)
            target_link_options(${TARGET} PRIVATE /INCREMENTAL:NO)
        endif()
    endif()
endfunction()
