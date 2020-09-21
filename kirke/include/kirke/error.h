/**
 *  \file kirke/error.h
 */

#ifndef KIRKE__ERROR__H
#define KIRKE__ERROR__H

// System Includes
#include <stdbool.h>

// Internal Includes
#include "kirke/macros.h"

BEGIN_DECLARATIONS

/**
 *  \defgroup error Error
 *  @{
 */

/**
 *  Generally, we consider three types of errors:  Machine errors, Programming errors, and User errors
 *
 *  Machine errors occur when the hardware is incapable of handling some operation. The most common
 *  example of this is out of memory errors.  A typical response to these is to panic and exit, but we leave
 *  the decision of how to handle this situation to the user. For example, the user is notfieid of an out of
 *  memory error by allocator->out_of_memory().
 *
 *  Programming errors should notify the developer that something is incorrect. We handle these with log
 *  messages, as in log__warning() or log__error().
 *
 *  User errors are only detectable at runtime, and include issues such as improper input - file not found,
 *  or invalid formatting, for example.  The proper way to handle these is to notify the user, and gracefully
 *  exit the program.
 *
 *  Handling user errors is the purpose of the Error structure.
 *
 *  The type field is the broad category of error which was encountered. This is generally the name of the
 *  class which defines and throws the error.
 *
 *  The code field is an integral identifier for the specific error encountered
 *
 *  The message field allows the developer to provide a detailed message describing the error and relevant
 *  conditions of the error when encountered
 */

/**
 *  \brief A structure which represents a recoverable runtime error which was encountered.
 */
typedef struct Error{
    /**
     *  A null-terminated C-style string of characters describing the error's broad type
     */
    char type[ 32 ];
    /**
     *  An identifier for this error, unique within its type.
     */
    unsigned long code;
    /**
     *  A null-terminated C-style string of characters which describes the specific error condition
     */
    char message[ 256 ];
} Error;

/**
 *  \brief This method sets the type, code and message of an Error structure.
 *  \param error A pointer to an Error structure. Upon completion, this will store the specified type,
 *  code and message.
 *  \param type A null-terminated C-style string which describes the general type of the message, such
 *  as the class in which the error originated.
 *  \param code An identifier for this particular error, unique within its type.
 *  \param format A format specifier with string replacement tokens, in the style of printf, which are
 *  used for creating the message
 *  field.
 */
void error__set( Error *error, const char* type, unsigned long long code, const char* format, ... );

/**
 *  \brief This method compares two Error structures for equality.
 *  \param first A pointer to the first error to be compared.
 *  \param second A pointer to the second error to be compared.
 *  \returns 1 if the two Error structures contain the same type and code, and 0 otherwise.
 */
bool error__equals( Error* first, Error* second );

/**
 *  @} group error
 */

END_DECLARATIONS

#endif // KIRKE__ERROR__H
