// System Includes
#include <string.h>

// 3rdParty Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "kirke/kirke.h"

TEST_CASE( "add", "[catch2]" ){
    REQUIRE( add( 41, 1 ) == 42 );
}

TEST_CASE( "multiply", "[catch2]" ){
    REQUIRE( multiply( 21, 2 ) == 42 );
}

TEST_CASE( "say_hello", "[catch2]" ){
    const int buffer_size = 16;
    char buffer[ buffer_size ];

    say_hello( buffer, buffer_size );

    REQUIRE( strncmp( buffer, "Hello!", buffer_size ) == 0 );
}
