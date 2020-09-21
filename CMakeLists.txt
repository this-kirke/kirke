cmake_minimum_required( VERSION 3.12 )

set( CMAKE_VERBOSE_MAKEFILE OFF )

option( KIRKE_BUILD_TESTS "Build tests with project." OFF )
option( KIRKE_BUILD_COVERAGE_REPORT "Build test coverage report with project and tests." OFF )
option( KIRKE_BUILD_DOCUMENTATION "Build project documentation." OFF )

if( CMAKE_CXX_COMPILER_ID STREQUAL "Clang" )
    set( BUILD_COVERAGE_REPORT OFF CACHE BOOL "Compiler is Clang. Disabled BUILD_COVERAGE_REPORT because we don't yet support coverage with Clang." )
endif( CMAKE_CXX_COMPILER_ID STREQUAL "Clang" )

project( kirke )

set( CMAKE_C_STANDARD 11 )
set( CMAKE_C_STANDARD_REQUIRED ON )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON )

add_subdirectory( 3rdParty/Catch2 )
add_subdirectory( kirke )

if( KIRKE_BUILD_TESTS )
    # "catch2__" methods defined in project/3rdParty/Catch2/CMakeLists.txt
    catch2__build_test_executable()
    
    if( KIRKE_BUILD_COVERAGE_REPORT )
        catch2__generate_coverage_report( OUTPUT_DIR ${CMAKE_BINARY_DIR}/docs/coverage )
    endif( KIRKE_BUILD_COVERAGE_REPORT )

endif( KIRKE_BUILD_TESTS )

if( KIRKE_BUILD_DOCUMENTATION )

    find_package( Doxygen )
        
    if( DOXYGEN_FOUND )

        set( DOXYGEN_PROJECT_NAME "libkirke" )
        set( DOXYGEN_PROJECT_BRIEF "Generic functionality for building C applications." )
        set( DOXYGEN_LAYOUT_FILE "${CMAKE_CURRENT_LIST_DIR}/doc/DoxygenLayout.xml" )
        set( DOXYGEN_STRIP_FROM_PATH "${CMAKE_CURRENT_LIST_DIR}" )
        set( DOXYGEN_DISABLE_INDEX YES )
        set( DOXYGEN_GENERATE_TREEVIEW YES )

        set( DOXYGEN_TYPEDEF_HIDES_STRUCT YES )
        set( DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/docs" )
        set( DOXYGEN_HTML_OUTPUT "." )
        set( DOXYGEN_HTML_EXTRA_STYLESHEET "${CMAKE_CURRENT_LIST_DIR}/3rdParty/doxygen_dark_theme/custom_dark_theme.css" "${CMAKE_CURRENT_LIST_DIR}/3rdParty/doxygen_dark_theme/custom.css" )

        set( DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES )
        set( DOXYGEN_EXCLUDE_PATTERNS "*/test/*" )

        doxygen_add_docs(
            docs
            kirke
            doc
            ALL
        )

    endif( DOXYGEN_FOUND )

endif( KIRKE_BUILD_DOCUMENTATION )
