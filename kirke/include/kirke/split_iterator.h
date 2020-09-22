/**
 *  \file kirke/split_iterator.h
 */

#ifndef KIRKE__SPLIT_ITERATOR__H
#define KIRKE__SPLIT_ITERATOR__H

// Standard Includes
#include <stdbool.h>

// Internal Includes
#include "kirke/macros.h"

BEGIN_DECLARATIONS

typedef struct String String;

/**
 *  \defgroup split_iterator SplitIterator
 *  @{
 */

/**
 *  \brief This is a type which captures state for a split iterator. A split iterator splits a String into
 *  component Strings - tokens - which are separated by a delimiter. Delimiters themselves are Strings, and
 *  can be multiple elements long.
 */
typedef struct SplitIterator{
    /**
     *  A pointer to the parent String, containing both tokens and delimiters
     */
    const String* string;
    /**
     *  A pointer to a String which represents the delimiter used to split tokens from the parent String.
     */
    const String* delimiter;
    /**
     *  The current position of the iterator, in elements. This is incremented by split_iterator__next to reference
     *  to the element following the last-found delimiter.
     */
    unsigned long position;
} SplitIterator;

/**
 *  \brief This method initializes a SplitIterator structure, storing a reference to the specified String and
 *  delimiter, and setting the SplitIterator's position to 0.
 *  \param iterator A pointer to the SplitIterator to be initialized.
 *  \param string A parent to the parent String, which will be split into tokens separated by the specified delimiter
 *  \param delimiter A String containing a sequence of elements which will be used to separate \p string into tokens.
 */
void split_iterator__initialize( SplitIterator* iterator, const String* string, const String* delimiter );

/**
 *  @} group split_iterator
 */

END_DECLARATIONS

#endif // KIRKE__SPLIT_ITERATOR__H
