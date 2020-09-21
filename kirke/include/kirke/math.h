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
 *  \brief This method compares the provided values, and returns the lesser or the two.
 *  \param first The first value to be compared.
 *  \param second The second value to be compared.
 */
unsigned long math__min__ulong( unsigned long first, unsigned long second );

/**
 *  \brief This method compares the provided values, and returns the greater or the two.
 *  \param first The first value to be compared.
 *  \param second The second value to be compared.
 */
unsigned long math__max__ulong( unsigned long first, unsigned long second );

/**
 *  \brief This method compares the provided values, and returns the lesser or the two.
 *  \param first The first value to be compared.
 *  \param second The second value to be compared.
 */
unsigned long long math__min__ullong( unsigned long long first, unsigned long long second );

/**
 *  \brief This method compares the provided values, and returns the greater or the two.
 *  \param first The first value to be compared.
 *  \param second The second value to be compared.
 */
unsigned long long math__max__ullong( unsigned long long first, unsigned long long second );

/**
 *  @} group math
 */

END_DECLARATIONS

#endif // KIRKE__MATH__H
