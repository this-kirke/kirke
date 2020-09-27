#ifndef KIRKE__LIST__H
#define KIRKE__LIST__H

// System Includes
#include <stdbool.h>

// Internal Includes
#include "kirke/macros.h"
#include "kirke/allocator.h"

BEGIN_DECLARATIONS

#define LIST__DECLARE( TYPENAME, METHOD_PREFIX, ELEMENT_TYPE )                                                                      \
    typedef struct TYPENAME TYPENAME;                                                                                               \
                                                                                                                                    \
    struct TYPENAME{                                                                                                                \
        ELEMENT_TYPE value;                                                                                                         \
        TYPENAME *next;                                                                                                             \
        TYPENAME *previous;                                                                                                         \
    };                                                                                                                              \
                                                                                                                                    \
    void METHOD_PREFIX ## __initialize( TYPENAME **list, Allocator *allocator, ELEMENT_TYPE value );                                \
                                                                                                                                    \
    void METHOD_PREFIX ## __clear( TYPENAME *list, Allocator *allocator );                                                          \
                                                                                                                                    \
    TYPENAME* METHOD_PREFIX ## __head( TYPENAME *list );                                                                            \
                                                                                                                                    \
    TYPENAME* METHOD_PREFIX ## __tail( TYPENAME *list );                                                                            \
                                                                                                                                    \
    bool METHOD_PREFIX ## __at( TYPENAME *list, unsigned long long position, TYPENAME **ref_list_pointer );                         \
                                                                                                                                    \
    void METHOD_PREFIX ## __append( TYPENAME *list, Allocator *allocator, ELEMENT_TYPE value );                                     \
                                                                                                                                    \
    TYPENAME *METHOD_PREFIX ## __prepend( TYPENAME *list, Allocator *allocator, ELEMENT_TYPE value );                               \
                                                                                                                                    \
    TYPENAME *METHOD_PREFIX ## __insert_before( TYPENAME *link, Allocator *allocator, ELEMENT_TYPE value );                         \

#define LIST__DEFINE( TYPENAME, METHOD_PREFIX, ELEMENT_TYPE )                                                                       \
                                                                                                                                    \
    void METHOD_PREFIX ## __initialize( TYPENAME **list, Allocator *allocator, ELEMENT_TYPE value ){                                \
        /* Cast for C++ compatibility */                                                                                            \
        *list = (TYPENAME *) allocator__alloc( allocator, sizeof( TYPENAME ) );                                                     \
        **list = (TYPENAME) {                                                                                                       \
            .value = value,                                                                                                         \
            .next = NULL,                                                                                                           \
            .previous = NULL                                                                                                        \
        };                                                                                                                          \
    }                                                                                                                               \
                                                                                                                                    \
    void METHOD_PREFIX ## __clear( TYPENAME *list, Allocator *allocator ){                                                          \
        TYPENAME *current = METHOD_PREFIX ## __head( list );                                                                        \
        while( current != NULL ){                                                                                                   \
            TYPENAME *head = current;                                                                                               \
            current = current->next;                                                                                                \
            allocator__free( allocator, head );                                                                                     \
        }                                                                                                                           \
    }                                                                                                                               \
                                                                                                                                    \
    TYPENAME *METHOD_PREFIX ## __head( TYPENAME *list ){                                                                            \
        if( list != NULL ){                                                                                                         \
            while( list->previous != NULL ){                                                                                        \
                list = list->previous;                                                                                              \
            }                                                                                                                       \
        }                                                                                                                           \
                                                                                                                                    \
        return list;                                                                                                                \
    }                                                                                                                               \
                                                                                                                                    \
    TYPENAME* METHOD_PREFIX ## __tail( TYPENAME *list ){                                                                            \
    if( list != NULL ){                                                                                                             \
            while( list->next != NULL ){                                                                                            \
                list = list->next;                                                                                                  \
            }                                                                                                                       \
        }                                                                                                                           \
                                                                                                                                    \
        return list;                                                                                                                \
    }                                                                                                                               \
                                                                                                                                    \
    bool METHOD_PREFIX ## __at( TYPENAME *list, unsigned long long position, TYPENAME **ref_list_pointer ){                         \
        TYPENAME *current = METHOD_PREFIX ## __head( list );                                                                        \
                                                                                                                                    \
        for( unsigned long long list_index = 0; list_index < position; list_index++ ){                                              \
            if( current->next == NULL ){                                                                                            \
                return false;                                                                                                       \
            }                                                                                                                       \
                                                                                                                                    \
            current = current->next;                                                                                                \
        }                                                                                                                           \
                                                                                                                                    \
        *ref_list_pointer = current;                                                                                                \
                                                                                                                                    \
        return true;                                                                                                                \
    }                                                                                                                               \
                                                                                                                                    \
    void METHOD_PREFIX ## __append( TYPENAME *list, Allocator *allocator, ELEMENT_TYPE value ){                                     \
        TYPENAME *tail = METHOD_PREFIX ## __tail( list );                                                                           \
                                                                                                                                    \
        /* Cast for C++ compatibility */                                                                                            \
        TYPENAME *new_list = (TYPENAME *) allocator__alloc( allocator, sizeof( TYPENAME ) );                                        \
        *new_list = (TYPENAME){                                                                                                     \
            .value = value,                                                                                                         \
            .next = NULL,                                                                                                           \
            .previous = tail                                                                                                        \
        };                                                                                                                          \
                                                                                                                                    \
        tail->next = new_list;                                                                                                      \
    }                                                                                                                               \
                                                                                                                                    \
    TYPENAME *METHOD_PREFIX ## __prepend( TYPENAME *list, Allocator *allocator, ELEMENT_TYPE value ){                               \
        TYPENAME *head = METHOD_PREFIX ## __head( list );                                                                           \
                                                                                                                                    \
        /* Cast for C++ compatibility */                                                                                            \
        TYPENAME *new_list = (TYPENAME *) allocator__alloc( allocator, sizeof( TYPENAME ) );                                        \
                                                                                                                                    \
        *new_list = (TYPENAME){                                                                                                     \
            .value = value,                                                                                                         \
            .next = head,                                                                                                           \
            .previous = NULL,                                                                                                       \
        };                                                                                                                          \
        head->previous = new_list;                                                                                                  \
                                                                                                                                    \
        return new_list;                                                                                                            \
    }                                                                                                                               \
                                                                                                                                    \
    TYPENAME *METHOD_PREFIX ## __insert_before( TYPENAME *link, Allocator *allocator, ELEMENT_TYPE value ){                         \
        (void)( link );                                                                                                             \
        (void)( allocator );                                                                                                        \
        (void)( value );                                                                                                            \
                                                                                                                                    \
        return NULL;                                                                                                                \
    }                                                                                                                               \
                                                                                                                                    \

END_DECLARATIONS

#endif // KIRKE__LIST__H
