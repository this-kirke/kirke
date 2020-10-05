/**
 *  \file kirke/io.h
 */

#ifndef KIRKE__IO__H
#define KIRKE__IO__H

// System Includes
#include <stdbool.h>

// Internal Includes
#include "kirke/macros.h"

BEGIN_DECLARATIONS

/** Forward declaration of Allocator, defined in \ref kirke/allocator.h */
typedef struct Allocator Allocator;

/** Forward declaration of Error, defined in \ref kirke/error.h */
typedef struct Error Error;

/** Forward declaration of String, defined in \ref kirke/string.h */
typedef struct String String;

/**
 *  \defgroup io IO
 *  @{
 */

/**
 *  \brief This enumerator defines possible Error types for IO functions.
 */
typedef enum IO__Error {
    /** \brief Denotes that an error occurred because the specified file could not be found. */
    IO__Error__UnableToOpenFile = 1
} IO__Error;

/**
 *  \brief This method reads the contents of the file located at \p file_path into a newly-allocated Slice.
 *  \param allocator A pointer to the Allocator which will be used to allocate memory controlled by the returned Slice.
 *  \param file_path A pointer to a String containing the path of the file to be read.
 *  \param out__string An out parameter. Upon successful completion, this will store the contents read from the input file.
 *  \param error Optional. The address of a pointer to an Error structure, which will be non-NULL upon return if an error is
 *  encountered while attempting to read the specified file.
 *  \returns Returns true if the operation completed successfully. This operation can fail if there is a problem opening the
 *  specified file.
 *  \returns Returns false if the operation did not complete successfully.
 */
bool io__read_text_file( Allocator* allocator, String file_path, String* out__string, Error* error );

/**
 *  \brief This method reads the contents of stdin into a newly-allocated String.
 *  \param allocator A pointer to the Allocator which will be used to allocate memory for the returned String.
 *  \returns A pointer to a newly-allocated String containing the contents of stdin.
 */
String* io__read_stdin( Allocator* allocator );

/**
 *  @} group io
 */

END_DECLARATIONS

#endif // KIRKE__IO__H
