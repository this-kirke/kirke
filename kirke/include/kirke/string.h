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
 *  @} group log
 */

END_DECLARATIONS

#endif // KIRKE__STRING__H
