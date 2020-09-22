// 3rdParty Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "kirke/array.h"
#include "kirke/system_allocator.h"

char chars_are_equal( const char *first, const char *second ){
    if( *first == *second ){
        return 1;
    }

    return 0;
}

ARRAY__DECLARE( Array__char, array__char, char )
ARRAY__DEFINE( Array__char, array__char, char, chars_are_equal )

TEST_CASE( "array__char__equals", "[array]" ){
    Array__char first = {
        .data = (char*) "Array 1",
        .length = 7,
        .capacity = 8,
        .element_size = 1
    };

    Array__char second = {
        .data = (char*) "Array 2",
        .length = 7,
        .capacity = 8,
        .element_size = 1
    };

    REQUIRE( array__char__equals( &first, &first ) == true );
    REQUIRE( array__char__equals( &first, &second ) == false );
}

TEST_CASE( "array__char__clear_elements", "[array]" ){
    char data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    Array__char array = {
        .data = data,
        .length = 10,
        .capacity = 10,
        .element_size = sizeof( char )
    };

    array__char__clear_elements( &array, 4, 2 );

    REQUIRE( array.capacity == 10 );
    REQUIRE( array.length == 10 );

    for( size_t element_index = 0; element_index < array.length; element_index++ ){
        if( element_index == 4 || element_index == 5 ){
            REQUIRE( array.data[ element_index ] == 0 );
        }
        else{
            REQUIRE( array.data[ element_index ] == element_index );
        }
    }
}

class Array__TestFixture{
    protected:
        Array__TestFixture(){
            system_allocator__initialize( &system_allocator, NULL );
        }

        ~Array__TestFixture(){
            system_allocator__deinitialize( &system_allocator );
        }

        SystemAllocator system_allocator;
};

TEST_CASE_METHOD( Array__TestFixture, "array__char__initialize_and_clear", "[array]" ){
    Array__char array;
    array__char__initialize( &array, system_allocator.allocator, 10 );

    REQUIRE( array.data != NULL );
    REQUIRE( array.capacity == 10 );

    array__char__clear( &array, system_allocator.allocator );

    REQUIRE( array.data == NULL );
    REQUIRE( array.length == 0 );
    REQUIRE( array.capacity == 0 );
    REQUIRE( array.element_size == 1 );
}

TEST_CASE_METHOD( Array__TestFixture, "array__char__initialize__full_and_clear", "[array]" ){
    char ARRAY[ 10 ] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
    Array__char expected_array = {
        .data = ARRAY,
        .length = 10,
        .capacity = 10,
        .element_size = sizeof( char )
    };

    Array__char array;
    array__char__initialize__full( &array, system_allocator.allocator, ARRAY, 10, 10 );

    REQUIRE( array__char__equals( &array, &expected_array ) );

    array__char__clear( &array, system_allocator.allocator );
}
