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
 *  @} group log
 */

END_DECLARATIONS

#endif // KIRKE__STRING__H
