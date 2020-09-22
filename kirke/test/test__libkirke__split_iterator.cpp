// 3rdParty Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "kirke/split_iterator.h"
#include "kirke/string.h"

TEST_CASE( "split_iterator__initialize", "[split_iterator]" ){
    String string = string__literal( "This,is,a,test." );
    String delimiter = string__literal( "," );

    SplitIterator split_iterator;
    split_iterator__initialize( &split_iterator, &string, &delimiter );

    // Explicitly checking memory address - this is not just an equivalent string.
    REQUIRE( split_iterator.string == &string );
    REQUIRE( split_iterator.delimiter == &delimiter );

    REQUIRE( split_iterator.position == 0 );
}
