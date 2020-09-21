// System Includes
#include <stdarg.h> // va_list, va_start, va_end
#include <stdio.h>  // snprintf, vsnprintf
#include <string.h> // strncmp

// Internal Includes
#include "kirke/error.h"
#include "kirke/log.h"

void error__set( Error *error, const char* type, unsigned long long code, const char* format, ... ){
    (void)( error );
    (void)( type );
    (void)( code );
    (void)( format );
}

bool error__equals( Error* first, Error* second ){
    if(
        strncmp( first->type, second->type, sizeof( first->type ) ) == 0 &&
        first->code == second->code
    ){
        return 1;
    }

    return 0;
}
