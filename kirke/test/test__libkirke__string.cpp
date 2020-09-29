// 3rdParty Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "kirke/string.h"
#include "kirke/system_allocator.h"

TEST_CASE( "string__literal__string", "[string]" ){
    char string_literal[] = "This is a string.";

    String string = string__literal( string_literal );

    REQUIRE( string.data == string_literal );
    REQUIRE( string.length == sizeof( string_literal ) - 1 );
    REQUIRE( string.capacity == sizeof( string_literal ) );
    REQUIRE( string.element_size == sizeof( char ) );
}

TEST_CASE( "string__literal__inline", "[string]" ){
    const char string_literal[] = "This is a string.";
    String string = string__literal( "This is a string." );

    REQUIRE( strcmp( string.data, string_literal ) == 0 );
    REQUIRE( string.length == sizeof( string_literal ) - 1 );
    REQUIRE( string.capacity == sizeof( string_literal ) );
    REQUIRE( string.element_size == sizeof( char ) );
}

TEST_CASE( "string__equals", "[string]" ){
    String first = string__literal( "String 1" );
    String second = string__literal( "String 2" );

    REQUIRE( string__equals( first, first ) == true );
    REQUIRE( string__equals( first, second ) == false );
}

TEST_CASE( "string__clear_elements", "[string]" ){
    char STRING[ 18 ] = "This is a string.";

    String string = string__literal( STRING );

    REQUIRE( string.capacity == 18 );
    REQUIRE( string.length == 17 );

    string__clear_elements( &string, 4, 2 );

    REQUIRE( string.capacity == 18 );
    REQUIRE( string.length == 17 );

    REQUIRE( string.data[ 4 ] == '\0' );
    REQUIRE( string.data[ 5 ] == '\0' );
}

TEST_CASE( "string__index_of", "[string]" ){
    String string = string__literal( "Hello, World!" );
    String sequence = string__literal( "Wo" );

    unsigned long long index;
    REQUIRE( string__index_of( &string, &sequence, &index ) );
    REQUIRE( index == 7 );
}

class String__TestFixture{
    protected:
        String__TestFixture(){
            system_allocator__initialize( &system_allocator, NULL );
        }

        ~String__TestFixture(){
            system_allocator__deinitialize( &system_allocator );
        }

        SystemAllocator system_allocator;
};

TEST_CASE_METHOD( String__TestFixture, "string__initialize_and_clear", "[string]" ){
    String string;
    string__initialize( &string, system_allocator.allocator, 10 );

    REQUIRE( string.data != NULL );
    REQUIRE( string.capacity == 10 );

    string__clear( &string, system_allocator.allocator );

    REQUIRE( string.data == NULL );
    REQUIRE( string.length == 0 );
    REQUIRE( string.capacity == 0 );
    REQUIRE( string.element_size == 1 );
}

TEST_CASE_METHOD( String__TestFixture, "string__initialize__full_and_clear", "[string]" ){
    const char STRING[] = "This is a string.";
    String expected_string = string__literal( STRING );

    String string;
    string__initialize__full( &string, system_allocator.allocator, STRING, 17, 18 );

    REQUIRE( string__equals( string, expected_string ) );

    string__clear( &string, system_allocator.allocator );
}

TEST_CASE_METHOD( String__TestFixture, "string__clone", "[string]" ){
    String string = string__literal( "This is a string." );
    String *clone = string__clone( &string, system_allocator.allocator );

    REQUIRE( string__equals( *clone, string ) );

    string__clear( clone, system_allocator.allocator );
    allocator__free( system_allocator.allocator, clone );
}

TEST_CASE_METHOD( String__TestFixture, "auto_string__initialize_and_clear", "[string]" ){
    AutoString auto_string = {0};
    auto_string__initialize( &auto_string, system_allocator.allocator, 15 );

    REQUIRE( auto_string.string->data != NULL );
    REQUIRE( auto_string.string->length == 0 );
    REQUIRE( auto_string.string->capacity == 15 );
    REQUIRE( auto_string.string->element_size == sizeof( char ) );
    REQUIRE( auto_string.allocator == system_allocator.allocator );

    auto_string__clear( &auto_string );

    REQUIRE( auto_string.string == NULL );
    REQUIRE( auto_string.allocator == NULL );
}

TEST_CASE_METHOD( String__TestFixture, "auto_string__append_elements", "[string]" ){
    const char STRING[] = "This is a string.";

    String expected_string = string__literal( STRING );

    AutoString auto_string;
    auto_string__initialize( &auto_string, system_allocator.allocator, 17 );

    auto_string__append_elements( &auto_string, 17, STRING );

    REQUIRE( string__equals( *auto_string.string, expected_string ) );
}

TEST_CASE_METHOD( String__TestFixture, "auto_string__append_element", "[string]" ){
    char STRING[] = "This is a string.";

    String expected_string = string__literal( STRING );

    AutoString auto_string;
    auto_string__initialize( &auto_string, system_allocator.allocator, 17 );

    for( size_t element_index = 0; element_index < sizeof( STRING ) - 1; element_index++ ){
        auto_string__append_element( &auto_string, STRING[ element_index ] );
    }

    REQUIRE( string__equals( *auto_string.string, expected_string ) );
}

TEST_CASE_METHOD( String__TestFixture, "auto_string__prepend_elements", "[string]" ){
    String values = string__literal( "Hello" );
    String expected_values1 = string__literal( "He" );
    String expected_values2 = string__literal( "lHe" );
    String expected_values3 = string__literal( "lolHe" );

    AutoString auto_string;
    auto_string__initialize( &auto_string, system_allocator.allocator, 0 );

    // Prepend several values to an empty auto_string.
    auto_string__prepend_elements( &auto_string, 2, &values.data[ 0 ] );
    REQUIRE( string__equals( *auto_string.string, expected_values1 ) );

    // Prepend a single value.
    auto_string__prepend_elements( &auto_string, 1, &values.data[ 2 ] );
    REQUIRE( string__equals( *auto_string.string, expected_values2 ) );

    // Prepend several values to a non-empty auto_string.
    auto_string__prepend_elements( &auto_string, 2, &values.data[ 3 ] );
    REQUIRE( string__equals( *auto_string.string, expected_values3 ) );

    // Prepend no values.
    auto_string__prepend_elements( &auto_string, 0, &values.data[ 0 ] );
    REQUIRE( string__equals( *auto_string.string, expected_values3 ) );

    // Prepend no values with NULL data.
    auto_string__prepend_elements( &auto_string, 0, NULL );
    REQUIRE( string__equals( *auto_string.string, expected_values3 ) );

    auto_string__clear( &auto_string );
}

TEST_CASE_METHOD( String__TestFixture, "auto_string__prepend_element", "[string]" ){
    const char STRING[] = "Hello World!";
    String expected_string = string__literal( STRING );

    AutoString auto_string;
    auto_string__initialize( &auto_string, system_allocator.allocator, sizeof( STRING ) );

    unsigned long long element_index;
    for( element_index = sizeof( STRING ) - 1; element_index > 0; element_index-- ){
        auto_string__prepend_element( &auto_string, STRING[ element_index - 1 ] );
    }

    REQUIRE( string__equals( *auto_string.string, expected_string ) );
    auto_string__clear( &auto_string );
}

TEST_CASE_METHOD( String__TestFixture, "auto_string__insert_elements", "[string]" ){
    String values = string__literal( "Hello World!" );
    String expected_values1 = string__literal( "He" );
    String expected_values2 = string__literal( "Hlle" );
    String expected_values3 = string__literal( "Hlleo" );
    String expected_values4 = string__literal( " Hlleo" );
    String expected_values5 = string__literal( " Hlleo\0\0\0\0Wo" );

    // Set up an auto_string.
    AutoString auto_string;
    auto_string__initialize( &auto_string, system_allocator.allocator, 0 );

    // Insert several values at the beginning.
    auto_string__insert_elements( &auto_string, 0, 2, &values.data[ 0 ] );
    REQUIRE( string__equals( *auto_string.string, expected_values1 ) );

    // Insert some more part-way through.
    auto_string__insert_elements( &auto_string, 1, 2, &values.data[ 2 ] );
    REQUIRE( string__equals( *auto_string.string, expected_values2 ) );

    // And at the end.
    auto_string__insert_elements( &auto_string, auto_string.string->length, 1, &values.data[ 4 ] );
    REQUIRE( string__equals( *auto_string.string, expected_values3 ) );

    // Then back at the beginning again.
    auto_string__insert_elements( &auto_string, 0, 1, &values.data[ 5 ] );
    REQUIRE( string__equals( *auto_string.string, expected_values4 ) );

    // Insert zero elements.
    auto_string__insert_elements( &auto_string, 0, 0, &values.data[ 0 ] );
    REQUIRE( string__equals( *auto_string.string, expected_values4 ) );

    // Insert zero elements with a NULL pointer.
    auto_string__insert_elements( &auto_string, 0, 0, NULL );
    REQUIRE( string__equals( *auto_string.string, expected_values4 ) );

    // Insert some elements off the end of the auto_string.
    auto_string__insert_elements( &auto_string, auto_string.string->length + 4, 2, &values.data[ 6 ] );
    REQUIRE( string__equals( *auto_string.string, expected_values5 ) );

    auto_string__clear( &auto_string );
}

TEST_CASE_METHOD( String__TestFixture, "auto_string__insert_element", "[string]" ){
    char STRING[] = "Hello Mom!";

    String expected_string = string__literal( STRING );

    AutoString auto_string;
    auto_string__initialize( &auto_string, system_allocator.allocator, expected_string.length );

    auto_string__insert_element( &auto_string, 0, STRING[ 0 ] );
    auto_string__insert_element( &auto_string, 1, STRING[ 9 ] );
    auto_string__insert_element( &auto_string, 1, STRING[ 1 ] );
    auto_string__insert_element( &auto_string, 2, STRING[ 8 ] );
    auto_string__insert_element( &auto_string, 2, STRING[ 2 ] );
    auto_string__insert_element( &auto_string, 3, STRING[ 7 ] );
    auto_string__insert_element( &auto_string, 3, STRING[ 3 ] );
    auto_string__insert_element( &auto_string, 4, STRING[ 6 ] );
    auto_string__insert_element( &auto_string, 4, STRING[ 4 ] );
    auto_string__insert_element( &auto_string, 5, STRING[ 5 ] );

    REQUIRE( string__equals( *auto_string.string, expected_string ) );
    auto_string__clear( &auto_string );
}

TEST_CASE_METHOD( String__TestFixture, "auto_string__remove_element", "[string]" ){
    AutoString auto_string;
    auto_string__initialize( &auto_string, system_allocator.allocator, 0 );

    char element_index;
    for( element_index = 0; element_index < 100; element_index++ ){
        auto_string__append_element( &auto_string, element_index );
    }

    REQUIRE( auto_string.string->length == 100 );

    auto_string__remove_element( &auto_string, 57 );
    auto_string__remove_element( &auto_string, 21 );
    auto_string__remove_element( &auto_string, 3 );
    auto_string__remove_element( &auto_string, 1 );

    REQUIRE( auto_string.string->length == 96 );

    long previous_element = -1;
    long current_element;
    for( element_index = 0; element_index < auto_string.string->length; element_index++ ){
        current_element = auto_string.string->data[ element_index ];
        REQUIRE( ( current_element != 1 && current_element != 3 && current_element != 21 && current_element != 57 ) );
        REQUIRE( previous_element < current_element );
        previous_element = current_element;
    }

    auto_string__clear( &auto_string );
}

TEST_CASE_METHOD( String__TestFixture, "auto_string__remove_index_fast", "[string]" ){
    AutoString auto_string;
    auto_string__initialize( &auto_string, system_allocator.allocator, 0 );

    char element_index;
    for( element_index = 0; element_index < 100; element_index++ ){
        auto_string__append_element( &auto_string, element_index );
    }

    REQUIRE( auto_string.string->length == 100 );

    auto_string__remove_element__fast( &auto_string, 1 );
    auto_string__remove_element__fast( &auto_string, 3 );
    auto_string__remove_element__fast( &auto_string, 21 );
    auto_string__remove_element__fast( &auto_string, 57 );

    REQUIRE( auto_string.string->length == 96 );

    REQUIRE( auto_string.string->data[ 1 ] == 99 );
    REQUIRE( auto_string.string->data[ 3 ] == 98 );
    REQUIRE( auto_string.string->data[ 21 ] == 97 );
    REQUIRE( auto_string.string->data[ 57 ] == 96 );

    long previous_element = -1;
    long current_element;
    for( element_index = 0; element_index < auto_string.string->length; element_index++ ){
        current_element = auto_string.string->data[ element_index ];
        REQUIRE( ( current_element != 1 && current_element != 3 && current_element != 21 && current_element != 57 ) );
        previous_element = current_element;
    }

    auto_string__clear( &auto_string );
}

TEST_CASE_METHOD( String__TestFixture, "auto_string__remove_range", "[string]" ){
    AutoString auto_string;
    auto_string__initialize( &auto_string, system_allocator.allocator, 100 );

    char element_index;
    for( element_index = 0; element_index < 100; element_index++ ){
        auto_string__append_element( &auto_string, element_index );
    }

    REQUIRE( auto_string.string->length == 100 );

    auto_string__remove_range( &auto_string, 31, 4 );

    REQUIRE( auto_string.string->length == 96 );

    char previous_element = -1;
    char current_element;
    for( element_index = 0; element_index < auto_string.string->length; element_index++ ){
        current_element = auto_string.string->data[ element_index ];
        REQUIRE( ( current_element < 31 || current_element > 34 ) );
        REQUIRE( previous_element < current_element );
        previous_element = current_element;
    }

    // Ensure the entire auto_string can be cleared, even when empty.
    auto_string__remove_range( &auto_string, 0, auto_string.string->length );

    REQUIRE( auto_string.string->length == 0);

    auto_string__remove_range( &auto_string, 0, auto_string.string->length );

    REQUIRE( auto_string.string->length == 0 );

    auto_string__clear( &auto_string );
}

void string__initialize__va_list__helper( String* string, Allocator* allocator, const char* format, ... ){
    va_list args;
    va_start( args, format );

    string__initialize__va_list( string, allocator, format, args );

    va_end( args );
}

TEST_CASE_METHOD( String__TestFixture, "string__initialize__va_list", "[string]" ){
    String expected_string = string__literal( "This is a test." );

    String string;
    string__initialize__va_list__helper( &string, system_allocator.allocator, "This is a %s.", "test" );

    REQUIRE( string__equals( string, expected_string ) );

    string__clear( &string, system_allocator.allocator );
}

TEST_CASE_METHOD( String__TestFixture, "string__initialize__format", "[string]" ){
    String expected_string = string__literal( "This is a test." );

    String string;
    string__initialize__format( &string, system_allocator.allocator, "This is a %s.", "test" );

    REQUIRE( string__equals( string, expected_string ) );

    string__clear( &string, system_allocator.allocator );
}

void string__append__va_list__helper( String* string, Allocator* allocator, const char* format, ... ){
    va_list args;
    va_start( args, format );

    string__append__va_list( string, allocator, format, args );

    va_end( args );
}

TEST_CASE_METHOD( String__TestFixture, "string__append__va_list", "[string]" ){
    char STRING[] = "Hello";

    String expected_string = string__literal( "HelloHello" );

    String string;
    string__initialize( &string, system_allocator.allocator, 0 );

    string__append__va_list__helper( &string, system_allocator.allocator, "%s", STRING );
    string__append__va_list__helper( &string, system_allocator.allocator, "%s", STRING );

    REQUIRE( string__equals( string, expected_string ) );
}

TEST_CASE_METHOD( String__TestFixture, "string__append__format", "[string]" ){
    char STRING[] = "Hello";

    String expected_string = string__literal( "HelloHello" );

    String string;
    string__initialize( &string, system_allocator.allocator, 0 );

    string__append__format( &string, system_allocator.allocator, "%s", STRING );
    string__append__format( &string, system_allocator.allocator, "%s", STRING );

    REQUIRE( string__equals( string, expected_string ) );
}
