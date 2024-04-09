# -----------------------------------------------------------------------------
# target_add_sanitisers(<target>)
# -----------------------------------------------------------------------------
function(target_add_sanitisers TARGET)
    # -------------------------------------------------------------------------
    # Determine system details
    # -------------------------------------------------------------------------
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        set(GCC TRUE)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
        set(APPLECLANG TRUE)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CLANG TRUE)
    endif()

    set(X86_LIST "AMD64" "IA64" "X86")
    if(CMAKE_SYSTEM_PROCESSOR IN_LIST X86_LIST)
        set(X86 TRUE)
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
        set(ARM64 TRUE)
    endif()

    if(UNIX AND NOT APPLE)
        set(LINUX TRUE)
    endif()

    # -------------------------------------------------------------------------
    # Determine available sanitisers
    # TODO: Test and fill in other system configurations in this list
    # -------------------------------------------------------------------------
    if(APPLECLANG AND ARM64)
        set(SUPPORTED_SANITISERS "address" "thread" "undefined")
    elseif(CLANG AND APPLE AND ARM64)
        set(SUPPORTED_SANITISERS "address" "leak" "thread" "undefined")
    elseif(GCC AND APPLE AND ARM64)
        set(SUPPORTED_SANITISERS "leak")
    elseif(MSVC)
        set(SUPPORTED_SANITISERS "address")
    endif()

    # -------------------------------------------------------------------------
    # Collect supported and enabled sanitisers
    # -------------------------------------------------------------------------
    if(ENABLE_SANITISER_ADDRESS AND "address" IN_LIST SUPPORTED_SANITISERS)
        list(APPEND SANITISERS "address")
    endif()

    if(ENABLE_SANITISER_LEAK AND "leak" IN_LIST SUPPORTED_SANITISERS)
        list(APPEND SANITISERS "leak")
    endif()

    if(ENABLE_SANITISER_UNDEFINED_BEHAVIOUR AND "undefined" IN_LIST SUPPORTED_SANITISERS)
        list(APPEND SANITISERS "undefined")
    endif()

    if(ENABLE_SANITISER_THREAD AND "thread" IN_LIST SUPPORTED_SANITISERS)
        if("address" IN_LIST SANITISERS OR "leak" IN_LIST SANITISERS)
            message(WARNING "Thread sanitiser is incompatible with address or leak sanitisers")
        else()
            list(APPEND SANITISERS "thread")
        endif()
    endif()

    if(ENABLE_SANITISER_MEMORY AND "memory" IN_LIST SUPPORTED_SANITISERS)
        message(
            WARNING
                "Memory sanitiser requires all code (including libc++) to be MSan-instrumented otherwise it reports false positives"
        )
        if("address" IN_LIST SANITISERS OR "thread" IN_LIST SANITISERS OR "leak" IN_LIST SANITISERS)
            message(WARNING "Memory sanitiser is incompatible with address, thread or leak sanitisers")
        else()
            list(APPEND SANITISERS "memory")
        endif()
    endif()

    # -------------------------------------------------------------------------
    # Apply sanitisers
    # -------------------------------------------------------------------------
    list(JOIN SANITISERS "," LIST_OF_SANITISERS)

    if(LIST_OF_SANITISERS)
        message(STATUS "Active sanitisers: ${LIST_OF_SANITISERS}")

        if(NOT MSVC)
            target_compile_options(${TARGET} PRIVATE -fno-omit-frame-pointer -fsanitize=${LIST_OF_SANITISERS})
            target_link_options(${TARGET} PRIVATE -fno-omit-frame-pointer -fsanitize=${LIST_OF_SANITISERS})
        elseif(MSVC)
            target_compile_options(${TARGET} PRIVATE /fsanitize=${LIST_OF_SANITISERS} /Zi /INCREMENTAL:NO)
            target_compile_definitions(${TARGET} PRIVATE _DISABLE_VECTOR_ANNOTATION _DISABLE_STRING_ANNOTATION)
            target_link_options(${TARGET} PRIVATE /INCREMENTAL:NO)
        endif()
    endif()
endfunction()
