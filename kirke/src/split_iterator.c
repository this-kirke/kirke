// Internal Includes
#include "kirke/split_iterator.h"
#include "kirke/string.h"

void split_iterator__initialize( SplitIterator* iterator, const String* string_, const String* delimiter ){
    iterator->string = string_;
    iterator->delimiter = delimiter;
    iterator->position = 0;
}

void split_iterator__rest( SplitIterator* iterator, String* ref_rest ){
    *ref_rest = (String){
        .data = iterator->string->data + iterator->position,
        .length = iterator->string->length - iterator->position,
        .capacity = iterator->string->length - iterator->position,
        .element_size = sizeof( char )
    };
}
