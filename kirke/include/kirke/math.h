/**
 *  \file kirke/math.h
 */

#ifndef KIRKE__MATH__H
#define KIRKE__MATH__H

// Internal Includes
#include "kirke/macros.h"

/**
 *  \defgroup math Math
 *  @{
 */

BEGIN_DECLARATIONS

/**
 *  \brief This method compares the provided values, and returns the lesser or the two.
 *  \param first The first value to be compared.
 *  \param second The second value to be compared.
 */
long math__min__long( long first, long second );

/**
 *  \brief This method compares the provided values, and returns the greater or the two.
 *  \param first The first value to be compared.
 *  \param second The second value to be compared.
 */
long math__max__long( long first, long second );

/**
 *  @} group math
 */

END_DECLARATIONS

#endif // KIRKE__MATH__H
