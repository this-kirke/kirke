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
 *  \brief This method converts a Log__Level enumerator value into a C-style string.
 *  \param log_level The log level which is to be converted.
 *  \returns A stack-allocated, const char* const containing a NULL-terminated C-style string representation of
 *  the name of \p log_level.
 */
char* log__level__to_string( Log__Level log_level );

/**
 *  @} group log
 */

END_DECLARATIONS

#endif // KIRKE__LOG__H
