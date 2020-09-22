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

TEST_CASE( "array__char__index_of", "[array]" ){
    Array__char array = {
        .data = (char*) "Hello, World!",
        .length = 13,
        .capacity = 14,
        .element_size = 1
    };

    Array__char sequence = {
        .data = (char*) "Wo",
        .length = 2,
        .capacity = 3,
        .element_size = 1
    };

    unsigned long long index;
    REQUIRE( array__char__index_of( &array, &sequence, &index ) );
    REQUIRE( index == 7 );
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

TEST_CASE_METHOD( Array__TestFixture, "array__char__clone", "[array]" ){
    char ARRAY[ 10 ] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };

    Array__char array;
    array__char__initialize__full( &array, system_allocator.allocator, ARRAY, 10, 10 );

    Array__char *clone = array__char__clone( &array, system_allocator.allocator );

    REQUIRE( array__char__equals( clone, &array ) );
}

TEST_CASE_METHOD( Array__TestFixture, "auto_array__char__initialize_and_clear", "[array]" ){
    AutoArray__char auto_array = {0};
    auto_array__char__initialize( &auto_array, system_allocator.allocator, 15 );

    REQUIRE( auto_array.array__char->data != NULL );
    REQUIRE( auto_array.array__char->length == 0 );
    REQUIRE( auto_array.array__char->capacity == 15 );
    REQUIRE( auto_array.array__char->element_size == sizeof( char ) );
    REQUIRE( auto_array.allocator == system_allocator.allocator );

    auto_array__char__clear( &auto_array );

    REQUIRE( auto_array.array__char == NULL );
    REQUIRE( auto_array.allocator == NULL );
}

TEST_CASE_METHOD( Array__TestFixture, "auto_array__char__append_elements", "[array]" ){
    char chars[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    Array__char expected_array = {
        .data = chars,
        .length = 10,
        .capacity = 10,
        .element_size = 1
    };

    AutoArray__char auto_array;
    auto_array__char__initialize( &auto_array, system_allocator.allocator, 10 );

    for( size_t element_index = 0; element_index < 5; element_index++ ){
        auto_array__char__append_elements( &auto_array, 2, &chars[ 2 * element_index ] );
    }

    REQUIRE( array__char__equals( auto_array.array__char, &expected_array ) );
}

TEST_CASE_METHOD( Array__TestFixture, "auto_array__char__append_element", "[array]" ){
    const unsigned long ELEMENT_COUNT = 10;

    char chars[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    Array__char expected_array = {
        .data = chars,
        .length = 10,
        .capacity = 10,
        .element_size = 1
    };

    AutoArray__char auto_array;
    auto_array__char__initialize( &auto_array, system_allocator.allocator, ELEMENT_COUNT );

    for( size_t element_index = 0; element_index < ELEMENT_COUNT; element_index++ ){
        auto_array__char__append_element( &auto_array, element_index );
    }

    REQUIRE( array__char__equals( auto_array.array__char, &expected_array ) );
}


TEST_CASE_METHOD( Array__TestFixture, "auto_array__char__prepend_elements", "[array]" ){
    char values_array[ 5 ] = { 0, 1, 2, 3, 4 };
    Array__char values = {
        .data = values_array,
        .length = ELEMENT_COUNT( values_array ),
        .capacity = ELEMENT_COUNT( values_array ),
        .element_size = sizeof( char )
    };

    char expected_values1_array[ 2 ] = { 0, 1 };
    Array__char expected_values1 = {
        .data = expected_values1_array,
        .length = ELEMENT_COUNT( expected_values1_array ),
        .capacity = ELEMENT_COUNT( expected_values1_array ),
        .element_size = sizeof( char )
    };

    char expected_values2_array[ 3 ] = { 2, 0, 1 };
    Array__char expected_values2 = {
        .data = expected_values2_array,
        .length = ELEMENT_COUNT( expected_values2_array ),
        .capacity = ELEMENT_COUNT( expected_values2_array ),
        .element_size = sizeof( char )
    };

    char expected_values3_array[ 5 ] = { 3, 4, 2, 0, 1 };
    Array__char expected_values3 = {
        .data = expected_values3_array,
        .length = ELEMENT_COUNT( expected_values3_array ),
        .capacity = ELEMENT_COUNT( expected_values3_array ),
        .element_size = sizeof( char )
    };

    AutoArray__char auto_array;
    auto_array__char__initialize( &auto_array, system_allocator.allocator, 0 );

    // Prepend several values to an empty auto_array.
    auto_array__char__prepend_elements( &auto_array, 2, &values.data[ 0 ] );
    REQUIRE( array__char__equals( auto_array.array__char, &expected_values1 ) );

    // Prepend a single value.
    auto_array__char__prepend_elements( &auto_array, 1, &values.data[ 2 ] );
    REQUIRE( array__char__equals( auto_array.array__char, &expected_values2 ) );

    // Prepend several values to a non-empty auto_array.
    auto_array__char__prepend_elements( &auto_array, 2, &values.data[ 3 ] );
    REQUIRE( array__char__equals( auto_array.array__char, &expected_values3 ) );

    // Prepend no values.
    auto_array__char__prepend_elements( &auto_array, 0, &values.data[ 0 ] );
    REQUIRE( array__char__equals( auto_array.array__char, &expected_values3 ) );

    // Prepend no values with NULL data.
    auto_array__char__prepend_elements( &auto_array, 0, NULL );
    REQUIRE( array__char__equals( auto_array.array__char, &expected_values3 ) );

    auto_array__char__clear( &auto_array );
}
