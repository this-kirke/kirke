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

TEST_CASE( "split_iterator__count", "split_iterator" ){
    String delimiter = string__literal( "," );
    SplitIterator iterator;

    String string2 = string__literal( "0,1,2,3" );
    split_iterator__initialize( &iterator, &string2, &delimiter );
    REQUIRE( split_iterator__count( &iterator ) == 4 );

    String string1 = string__literal( "0,1,2," );
    split_iterator__initialize( &iterator, &string1, &delimiter );
    REQUIRE( split_iterator__count( &iterator ) == 3 );

    String string3 = string__literal( ",,," );
    split_iterator__initialize( &iterator, &string3, &delimiter );
    REQUIRE( split_iterator__count( &iterator ) == 0 );

    String string4 = string__literal( "0123456789" );
    split_iterator__initialize( &iterator, &string4, &delimiter );
    REQUIRE( split_iterator__count( &iterator ) == 1 );

    String string5 = string__literal( "," );
    split_iterator__initialize( &iterator, &string5, &delimiter );
    REQUIRE( split_iterator__count( &iterator ) == 0 );

    String string6 = string__literal( "" );
    split_iterator__initialize( &iterator, &string6, &delimiter );
    REQUIRE( split_iterator__count( &iterator ) == 0 );
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


TEST_CASE( "split_iterator__next", "[split_iterator]" ){
    const unsigned long WORD_COUNT = 4;
    String test_words[ WORD_COUNT ] = {
        string__literal( "This" ),
        string__literal( "is" ),
        string__literal( "a" ),
        string__literal( "test." ),
    };

    String test_string = string__literal( "This,is,a,test." );
    String delimiter = string__literal( "," );

    unsigned long split_index = 0;

    SplitIterator split_iterator;
    split_iterator__initialize( &split_iterator, &test_string, &delimiter );

    String token;

    // Ensure that the first call to split_iterator__next returns 1
    REQUIRE( split_iterator__next( &split_iterator, &token ) );
    REQUIRE( string__equals( &token, &test_words[ split_index++ ] ) );

    while( split_iterator__next( &split_iterator, &token ) ){
        REQUIRE( string__equals( &token, &test_words[ split_index++ ] ) );
    }
}
