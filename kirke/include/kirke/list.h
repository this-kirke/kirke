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
                                                                                                                                    \
    void METHOD_PREFIX ## __insert_after( TYPENAME *link, Allocator *allocator, ELEMENT_TYPE value );                               \
                                                                                                                                    \
    unsigned long long METHOD_PREFIX ## __length( TYPENAME *list );                                                                 \
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
    unsigned long long METHOD_PREFIX ## __length( TYPENAME *list ){                                                                 \
        (void)( list );                                                                                                             \
        return 0;                                                                                                                   \
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
        TYPENAME *head = METHOD_PREFIX ## __head( link );                                                                           \
                                                                                                                                    \
        if( link == head ){                                                                                                         \
            head = METHOD_PREFIX ## __prepend( head, allocator, value );                                                            \
        }                                                                                                                           \
        else{                                                                                                                       \
            /* Cast for C++ compatibility */                                                                                        \
            TYPENAME *new_link = (TYPENAME *) allocator__alloc( allocator, sizeof( TYPENAME ) );                                    \
            *new_link = (TYPENAME){                                                                                                 \
                .value = value,                                                                                                     \
                .next = link,                                                                                                       \
                .previous = link->previous                                                                                          \
            };                                                                                                                      \
                                                                                                                                    \
            link->previous->next = new_link;                                                                                        \
            link->previous = new_link;                                                                                              \
        }                                                                                                                           \
                                                                                                                                    \
        return head;                                                                                                                \
    }                                                                                                                               \
                                                                                                                                    \
    void METHOD_PREFIX ## __insert_after( TYPENAME *link, Allocator *allocator, ELEMENT_TYPE value ){                               \
        /* Cast for C++ compatibility */                                                                                            \
        TYPENAME *new_link = (TYPENAME *) allocator__alloc( allocator, sizeof( TYPENAME ) );                                        \
        *new_link = (TYPENAME){                                                                                                     \
            .value = value,                                                                                                         \
            .next = link->next,                                                                                                     \
            .previous = link                                                                                                        \
        };                                                                                                                          \
                                                                                                                                    \
        link->next->previous = new_link;                                                                                            \
        link->next = new_link;                                                                                                      \
    }                                                                                                                               \
                                                                                                                                    \

END_DECLARATIONS

#endif // KIRKE__LIST__H
