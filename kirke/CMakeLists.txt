set( libkirke__DIR "${CMAKE_CURRENT_LIST_DIR}" )

add_library(
    libkirke
    ${libkirke__DIR}/src/allocator.c
    ${libkirke__DIR}/src/error.c
    ${libkirke__DIR}/src/io.c
    ${libkirke__DIR}/src/log.c
    ${libkirke__DIR}/src/math.c
    ${libkirke__DIR}/src/split_iterator.c
    ${libkirke__DIR}/src/string.c
    ${libkirke__DIR}/src/system_allocator.c
)

target_include_directories(
    libkirke
    PUBLIC
    ${libkirke__DIR}/include
)

set_target_properties(
    libkirke
    PROPERTIES
    OUTPUT_NAME
    kirke
)

target_compile_options(
    libkirke
    PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Werror -Wall -Wextra -pedantic-errors>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

if( KIRKE_BUILD_TESTS )

    if( KIRKE_BUILD_COVERAGE_REPORT )
        target_link_libraries(
            libkirke
            PRIVATE
            gcov
        )

        set_target_properties(
            libkirke
            PROPERTIES
            COMPILE_FLAGS "--coverage"
        )
    endif( KIRKE_BUILD_COVERAGE_REPORT )

    # "catch2__" methods defined in project/3rdParty/Catch2/CMakeLists.txt
    catch2__add_test(
        NAME test__libkirke__array
        SOURCES "${libkirke__DIR}/test/test__libkirke__array.cpp"
        LINK_LIBRARIES libkirke
    )

    catch2__add_test(
        NAME test__libkirke__allocator
        SOURCES "${libkirke__DIR}/test/test__libkirke__allocator.cpp"
        LINK_LIBRARIES libkirke
    )

    catch2__add_test(
        NAME test__libkirke__error
        SOURCES "${libkirke__DIR}/test/test__libkirke__error.cpp"
        LINK_LIBRARIES libkirke
    )

    catch2__add_test(
        NAME test__libkirke__io
        SOURCES "${libkirke__DIR}/test/test__libkirke__io.cpp"
        LINK_LIBRARIES libkirke
    )

    catch2__add_test(
        NAME test__libkirke__log
        SOURCES "${libkirke__DIR}/test/test__libkirke__log.cpp"
        LINK_LIBRARIES libkirke
    )

    catch2__add_test(
        NAME test__libkirke__math
        SOURCES "${libkirke__DIR}/test/test__libkirke__math.cpp"
        LINK_LIBRARIES libkirke
    )

    catch2__add_test(
        NAME test__libkirke__split_iterator
        SOURCES "${libkirke__DIR}/test/test__libkirke__split_iterator.cpp"
        LINK_LIBRARIES libkirke
    )

    catch2__add_test(
        NAME test__libkirke__string
        SOURCES "${libkirke__DIR}/test/test__libkirke__string.cpp"
        LINK_LIBRARIES libkirke
    )

    catch2__add_test(
        NAME test__libkirke__system_allocator
        SOURCES "${libkirke__DIR}/test/test__libkirke__system_allocator.cpp"
        LINK_LIBRARIES libkirke
    )

endif( KIRKE_BUILD_TESTS )
