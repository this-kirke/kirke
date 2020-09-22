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
