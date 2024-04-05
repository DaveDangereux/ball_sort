# -----------------------------------------------------------------------------
# target_set_warnings(TARGET <target> [ENABLE <[ON|OFF]> AS_ERRORS <[ON|OFF]>])
# -----------------------------------------------------------------------------
function(target_set_warnings TARGET)
    # Parse keyword arguments
    set(one_value_keywords ENABLE AS_ERRORS)
    cmake_parse_arguments(
        TARGET_SET_WARNINGS
        ""
        "${one_value_keywords}"
        ""
        ${ARGN})

    message("Positional arg: ${TARGET}")
    # Check for required arguments
    if(NOT TARGET)
        message(WARNING "No target supplied to target_set_warnings")
    endif()

    # Set defaults for optional arguments
    if(NOT TARGET_SET_WARNINGS_ENABLE AND NOT ENABLE_WARNINGS)
        message(STATUS "[${TARGET}] Warnings disabled")
        return()
    endif()

    if(NOT TARGET_SET_WARNINGS_AS_ERRORS)
        set(TARGET_SET_WARNINGS_AS_ERRORS ${WARNINGS_AS_ERRORS})
    endif()

    message(STATUS "[${TARGET}] Warnings enabled")

    if(TARGET_SET_WARNINGS_AS_ERRORS)
        message(STATUS "[${TARGET}] Warnings as errors enabled")
    endif()

    set(MSVC_WARNINGS
        # Baseline
        /W4 # Baseline reasonable warnings
        /permissive- # standards conformance mode for MSVC compiler
        # C and C++ Warnings
        /w14242 # 'identifier': conversion from 'type1' to 'type2', possible loss of data
        /w14254 # 'operator': conversion from 'type1:field_bits' to 'type2:field_bits', possible loss of data
        /w14287 # 'operator': unsigned/negative constant mismatch
        /w14296 # 'operator': expression is always 'boolean_value'
        /w14311 # 'variable': pointer truncation from 'type1' to 'type2'
        /w44062 # enumerator in a switch of enum 'enumeration' is not handled
        /w44242 # conversion from 'type1' to 'type2', possible loss of data
        /w14826 # Conversion from 'type1' to 'type2' is sign-extended. This may cause unexpected runtime behavior.
        /w14905 # wide string literal cast to 'LPSTR'
        /w14906 # string literal cast to 'LPWSTR'
        # C++ Only
        /w14263 # 'function': member function does not override any base class virtual member function
        /w14265 # 'classname': class has virtual functions, but destructor is not virtual instances of this class may
                # not be destructed correctly
        /w14640 # Enable warning on thread un-safe static member initialization
        /w14928 # illegal copy-initialization; more than one user-defined conversion has been implicitly applied
        /we4289 # nonstandard extension used: 'variable': loop control variable declared in the for-loop is used outside
                # the for-loop scope
        /w14545 # expression before comma evaluates to a function which is missing an argument list
        /w14546 # function call before comma missing argument list
        /w14547 # 'operator': operator before comma has no effect; expected operator with side-effect
        /w14549 # 'operator': operator before comma has no effect; did you intend 'operator'?
        /w14555 # expression has no effect; expected expression with side- effect
        /w14619 # pragma warning: there is no warning number 'number'
    )

    set(CLANG_WARNINGS
        # Baseline
        -Wall
        -Wextra # reasonable and standard
        -Wshadow # if a variable declaration shadows one from a parent context
        -Wpedantic # warn if non-standard is used
        # C and C++ Warnings
        -Wunused # warn on anything being unused
        -Wformat=2 # warn on security issues around functions that format output
        -Wcast-align # warn for potential performance problem casts
        -Wconversion # warn on type conversions that may lose data
        -Wsign-conversion # warn on sign conversions
        -Wnull-dereference # warn if a null dereference is detected
        -Wdouble-promotion # warn if float is implicit promoted to double
        # C++ Warnings
        -Wnon-virtual-dtor # if a class with virtual func has a non-virtual dest
        -Wold-style-cast # warn for c-style casts
        -Woverloaded-virtual # if you overload (not override) a virtual function
        -Weffc++ # violations from Scott Meyers’ Effective C++
    )

    set(GCC_WARNINGS
        ${CLANG_WARNINGS} -Wduplicated-cond # warn if if / else chain has duplicated conditions
        -Wduplicated-branches # warn if if / else branches have duplicated code
        -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
    )

    if(${TARGET_SET_WARNINGS_AS_ERRORS})
        set(MSVC_WARNINGS ${MSVC_WARNINGS} /WX)
        set(CLANG_WARNINGS ${CLANG_WARNINGS} -Werror)
        set(GCC_WARNINGS ${GCC_WARNINGS} -Werror)
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        set(WARNINGS ${MSVC_WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(WARNINGS ${CLANG_WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        set(WARNINGS ${GCC_WARNINGS})
    else()
        message(WARNING "target_set_warnings CMake function not supported for ${CMAKE_CXX_COMPILER_ID} compiler")
    endif()

    target_compile_options(${TARGET} PRIVATE ${WARNINGS})
endfunction()
