// System Includes
#include <string.h>

// 3rdParty Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "kirke/error.h"

TEST_CASE( "error__equals", "[error]" ){
    Error first;
    sprintf( first.type, "Error" );
    first.code = 42;
    sprintf( first.message, "This is an error!" );

    Error second;
    sprintf( second.type, "Error" );
    first.code = 40;
    sprintf( second.message, "This is an error!" );

    REQUIRE( error__equals( &first, &first ) );
    REQUIRE_FALSE( error__equals( &first, &second ) );
}
