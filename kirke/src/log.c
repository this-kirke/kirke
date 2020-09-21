// Internal Includes
#include "kirke/log.h"

static Log__Level KIRKE__LOG__LEVEL = Log__Level__Warning;

void log__set_log_level( Log__Level level ){
    if( level >= Log__Level__Verbose && level <= Log__Level__Error ){
        KIRKE__LOG__LEVEL = level;
    }
}

Log__Level log__get_log_level(){
    return KIRKE__LOG__LEVEL;
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
