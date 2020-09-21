// System Includes
#include <stdarg.h> // va_list, va_start, va_end
#include <stdio.h>  // snprintf, vsnprintf
#include <string.h> // strncmp

// Internal Includes
#include "kirke/error.h"
#include "kirke/log.h"

void error__set( Error *error, const char* type, unsigned long long code, const char* format, ... ){
    RETURN_IF_FAIL( error != NULL );

    if( error->code != Error__None ){
        log__warning( "error__set:  Overwriting existing destination error.  Destination should be cleared with error__reset before calling error__set." );
        return;
    }

    snprintf( error->type, sizeof( error->type ), "%s", type );
    error->code = code;

    va_list args;
    va_start( args, format );

    vsnprintf( error->message, sizeof( error->message ), format, args );
    va_end( args );
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
