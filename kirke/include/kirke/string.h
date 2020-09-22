/**
 *  \file kirke/string.h
 */

#ifndef KIRKE__STRING__H
#define KIRKE__STRING__H

// Internal Includes
#include "kirke/macros.h"
#include "kirke/array.h"

BEGIN_DECLARATIONS

/**
 *  \defgroup string String
 *  @{
 */

ARRAY__DECLARE( String, string, char )
ARRAY__DECLARE( Array__String, array__string, String )

/**
 *  \def string__literal( TEXT )
 *  \brief This macro defines a String object containing the specified text.
 *  \param TEXT A pointer to the an array of characters which will be contained by the defined String.
 */
#define string__literal( TEXT ){        \
        .data = (char*) TEXT,           \
        .length = sizeof( TEXT ) - 1,   \
        .capacity = sizeof( TEXT ),     \
        .element_size = sizeof( char )  \
    }

/**
 *  \brief This method initializes a String using the provided format and variable arguments list. The provided Allocator is
 *  used to allocate new memory.
 *  \param string A pointer to the String which will be initialized.
 *  \param allocator The allocator which will be used to manage memory controlled by the provided String.
 *  \param format A null-terminated (C-style) string of characters, with optional format specifiers. Format specifiers
 *  are the same as those used for printf.
 *  \param args If format specifiers are contained within \p format, then this parameter must contain the arguments which
 *  correspond to each specifier used.
 */
void string__initialize__va_list( String* string, Allocator* allocator, const char* format, va_list args );

/**
 *  \brief This method initializes a String using the provided format and specifiers. The provided Allocator is
 *  used to allocate new memory.
 *  \param string A pointer to the String which will be initialized.
 *  \param allocator The allocator which will be used to manage memory controlled by the provided String.
 *  \param format A null-terminated (C-style) string of characters, with optional format specifiers. Format specifiers
 *  are the same as those used for printf. If format specifiers are contained within \p format, then this parameter
 *  must be followed by a variable argument list of the corresponding variables.
 */
void string__initialize__format( String* string, Allocator* allocator, const char* format, ... );

/**
 *  \brief This method appends a formatted C-Style string to the end of a String.
 *  \param string A pointer to the String to which the format string will be appended.
 *  \param allocator The allocator used to allocate memory for \p string, which will also be used to expand
 *  this memory if necessary.
 *  \param format A null-terminated (C-style) string of characters, with optional format specifiers. Format specifiers
 *  are the same as those used for printf.
 *  \param args If format specifiers are contained within \p format, then this parameter must contain the arguments which
 *  correspond to each specifier used.
 */
void string__append__va_list( String *string, Allocator *allocator, const char* format, va_list args );

/**
 *  @} group string
 */

END_DECLARATIONS

#endif // KIRKE__STRING__H
