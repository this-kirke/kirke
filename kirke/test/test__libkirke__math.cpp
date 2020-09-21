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

TEST_CASE( "math__max__long", "[math]" ){
    long first = LONG_MIN;
    long second = LONG_MAX;

    REQUIRE( math__max__long( first, first ) == first );
    REQUIRE( math__max__long( first, second ) == second );
    REQUIRE( math__max__long( second, first ) == second );
}

TEST_CASE( "math__min__ulong", "[math]" ){
    unsigned long first = 42;
    unsigned long second = ULONG_MAX;

    REQUIRE( math__min__ulong( first, first ) == first );
    REQUIRE( math__min__ulong( first, second ) == first );
    REQUIRE( math__min__ulong( second, first ) == first );
}

TEST_CASE( "math__max__ulong", "[math]" ){
    unsigned long first = 0;
    unsigned long second = ULONG_MAX;

    REQUIRE( math__max__ulong( first, first ) == first );
    REQUIRE( math__max__ulong( first, second ) == second );
    REQUIRE( math__max__ulong( second, first ) == second );
}

TEST_CASE( "math__min__ullong", "[math]" ){
    unsigned long long first = 42;
    unsigned long long second = ULLONG_MAX;

    REQUIRE( math__min__ullong( first, first ) == first );
    REQUIRE( math__min__ullong( first, second ) == first );
    REQUIRE( math__min__ullong( second, first ) == first );
}

TEST_CASE( "math__max__ullong", "[math]" ){
    unsigned long long first = 0;
    unsigned long long second = ULLONG_MAX;

    REQUIRE( math__max__ullong( first, first ) == first );
    REQUIRE( math__max__ullong( first, second ) == second );
    REQUIRE( math__max__ullong( second, first ) == second );
}

TEST_CASE( "math__nearest_greater_power_of_2__ulong", "[math]" ){
    REQUIRE( math__nearest_greater_power_of_2__ulong( 0 ) == 1 );
    REQUIRE( math__nearest_greater_power_of_2__ulong( 1 ) == 2 );
    REQUIRE( math__nearest_greater_power_of_2__ulong( 2 ) == 4 );
    REQUIRE( math__nearest_greater_power_of_2__ulong( 4 ) == 8 );
    REQUIRE( math__nearest_greater_power_of_2__ulong( 8 ) == 16 );
    REQUIRE( math__nearest_greater_power_of_2__ulong( 16 ) == 32 );
    REQUIRE( math__nearest_greater_power_of_2__ulong( 32 ) == 64 );
    REQUIRE( math__nearest_greater_power_of_2__ulong( 64 ) == 128 );
    REQUIRE( math__nearest_greater_power_of_2__ulong( 128 ) == 256 );

    REQUIRE( math__nearest_greater_power_of_2__ulong( 255 ) == 256 );
    REQUIRE( math__nearest_greater_power_of_2__ulong( 65535 ) == 65536 );
}
