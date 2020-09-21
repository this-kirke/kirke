// System Includes
#include <limits.h>

// 3rdParty Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "kirke/math.h"

TEST_CASE( "math__min__long", "[math]" ){
    long first = LONG_MIN;
    long second = LONG_MAX;

    REQUIRE( math__min__long( first, first ) == first );
    REQUIRE( math__min__long( first, second ) == first );
    REQUIRE( math__min__long( second, first ) == first );
}
