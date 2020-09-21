// Internal Includes
#include "kirke/log.h"

void log__set_log_level( Log__Level level ){
    (void)( level );
}

Log__Level log__get_log_level(){
    return 0;
}

char* log__level__to_string( Log__Level log_level ){
    switch( log_level ){
        case Log__Level__Verbose:
            return "Verbose";
        case Log__Level__Debug:
            return "Debug";
        case Log__Level__Info:
            return "Info";
        case Log__Level__Warning:
            return "Warning";
        case Log__Level__Error:
            return "Error";
        default:
            return "INVALID";
    }
}
