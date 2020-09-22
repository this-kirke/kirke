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


TEST_CASE( "split_iterator__rest", "[split_iterator]" ){
    String string = string__literal( "This,is,a,test." );
    String delimiter = string__literal( "," );

    SplitIterator split_iterator;
    split_iterator__initialize( &split_iterator, &string, &delimiter );

    String rest;

    // Test that for a newly-initialized SplitIterator, split_iterator__rest returns the entire String.
    split_iterator__rest( &split_iterator, &rest );
    REQUIRE( string__equals( &rest, &string ) );

    // Test that split_iterator__rest returns a String from the current position (inclusive) to the end of the string.
    String expected_string = string__literal( "is,a,test." );
    split_iterator.position = 5;
    split_iterator__rest( &split_iterator, &rest );

    REQUIRE( string__equals( &rest, &expected_string ) );
}
