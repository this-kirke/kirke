// Internal Includes
#include "kirke/split_iterator.h"

void split_iterator__initialize( SplitIterator* iterator, String const *string, String const *delimiter ){
    iterator->string = string;
    iterator->delimiter = delimiter;
    iterator->position = 0;
}

unsigned long long split_iterator__count( SplitIterator const *iterator ){
    SplitIterator copy = {
        .string = iterator->string,
        .delimiter = iterator->delimiter,
        .position = 0
    };

    unsigned long long count = 0;

    String string;
    while( split_iterator__next( &copy, &string ) ){
        count++;
    }

    return count;
}

bool split_iterator__next( SplitIterator* iterator, String* out__token ){
    if( iterator->position >= iterator->string->length ){
        return false;
    }

    /*
     * The do {} while( out_token->length == 0 ); prevents returning 0-length tokens, in case
     * one delimiter directly follows another.
     */
    do{
        split_iterator__rest( iterator, out__token );

        if( string__index_of( out__token, iterator->delimiter, &out__token->length ) ){
            iterator->position += out__token->length + iterator->delimiter->length;
        }
        else{
            iterator->position += out__token->length;
        }
    } while( out__token->length == 0 && iterator->position < iterator->string->length );

    if( out__token->length == 0 ){
        return false;
    }

    return true;
}

void split_iterator__rest( SplitIterator* iterator, String* ref_rest ){
    *ref_rest = (String){
        .data = iterator->string->data + iterator->position,
        .length = iterator->string->length - iterator->position,
        .capacity = iterator->string->length - iterator->position,
        .element_size = sizeof( char )
    };
}
