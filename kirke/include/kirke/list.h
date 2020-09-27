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
    void METHOD_PREFIX ## __append( TYPENAME *list, Allocator *allocator, ELEMENT_TYPE value );                                     \
                                                                                                                                    \

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
    void METHOD_PREFIX ## __append( TYPENAME *list, Allocator *allocator, ELEMENT_TYPE value ){                                     \
        (void)( list );                                                                                                             \
        (void)( allocator );                                                                                                        \
        (void)( value );                                                                                                            \
    }                                                                                                                               \
                                                                                                                                    \
END_DECLARATIONS

#endif // KIRKE__LIST__H
