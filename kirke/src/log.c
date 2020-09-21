// System Includes
#include <time.h>

// Internal Includes
#include "kirke/log.h"

static Log__Level KIRKE__LOG__LEVEL = Log__Level__Warning;

void log__set_log_level( Log__Level level ){
    if( level >= Log__Level__Verbose && level < Log__Level__COUNT ){
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

static const char *log_level_colors[] = {
    "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"
};

void log__log( Log__Level level, const char* file, int line, const char* format, ... ){
    if( level < KIRKE__LOG__LEVEL || level >= Log__Level__COUNT ){
        return;
    }

    time_t now = time( NULL );
    struct tm *local_time = localtime( &now );

    char time_buffer[ 16 ];
    time_buffer[ strftime( time_buffer, sizeof( time_buffer ), "%H:%M:%S", local_time ) ] = '\0';

    fprintf(
        stderr,
        "[%s%7s]:\t\x1b[0m%s\t%s%-5s\x1b[0m %s:%d:\x1b[0m\t",
        log_level_colors[ level ],
        log__level__to_string( level ),
        time_buffer,
        log_level_colors[ level ],
        log_level_colors[ level ],
        file,
        line
    );

    va_list args;
    va_start( args, format );
    vfprintf( stderr, format, args );
    va_end( args );

    fprintf( stderr, "\n" );
}
