// Internal Includes
#include "kirke/split_iterator.h"
#include "kirke/string.h"

void split_iterator__initialize( SplitIterator* iterator, const String* string_, const String* delimiter ){
    iterator->string = string_;
    iterator->delimiter = delimiter;
    iterator->position = 0;
}

unsigned long long split_iterator__count( SplitIterator const *iterator ){
    (void)( iterator );
    return 0;
}

bool split_iterator__next( SplitIterator* iterator, String* out_token ){
    if( iterator->position >= iterator->string->length ){
        return false;
    }

    /*
     * The do {} while( out_token->length == 0 ); prevents returning 0-length tokens, in case
     * one delimiter directly follows another.
     */
    do{
        split_iterator__rest( iterator, out_token );

        if( string__index_of( out_token, iterator->delimiter, &out_token->length ) ){
            iterator->position += out_token->length + iterator->delimiter->length;
        }
        else{
            iterator->position += out_token->length;
        }
    } while( out_token->length == 0 );


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
