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
