// System Includes
#include <stdarg.h> // va_list, va_start, va_end
#include <stdio.h>  // snprintf, vsnprintf
#include <string.h> // strncmp

// Internal Includes
#include "kirke/error.h"
#include "kirke/log.h"
bool error__equals( Error* first, Error* second ){
    (void)( first );
    (void)( second );

    return false;
}
