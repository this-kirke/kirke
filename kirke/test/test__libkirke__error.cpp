// System Includes
#include <string.h>

// 3rdParty Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "kirke/error.h"

TEST_CASE( "error__equals", "[error]" ){
    Error first = {
        { .type = "Error" },
        .code = 42,
        { .message = "This is an error!" }
    };

    Error second = {
        { .type = "Error" },
        .code = 40,
        { .message = "This is an error!" }
    };

    REQUIRE( error__equals( &first, &first ) );
    REQUIRE_FALSE( error__equals( &first, &second ) );
}
