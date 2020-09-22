// Internal Includes
#include "kirke/split_iterator.h"
#include "kirke/string.h"

void split_iterator__initialize( SplitIterator* iterator, const String* string_, const String* delimiter ){
    iterator->string = string_;
    iterator->delimiter = delimiter;
    iterator->position = 0;
}
