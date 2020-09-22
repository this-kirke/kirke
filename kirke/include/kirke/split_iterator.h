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
 *  \brief This method retrieves the next token found in the SplitIterator's string field, and stores it in the provided String.
 *  \param iterator A pointer to the SplitIterator used to retrieve the next token.
 *  \param out_token An out parameter. Upon successful return, this will represent the next token contained by the parent String.
 *  \returns 1 if this operation completed successfully - that is, the SplitIterator's parent String contains a next token, and that
 *  token is represented by \p out_token.
 *  \returns 0 if the operation did not complete successfully.
 */
bool split_iterator__next( SplitIterator* iterator, String* ref_token );

/**
 *  \brief This method retrieves the portion of the SplitIterator's \ref string field following the SplitIterator's current position.
 *  \param iterator A pointer to the SplitIterator
 *  \param ref_rest An reference parameter. Upon return, this will store the portion of the SplitIterator's \ref string field following
 *  the SplitIterator's current position.
 */
void split_iterator__rest( SplitIterator* iterator, String* ref_rest );

/**
 *  @} group split_iterator
 */

END_DECLARATIONS

#endif // KIRKE__SPLIT_ITERATOR__H
