/**
 *  \file kirke/split_iterator.h
 */

#ifndef KIRKE__SPLIT_ITERATOR__H
#define KIRKE__SPLIT_ITERATOR__H

// Standard Includes
#include <stdbool.h>

// Internal Includes
#include "kirke/macros.h"
#include "kirke/string.h"

BEGIN_DECLARATIONS

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
    String const *string;
    /**
     *  A pointer to a String which represents the delimiter used to split tokens from the parent String.
     */
    String const *delimiter;
    /**
     *  The current position of the iterator, in elements. This is incremented by split_iterator__next to reference
     *  to the element following the last-found delimiter.
     */
    unsigned long long position;
} SplitIterator;

/**
 *  \brief This method initializes a SplitIterator structure, storing a reference to the specified String and
 *  delimiter, and setting the SplitIterator's position to 0.
 *  \param iterator A pointer to the SplitIterator to be initialized.
 *  \param string The parent String, which will be split into tokens separated by the specified delimiter
 *  \param delimiter A String which will be used to separate \p string into tokens.
 */
void split_iterator__initialize( SplitIterator* iterator, String const *string, String const *delimiter );

/**
 *  \brief This method counts the total number of tokens which will be returned by split_iterator__next. This is useful
 *  for determining the number of tokens while not having to handle each of them individually.
 *  \param iterator A pointer to an initialized iterator, for which the number of tokens will be calculated.
 *  \returns the number of tokens which exist in iterator->string, separated by iterator->delimiter.  The number of tokens
 *  is equal to the number of occurrences of the delimiter sequence + 1.
 */
unsigned long long split_iterator__count( SplitIterator const *iterator );

/**
 *  \brief This method retrieves the next token found in the SplitIterator's string field, and stores it in the provided String.
 *  \param iterator A pointer to the SplitIterator used to retrieve the next token.
 *  \param out_token An out parameter. Upon successful return, this will represent the next token contained by the parent String.
 *  \returns Returns true if this operation completed successfully. This method can fail if there are no remaining tokens in the
 *  parent string.
 *  \returns Returns false if the operation did not complete successfully.
 */
bool split_iterator__next( SplitIterator *iterator, String *out__token );

/**
 *  \brief This method retrieves the portion of the SplitIterator's \ref string field following the SplitIterator's current position.
 *  \param iterator A pointer to the SplitIterator
 *  \param out__rest An out parameter. Upon return, this will store the portion of the SplitIterator's \ref string field following
 *  the SplitIterator's current position.
 */
void split_iterator__rest( SplitIterator *iterator, String *out__rest );

/**
 *  @} group split_iterator
 */

END_DECLARATIONS

#endif // KIRKE__SPLIT_ITERATOR__H
