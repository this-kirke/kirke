/**
 *  \file kirke/log.h
 */

#ifndef KIRKE__LOG__H
#define KIRKE__LOG__H

// System Includes
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// Internal Includes
#include "kirke/macros.h"

/**
 *  \defgroup log Log
 *  @{
 */

BEGIN_DECLARATIONS

/**
 * \brief An enumerator type describing the severity of a log message.
 */
typedef enum Log__Level {
    /**
     *  Denotes the lowest-severity log level.
     */
    Log__Level__Verbose,
    /**
     *  Denotes a log level intended for debug messages.
     */
    Log__Level__Debug,
    /**
     *  Denotes a log level appropriate for providing informational messages to end users.
     */
    Log__Level__Info,
    /**
     *  Denotes a log level appropriate for providing warning messages.
     */
    Log__Level__Warning,
    /**
     *  Denotes the highest-severity log level, appropriate for reporting error conditions encountered.
     */
    Log__Level__Error,
        /**
     * The total number of defined log levels.
     * \note This is not a valid direction.
     */
    Log__Level__COUNT
} Log__Level;


/**
 *  \def log__verbose
 *  \brief Convenience macro to log a message with Log__Level__Verbose severity.
 *  \note Contents of __VA_ARGS__ parameter should be a C-style string with format specifiers, followed by a
 *  list of variables corresponding to the format specifiers in the string.
 */
#define log__verbose( ... ) log__log( Log__Level__Verbose, __FILE__, __LINE__, __VA_ARGS__ )

/**
 *  \def log__debug
 *  \brief Convenience macro to log a message with Log__Level__Debug severity.
 *  \note Contents of __VA_ARGS__ parameter should be a C-style string with format specifiers, followed by a
 *  list of variables corresponding to the format specifiers in the string.
 */
#define log__debug( ... ) log__log( Log__Level__Debug, __FILE__, __LINE__, __VA_ARGS__ )

/**
 *  \def log__info
 *  \brief Convenience macro to log a message with Log__Level__Info severity.
 *  \note Contents of __VA_ARGS__ parameter should be a C-style string with format specifiers, followed by a
 *  list of variables corresponding to the format specifiers in the string.
 */
#define log__info( ... )  log__log( Log__Level__Info,  __FILE__, __LINE__, __VA_ARGS__ )

/**
 *  \def log__warning
 *  \brief Convenience macro to log a message with Log__Level__Warning severity.
 *  \note Contents of __VA_ARGS__ parameter should be a C-style string with format specifiers, followed by a
 *  list of variables corresponding to the format specifiers in the string.
 */
#define log__warning( ... )  log__log( Log__Level__Warning,  __FILE__, __LINE__, __VA_ARGS__ )

/**
 *  \def log__error
 *  \brief Convenience macro to log a message with Log__Level__Error severity.
 *  \note Contents of __VA_ARGS__ parameter should be a C-style string with format specifiers, followed by a
 *  list of variables corresponding to the format specifiers in the string.
 */
#define log__error( ... ) log__log( Log__Level__Error, __FILE__, __LINE__, __VA_ARGS__ )

/**
 *  \brief This method returns the currently-set log level.
 *  \returns The currently-set log level.
 */
Log__Level log__get_log_level();

/**
 *  \brief This method sets the current log level. Any messages lower than the currently-set log level will
 *  not be logged.
 *  \param level The level at which the logger will be set.
 */
void log__set_log_level( Log__Level level );

/**
 *  \brief This method converts a Log__Level enumerator value into a C-style string.
 *  \param log_level The log level which is to be converted.
 *  \returns A stack-allocated, const char* const containing a NULL-terminated C-style string representation of
 *  the name of \p log_level.
 */
char* log__level__to_string( Log__Level level );

/**
 *  \brief This method logs a message to stdout.
 *  \param level The severity level of the message to be logged.
 *  \param file A string representing the absolute path to the file which called this method. The macros log__*
 *  automatically fill this parameter with the current __FILE__ macro definition.
 *  \param line An integer representing the source code line at which this method was called. The macros log__*
 *  automatically fill this parameter with the current __LINE__ macro definition.
 *  \param format A C-style string, optionally containing format specifiers, followed by a list of variables
 *  corresponding to the format specifiers that exist in the string.
 */
void log__log( Log__Level level, const char *file, int line, const char *format, ... );

/**
 *  @} group log
 */

END_DECLARATIONS

#endif // KIRKE__LOG__H
