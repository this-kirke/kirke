#ifndef KIRKE__HASH_MAP__H
#define KIRKE__HASH_MAP__H

// System Includes
#include <stdbool.h>

// Internal Includes
#include "kirke/macros.h"
#include "kirke/list.h"
#include "kirke/string.h"

#define HASH_MAP__DECLARE( TYPENAME, METHOD_PREFIX, KEY_TYPE, VALUE_TYPE )                                                                          \
                                                                                                                                                    \
    typedef struct TYPENAME ## __KeyValuePair {                                                                                                     \
        KEY_TYPE key;                                                                                                                               \
        VALUE_TYPE value;                                                                                                                           \
    } TYPENAME ## __KeyValuePair;                                                                                                                   \
                                                                                                                                                    \
    LIST__DECLARE( TYPENAME ## __List__KeyValuePair, METHOD_PREFIX ## __list__key_value_pair, TYPENAME ## __KeyValuePair )                          \
    ARRAY__DECLARE( TYPENAME ## __Array__List__KeyValuePair, METHOD_PREFIX ## __array__list__key_value_pair, TYPENAME ## __List__KeyValuePair * )   \
                                                                                                                                                    \
    typedef struct TYPENAME {                                                                                                                       \
        Allocator *allocator;                                                                                                                       \
        TYPENAME ## __Array__List__KeyValuePair entry_buckets;                                                                                      \
    } HashMap;                                                                                                                                      \
                                                                                                                                                    \
    void METHOD_PREFIX ## __initialize( TYPENAME *hash_map, Allocator *allocator, unsigned long long bucket_count );                                \
                                                                                                                                                    \
    void METHOD_PREFIX ## __clear( TYPENAME *hash_map );                                                                                            \


#define HASH_MAP__DEFINE( TYPENAME, METHOD_PREFIX, KEY_TYPE, VALUE_TYPE, KEY_TYPE__EQUALS_FUNCTION )                                                \
    bool METHOD_PREFIX ## __key_value_pair__keys_are_equal( TYPENAME ## __KeyValuePair first, TYPENAME ## __KeyValuePair second ){                  \
        if( KEY_TYPE__EQUALS_FUNCTION( first.key, second.key ) ){                                                                                   \
            return true;                                                                                                                            \
        }                                                                                                                                           \
        return false;                                                                                                                               \
    }                                                                                                                                               \
                                                                                                                                                    \
    LIST__DEFINE(                                                                                                                                   \
        TYPENAME ## __List__KeyValuePair,                                                                                                           \
        METHOD_PREFIX ## __list__key_value_pair,                                                                                                    \
        TYPENAME ## __KeyValuePair,                                                                                                                 \
        METHOD_PREFIX ## __key_value_pair__keys_are_equal                                                                                           \
    )                                                                                                                                               \
                                                                                                                                                    \
    ARRAY__DEFINE(                                                                                                                                  \
        TYPENAME ## __Array__List__KeyValuePair,                                                                                                    \
        METHOD_PREFIX ## __array__list__key_value_pair,                                                                                             \
        TYPENAME ## __List__KeyValuePair *,                                                                                                         \
        METHOD_PREFIX ## __list__key_value_pair__equals                                                                                             \
    )                                                                                                                                               \
                                                                                                                                                    \
    void METHOD_PREFIX ## __initialize( TYPENAME *hash_map, Allocator *allocator, unsigned long long bucket_count ){                                \
        (void)( hash_map );                                                                                                                         \
        (void)( allocator );                                                                                                                        \
        (void)( bucket_count );                                                                                                                     \
    }                                                                                                                                               \
                                                                                                                                                    \
    void METHOD_PREFIX ## __clear( HashMap *hash_map ){                                                                                             \
        (void)( hash_map );                                                                                                                         \
    }                                                                                                                                               \

#endif // KIRKE__HASH_MAP__H
