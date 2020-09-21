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


TEST_CASE( "error__set", "[error]" ){
    const char *expected_type = "Error";
    unsigned long long expected_code = 42;
    const char *expected_message = "This is an error!";

    Error error = { 0 };

    error__set( &error, "Error", 42, "This is an %s!", "error" );

    REQUIRE( strcmp( error.type, expected_type ) == 0 );
    REQUIRE( error.code == expected_code );
    REQUIRE( strcmp( error.message, expected_message ) == 0 );
}
