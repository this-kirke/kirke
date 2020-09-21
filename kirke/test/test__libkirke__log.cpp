// System Includes
#include <string.h>

// 3rdParty Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "kirke/log.h"

TEST_CASE( "log__level__to_string", "[log]" ){
    REQUIRE( strcmp( log__level__to_string( Log__Level__Verbose ), "Verbose" ) == 0 );
    REQUIRE( strcmp( log__level__to_string( Log__Level__Debug ), "Debug" ) == 0 );
    REQUIRE( strcmp( log__level__to_string( Log__Level__Info ), "Info" ) == 0 );
    REQUIRE( strcmp( log__level__to_string( Log__Level__Warning ), "Warning" ) == 0 );
    REQUIRE( strcmp( log__level__to_string( Log__Level__Error ), "Error" ) == 0 );
    REQUIRE( strcmp( log__level__to_string( (Log__Level) ( Log__Level__Error + 1 ) ), "INVALID" ) == 0 );
}
