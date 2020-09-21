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

TEST_CASE( "log__get_and_set__log_level", "[log]" ){
    REQUIRE( log__get_log_level() == Log__Level__Warning );

    log__set_log_level( Log__Level__Verbose );
    REQUIRE( log__get_log_level() == Log__Level__Verbose );

    log__set_log_level( Log__Level__Debug );
    REQUIRE( log__get_log_level() == Log__Level__Debug );

    log__set_log_level( Log__Level__Info );
    REQUIRE( log__get_log_level() == Log__Level__Info );

    log__set_log_level( Log__Level__Warning );
    REQUIRE( log__get_log_level() == Log__Level__Warning );

    log__set_log_level( Log__Level__Error );
    REQUIRE( log__get_log_level() == Log__Level__Error );

    log__set_log_level( (Log__Level) ( Log__Level__Error + 1 ) );
    REQUIRE( log__get_log_level() == Log__Level__Error );
}
