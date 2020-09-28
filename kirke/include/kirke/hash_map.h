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
    } TYPENAME;                                                                                                                                     \
                                                                                                                                                    \
    void METHOD_PREFIX ## __initialize( TYPENAME *hash_map, Allocator *allocator, unsigned long long bucket_count );                                \
                                                                                                                                                    \
    void METHOD_PREFIX ## __clear( TYPENAME *hash_map );                                                                                            \
                                                                                                                                                    \
    void METHOD_PREFIX ## __insert( TYPENAME* hash_map, KEY_TYPE key, VALUE_TYPE value );                                                           \
                                                                                                                                                    \
    bool METHOD_PREFIX ## __retrieve( TYPENAME *hash_map, KEY_TYPE key, VALUE_TYPE *out_value );                                                    \
                                                                                                                                                    \
    void METHOD_PREFIX ## __delete( TYPENAME * hash_map, KEY_TYPE key );

#define HASH_MAP__DEFINE( TYPENAME, METHOD_PREFIX, KEY_TYPE, VALUE_TYPE, KEY_TYPE__HASH_FUNCTION, KEY_TYPE__EQUALS_FUNCTION )                       \
                                                                                                                                                    \
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
        hash_map->allocator = allocator;                                                                                                            \
                                                                                                                                                    \
        METHOD_PREFIX ## __array__list__key_value_pair ## __initialize( &hash_map->entry_buckets, allocator, bucket_count );                        \
        METHOD_PREFIX ## __array__list__key_value_pair__clear_elements( &hash_map->entry_buckets, 0, hash_map->entry_buckets.capacity );            \
    }                                                                                                                                               \
                                                                                                                                                    \
    void METHOD_PREFIX ## __clear( TYPENAME *hash_map ){                                                                                            \
        METHOD_PREFIX ## __array__list__key_value_pair__clear( &hash_map->entry_buckets, hash_map->allocator );                                     \
        hash_map->allocator = NULL;                                                                                                                 \
    }                                                                                                                                               \
                                                                                                                                                    \
    void METHOD_PREFIX ## __insert( TYPENAME *hash_map, KEY_TYPE key, VALUE_TYPE value ){                                                           \
        unsigned long long bucket_index = KEY_TYPE__HASH_FUNCTION( &key ) % hash_map->entry_buckets.capacity;                                       \
                                                                                                                                                    \
        /* If no list of entries exists at the index, create a new list with the specified key:value and return */                                  \
        if( hash_map->entry_buckets.data[ bucket_index ] == NULL ){                                                                                 \
            hash_map->entry_buckets.data[ bucket_index ] = (TYPENAME ## __List__KeyValuePair*) allocator__alloc(                                    \
                hash_map->allocator,                                                                                                                \
                sizeof( TYPENAME ## __List__KeyValuePair )                                                                                          \
            );                                                                                                                                      \
            hash_map->entry_buckets.length += 1;                                                                                                    \
                                                                                                                                                    \
            METHOD_PREFIX ## __list__key_value_pair__initialize(                                                                                    \
                &hash_map->entry_buckets.data[ bucket_index ],                                                                                      \
                hash_map->allocator,                                                                                                                \
                (TYPENAME ## __KeyValuePair) { .key = key, .value = value }                                                                         \
            );                                                                                                                                      \
                                                                                                                                                    \
            return;                                                                                                                                 \
        }                                                                                                                                           \
                                                                                                                                                    \
        /* If an entry with this key already exists, update it to the new value and return */                                                       \
        unsigned long long index;                                                                                                                   \
        if(                                                                                                                                         \
            METHOD_PREFIX ## __list__key_value_pair__index_of(                                                                                      \
                hash_map->entry_buckets.data[ bucket_index ],                                                                                       \
                (TYPENAME ## __KeyValuePair) { .key = key, .value = value },                                                                        \
                &index                                                                                                                              \
            )                                                                                                                                       \
        ){                                                                                                                                          \
            TYPENAME ## __List__KeyValuePair *existing_entry;                                                                                       \
            METHOD_PREFIX ## __list__key_value_pair__at( hash_map->entry_buckets.data[ bucket_index ], index, &existing_entry );                    \
            existing_entry->value.value = value;                                                                                                    \
            return;                                                                                                                                 \
        }                                                                                                                                           \
                                                                                                                                                    \
        /* Entries already exist at this index, and they don't match our key. Append the specified key:value to the existing list of entries */     \
        METHOD_PREFIX ## __list__key_value_pair__append(                                                                                            \
            hash_map->entry_buckets.data[ bucket_index ],                                                                                           \
            hash_map->allocator,                                                                                                                    \
            (TYPENAME ## __KeyValuePair) { .key = key, .value = value }                                                                             \
        );                                                                                                                                          \
    }                                                                                                                                               \
                                                                                                                                                    \
    bool METHOD_PREFIX ## __retrieve( TYPENAME *hash_map, KEY_TYPE key, VALUE_TYPE *out_value ){                                                    \
        unsigned long long bucket_index = KEY_TYPE__HASH_FUNCTION( &key ) % hash_map->entry_buckets.capacity;                                       \
                                                                                                                                                    \
        TYPENAME ## __List__KeyValuePair *entry;                                                                                                    \
        if(                                                                                                                                         \
            METHOD_PREFIX ## __list__key_value_pair__where(                                                                                         \
                hash_map->entry_buckets.data[ bucket_index ],                                                                                       \
                (TYPENAME ## __KeyValuePair) { .key = key },                                                                                        \
                &entry                                                                                                                              \
            )                                                                                                                                       \
        ){                                                                                                                                          \
            *out_value = entry->value.value;                                                                                                        \
            return true;                                                                                                                            \
        }                                                                                                                                           \
                                                                                                                                                    \
        return false;                                                                                                                               \
    }                                                                                                                                               \
                                                                                                                                                    \
    void METHOD_PREFIX ## __delete( TYPENAME *hash_map, KEY_TYPE key ){                                                                             \
        unsigned long long bucket_index = KEY_TYPE__HASH_FUNCTION( &key ) % hash_map->entry_buckets.capacity;                                       \
                                                                                                                                                    \
        TYPENAME ## __List__KeyValuePair *entry;                                                                                                    \
        if(                                                                                                                                         \
            METHOD_PREFIX ## __list__key_value_pair__where(                                                                                         \
                hash_map->entry_buckets.data[ bucket_index ],                                                                                       \
                (TYPENAME ## __KeyValuePair) { .key = key },                                                                                        \
                &entry                                                                                                                              \
            )                                                                                                                                       \
        ){                                                                                                                                          \
            hash_map->entry_buckets.data[ bucket_index ] = METHOD_PREFIX ## __list__key_value_pair__delete_link( entry, hash_map->allocator );      \
        }                                                                                                                                           \
    }

#define HASH_MAP__DEFINE_DEFAULT_HASH_FUNCTION( METHOD_PREFIX, KEY_TYPE )                                                                           \
    /* djb2 string hashing algorithm */                                                                                                             \
    /* sstp://www.cse.yorku.ca/~oz/hash.ssml */                                                                                                     \
    static unsigned long long METHOD_PREFIX ## __hash__ ## KEY_TYPE( KEY_TYPE *key ){                                                               \
        unsigned long long hash = 5381;                                                                                                             \
        char* key_char = (char*) key;                                                                                                               \
                                                                                                                                                    \
        for( unsigned long long byte = 0; byte < sizeof( KEY_TYPE ); byte++ ){                                                                      \
            hash = ( ( hash << 5 ) + hash ) ^ key_char[ byte ];                                                                                     \
        }                                                                                                                                           \
                                                                                                                                                    \
        return hash;                                                                                                                                \
    }

#define HASH_MAP__DEFAULT_HASH_FUNCTION( METHOD_PREFIX, KEY_TYPE ) METHOD_PREFIX ## __hash__ ## KEY_TYPE

#define HASH_MAP__DIRECT_COMPARE( first, second ) (first) == (second)

#endif // KIRKE__HASH_MAP__H
