// System Includes
#include <stdio.h> // vsnprintf

// Internal Includes
#include "kirke/string.h"

static bool chars_are_equal( const char *first, const char *second ){
    if( *first == *second ){
        return true;
    }

    return false;
}

ARRAY__DEFINE( String, string, char, chars_are_equal )
ARRAY__DEFINE( Array__String, array__string, String, string__equals )

void string__initialize__va_list( String* string, Allocator* allocator, const char* format, va_list args ){
    char c;
    va_list args_copy;
    va_copy( args_copy, args );
    int required_capacity = vsnprintf( &c, 1, format, args_copy ) + 1;

    string__initialize( string, allocator, required_capacity );
    string->length = vsnprintf( string->data, required_capacity, format, args );
}
