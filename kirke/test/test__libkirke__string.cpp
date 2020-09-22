// 3rdParty Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "kirke/string.h"
#include "kirke/system_allocator.h"

TEST_CASE( "string__literal__array", "[string]" ){
    char string_literal[] = "This is a string.";

    String string = string__literal( string_literal );

    REQUIRE( string.data == string_literal );
    REQUIRE( string.length == sizeof( string_literal ) - 1 );
    REQUIRE( string.capacity == sizeof( string_literal ) );
    REQUIRE( string.element_size == sizeof( char ) );
}

TEST_CASE( "string__literal__inline", "[string]" ){
    const char string_literal[] = "This is a string.";
    String string = string__literal( "This is a string." );

    REQUIRE( strcmp( string.data, string_literal ) == 0 );
    REQUIRE( string.length == sizeof( string_literal ) - 1 );
    REQUIRE( string.capacity == sizeof( string_literal ) );
    REQUIRE( string.element_size == sizeof( char ) );
}
