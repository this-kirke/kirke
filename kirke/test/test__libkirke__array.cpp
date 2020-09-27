// 3rdParty Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "kirke/array.h"
#include "kirke/system_allocator.h"

char chars_are_equal( char first, char second ){
    if( first == second ){
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

    REQUIRE( array__char__equals( first, first ) == true );
    REQUIRE( array__char__equals( first, second ) == false );
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

    REQUIRE( array__char__equals( array, expected_array ) );

    array__char__clear( &array, system_allocator.allocator );
}

TEST_CASE_METHOD( Array__TestFixture, "array__char__clone", "[array]" ){
    char ARRAY[ 10 ] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };

    Array__char array;
    array__char__initialize__full( &array, system_allocator.allocator, ARRAY, 10, 10 );

    Array__char *clone = array__char__clone( &array, system_allocator.allocator );

    REQUIRE( array__char__equals( *clone, array ) );

    array__char__clear( clone, system_allocator.allocator );
    allocator__free( system_allocator.allocator, clone );
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

    REQUIRE( array__char__equals( *auto_array.array__char, expected_array ) );
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

    REQUIRE( array__char__equals( *auto_array.array__char, expected_array ) );
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
    REQUIRE( array__char__equals( *auto_array.array__char, expected_values1 ) );

    // Prepend a single value.
    auto_array__char__prepend_elements( &auto_array, 1, &values.data[ 2 ] );
    REQUIRE( array__char__equals( *auto_array.array__char, expected_values2 ) );

    // Prepend several values to a non-empty auto_array.
    auto_array__char__prepend_elements( &auto_array, 2, &values.data[ 3 ] );
    REQUIRE( array__char__equals( *auto_array.array__char, expected_values3 ) );

    // Prepend no values.
    auto_array__char__prepend_elements( &auto_array, 0, &values.data[ 0 ] );
    REQUIRE( array__char__equals( *auto_array.array__char, expected_values3 ) );

    // Prepend no values with NULL data.
    auto_array__char__prepend_elements( &auto_array, 0, NULL );
    REQUIRE( array__char__equals( *auto_array.array__char, expected_values3 ) );

    auto_array__char__clear( &auto_array );
}


TEST_CASE_METHOD( Array__TestFixture, "auto_array__char__prepend_element", "[array]" ){
    const unsigned long ELEMENT_COUNT = 10;

    char chars[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

    Array__char expected_array = {
        .data = chars,
        .length = 10,
        .capacity = 10,
        .element_size = 1
    };


    AutoArray__char auto_array;
    auto_array__char__initialize( &auto_array, system_allocator.allocator, ELEMENT_COUNT );

    unsigned long element_index;
    for( element_index = ELEMENT_COUNT; element_index > 0; element_index-- ){
        auto_array__char__prepend_element( &auto_array, chars[ element_index - 1 ] );
    }

    REQUIRE( array__char__equals( *auto_array.array__char, expected_array ) );
    auto_array__char__clear( &auto_array );
}

TEST_CASE_METHOD( Array__TestFixture, "auto_array__char__insert_elements", "[array]" ){
    char values_array[ 8 ] = { 0, 1, 2, 3, 4, 5, 6, 7 };
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

    char expected_values2_array[ 4 ] = { 0, 2, 3, 1 };
    Array__char expected_values2 = {
        .data = expected_values2_array,
        .length = ELEMENT_COUNT( expected_values2_array ),
        .capacity = ELEMENT_COUNT( expected_values2_array ),
        .element_size = sizeof( char )
    };

    char expected_values3_array[ 5 ] = { 0, 2, 3, 1, 4 };
    Array__char expected_values3 = {
        .data = expected_values3_array,
        .length = ELEMENT_COUNT( expected_values3_array ),
        .capacity = ELEMENT_COUNT( expected_values3_array ),
        .element_size = sizeof( char )
    };

    char expected_values4_array[ 6 ] = { 5, 0, 2, 3, 1, 4 };
    Array__char expected_values4 = {
        .data = expected_values4_array,
        .length = ELEMENT_COUNT( expected_values4_array ),
        .capacity = ELEMENT_COUNT( expected_values4_array ),
        .element_size = sizeof( char )
    };

    char expected_values5_array[ 12 ] = { 5, 0, 2, 3, 1, 4, 0, 0, 0, 0, 6, 7 };
    Array__char expected_values5 = {
        .data = expected_values5_array,
        .length = ELEMENT_COUNT( expected_values5_array ),
        .capacity = ELEMENT_COUNT( expected_values5_array ),
        .element_size = sizeof( char )
    };

    // Set up an auto_array.
    AutoArray__char auto_array;
    auto_array__char__initialize( &auto_array, system_allocator.allocator, 0 );

    // Insert several values at the beginning.
    auto_array__char__insert_elements( &auto_array, 0, 2, &values.data[ 0 ] );
    REQUIRE( array__char__equals( *auto_array.array__char, expected_values1 ) );

    // Insert some more part-way through.
    auto_array__char__insert_elements( &auto_array, 1, 2, &values.data[ 2 ] );
    REQUIRE( array__char__equals( *auto_array.array__char, expected_values2 ) );

    // And at the end.
    auto_array__char__insert_elements( &auto_array, auto_array.array__char->length, 1, &values.data[ 4 ] );
    REQUIRE( array__char__equals( *auto_array.array__char, expected_values3 ) );

    // Then back at the beginning again.
    auto_array__char__insert_elements( &auto_array, 0, 1, &values.data[ 5 ] );
    REQUIRE( array__char__equals( *auto_array.array__char, expected_values4 ) );

    // Insert zero elements.
    auto_array__char__insert_elements( &auto_array, 0, 0, &values.data[ 0 ] );
    REQUIRE( array__char__equals( *auto_array.array__char, expected_values4 ) );

    // Insert zero elements with a NULL pointer.
    auto_array__char__insert_elements( &auto_array, 0, 0, NULL );
    REQUIRE( array__char__equals( *auto_array.array__char, expected_values4 ) );

    // Insert some elements off the end of the auto_array.
    auto_array__char__insert_elements( &auto_array, auto_array.array__char->length + 4, 2, &values.data[ 6 ] );
    REQUIRE( array__char__equals( *auto_array.array__char, expected_values5 ) );

    auto_array__char__clear( &auto_array );
}


TEST_CASE_METHOD( Array__TestFixture, "auto_array__char__insert_element", "[array]" ){
    const unsigned long ELEMENT_COUNT = 10;

    char chars[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

    Array__char expected_array = {
        .data = chars,
        .length = 10,
        .capacity = 10,
        .element_size = 1
    };


    AutoArray__char auto_array;
    auto_array__char__initialize( &auto_array, system_allocator.allocator, ELEMENT_COUNT );

    auto_array__char__insert_element( &auto_array, 0, chars[ 0 ] );
    auto_array__char__insert_element( &auto_array, 1, chars[ 9 ] );
    auto_array__char__insert_element( &auto_array, 1, chars[ 1 ] );
    auto_array__char__insert_element( &auto_array, 2, chars[ 8 ] );
    auto_array__char__insert_element( &auto_array, 2, chars[ 2 ] );
    auto_array__char__insert_element( &auto_array, 3, chars[ 7 ] );
    auto_array__char__insert_element( &auto_array, 3, chars[ 3 ] );
    auto_array__char__insert_element( &auto_array, 4, chars[ 6 ] );
    auto_array__char__insert_element( &auto_array, 4, chars[ 4 ] );
    auto_array__char__insert_element( &auto_array, 5, chars[ 5 ] );

    REQUIRE( array__char__equals( *auto_array.array__char, expected_array ) );
    auto_array__char__clear( &auto_array );
}

TEST_CASE_METHOD( Array__TestFixture, "auto_array__char__remove_element", "[array]" ){
    AutoArray__char auto_array;
    auto_array__char__initialize( &auto_array, system_allocator.allocator, 0 );

    unsigned long element_index;
    for( element_index = 0; element_index < 100; element_index++ ){
        auto_array__char__append_element( &auto_array, element_index );
    }

    REQUIRE( auto_array.array__char->length == 100 );

    auto_array__char__remove_element( &auto_array, 57 );
    auto_array__char__remove_element( &auto_array, 21 );
    auto_array__char__remove_element( &auto_array, 3 );
    auto_array__char__remove_element( &auto_array, 1 );

    REQUIRE( auto_array.array__char->length == 96 );

    long previous_element = -1;
    long current_element;
    for( element_index = 0; element_index < auto_array.array__char->length; element_index++ ){
        current_element = auto_array.array__char->data[ element_index ];
        REQUIRE( ( current_element != 1 && current_element != 3 && current_element != 21 && current_element != 57 ) );
        REQUIRE( previous_element < current_element );
        previous_element = current_element;
    }

    auto_array__char__clear( &auto_array );
}

TEST_CASE_METHOD( Array__TestFixture, "auto_array__char__remove_index_fast", "[array]" ){
    AutoArray__char auto_array;
    auto_array__char__initialize( &auto_array, system_allocator.allocator, 0 );

    unsigned long element_index;
    for( element_index = 0; element_index < 100; element_index++ ){
        auto_array__char__append_element( &auto_array, element_index );
    }

    REQUIRE( auto_array.array__char->length == 100 );

    auto_array__char__remove_element__fast( &auto_array, 1 );
    auto_array__char__remove_element__fast( &auto_array, 3 );
    auto_array__char__remove_element__fast( &auto_array, 21 );
    auto_array__char__remove_element__fast( &auto_array, 57 );

    REQUIRE( auto_array.array__char->length == 96 );

    REQUIRE( auto_array.array__char->data[ 1 ] == 99 );
    REQUIRE( auto_array.array__char->data[ 3 ] == 98 );
    REQUIRE( auto_array.array__char->data[ 21 ] == 97 );
    REQUIRE( auto_array.array__char->data[ 57 ] == 96 );

    long previous_element = -1;
    long current_element;
    for( element_index = 0; element_index < auto_array.array__char->length; element_index++ ){
        current_element = auto_array.array__char->data[ element_index ];
        REQUIRE( ( current_element != 1 && current_element != 3 && current_element != 21 && current_element != 57 ) );
        previous_element = current_element;
    }

    auto_array__char__clear( &auto_array );
}

TEST_CASE_METHOD( Array__TestFixture, "auto_array__char__remove_range", "[array]" ){
    AutoArray__char auto_array;
    auto_array__char__initialize( &auto_array, system_allocator.allocator, 100 );

    unsigned long element_index;
    for( element_index = 0; element_index < 100; element_index++ ){
        auto_array__char__append_element( &auto_array, element_index );
    }

    REQUIRE( auto_array.array__char->length == 100 );

    auto_array__char__remove_range( &auto_array, 31, 4 );

    REQUIRE( auto_array.array__char->length == 96 );

    long previous_element = -1;
    long current_element;
    for( element_index = 0; element_index < auto_array.array__char->length; element_index++ ){
        current_element = auto_array.array__char->data[ element_index ];
        REQUIRE( ( current_element < 31 || current_element > 34 ) );
        REQUIRE( previous_element < current_element );
        previous_element = current_element;
    }

    // Ensure the entire auto_array can be cleared, even when empty.
    auto_array__char__remove_range( &auto_array, 0, auto_array.array__char->length );

    REQUIRE( auto_array.array__char->length == 0);

    auto_array__char__remove_range( &auto_array, 0, auto_array.array__char->length );

    REQUIRE( auto_array.array__char->length == 0 );

    auto_array__char__clear( &auto_array );
}
