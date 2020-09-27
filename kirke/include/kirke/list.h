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
    bool METHOD_PREFIX ## __equals( TYPENAME const *first, TYPENAME const *second );                                                \
                                                                                                                                    \
    TYPENAME* METHOD_PREFIX ## __head( TYPENAME const *list );                                                                      \
                                                                                                                                    \
    TYPENAME* METHOD_PREFIX ## __tail( TYPENAME const *list );                                                                      \
                                                                                                                                    \
    unsigned long long METHOD_PREFIX ## __length( TYPENAME const *list );                                                           \
                                                                                                                                    \
    bool METHOD_PREFIX ## __where( TYPENAME *list, ELEMENT_TYPE value, TYPENAME **ref_list_pointer );                               \
                                                                                                                                    \
    bool METHOD_PREFIX ## __index_of( TYPENAME *list, ELEMENT_TYPE value, unsigned long long *out_index );                          \
                                                                                                                                    \
    bool METHOD_PREFIX ## __at( TYPENAME *list, unsigned long long position, TYPENAME **ref_list_pointer );                         \
                                                                                                                                    \
    unsigned long long METHOD_PREFIX ## __position_of( TYPENAME *link );                                                            \
                                                                                                                                    \
    void METHOD_PREFIX ## __for_each( TYPENAME *list, void( *function )( ELEMENT_TYPE *value, void *user_data ), void *user_data ); \
                                                                                                                                    \
    void METHOD_PREFIX ## __append( TYPENAME *list, Allocator *allocator, ELEMENT_TYPE value );                                     \
                                                                                                                                    \
    TYPENAME *METHOD_PREFIX ## __prepend( TYPENAME *list, Allocator *allocator, ELEMENT_TYPE value );                               \
                                                                                                                                    \
    TYPENAME *METHOD_PREFIX ## __insert_before( TYPENAME *link, Allocator *allocator, ELEMENT_TYPE value );                         \
                                                                                                                                    \
    void METHOD_PREFIX ## __insert_after( TYPENAME *link, Allocator *allocator, ELEMENT_TYPE value );                               \
                                                                                                                                    \
    void METHOD_PREFIX ## __concatenate( TYPENAME *first, TYPENAME *second );                                                       \
                                                                                                                                    \
    TYPENAME *METHOD_PREFIX ## __delete_link( TYPENAME *link, Allocator *allocator );                                               \
                                                                                                                                    \
    TYPENAME *METHOD_PREFIX ## __delete_first( TYPENAME *link, ELEMENT_TYPE value, Allocator *allocator );                          \
                                                                                                                                    \
    TYPENAME *METHOD_PREFIX ## __delete_all( TYPENAME *link, ELEMENT_TYPE value, Allocator *allocator );                            \

#define LIST__DEFINE( TYPENAME, METHOD_PREFIX, ELEMENT_TYPE, ELEMENT_TYPE__EQUALS_FUNCTION )                                        \
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
    bool METHOD_PREFIX ## __equals( TYPENAME const *first, TYPENAME const *second ){                                                \
        (void)( first );                                                                                                            \
        (void)( second );                                                                                                           \
                                                                                                                                    \
        return false;                                                                                                               \
    }                                                                                                                               \
                                                                                                                                    \
    TYPENAME *METHOD_PREFIX ## __head( TYPENAME const *list ){                                                                      \
        if( list != NULL ){                                                                                                         \
            while( list->previous != NULL ){                                                                                        \
                list = list->previous;                                                                                              \
            }                                                                                                                       \
        }                                                                                                                           \
                                                                                                                                    \
        return (TYPENAME *) list;                                                                                                   \
    }                                                                                                                               \
                                                                                                                                    \
    TYPENAME *METHOD_PREFIX ## __tail( TYPENAME const *list ){                                                                      \
        if( list != NULL ){                                                                                                         \
            while( list->next != NULL ){                                                                                            \
                list = list->next;                                                                                                  \
            }                                                                                                                       \
        }                                                                                                                           \
                                                                                                                                    \
        return (TYPENAME *) list;                                                                                                   \
    }                                                                                                                               \
                                                                                                                                    \
    unsigned long long METHOD_PREFIX ## __length( TYPENAME const *list ){                                                           \
        TYPENAME *current = METHOD_PREFIX ## __head( list );                                                                        \
                                                                                                                                    \
        unsigned long long length = 0;                                                                                              \
        while( current != NULL ){                                                                                                   \
            current = current->next;                                                                                                \
            length++;                                                                                                               \
        }                                                                                                                           \
                                                                                                                                    \
        return length;                                                                                                              \
    }                                                                                                                               \
                                                                                                                                    \
    bool METHOD_PREFIX ## __where( TYPENAME *list, ELEMENT_TYPE value, TYPENAME **ref_list_pointer ){                               \
        TYPENAME *current = METHOD_PREFIX ## __head( list );                                                                        \
                                                                                                                                    \
        while( current != NULL ){                                                                                                   \
            if( ELEMENT_TYPE__EQUALS_FUNCTION( &current->value, &value ) ){                                                         \
                *ref_list_pointer = current;                                                                                        \
                return true;                                                                                                        \
            }                                                                                                                       \
            current = current->next;                                                                                                \
        }                                                                                                                           \
                                                                                                                                    \
        return false;                                                                                                               \
    }                                                                                                                               \
                                                                                                                                    \
    bool METHOD_PREFIX ## __index_of( TYPENAME *list, ELEMENT_TYPE value, unsigned long long *out_index ){                          \
        TYPENAME *current = METHOD_PREFIX ## __head( list );                                                                        \
                                                                                                                                    \
        unsigned long long index = 0;                                                                                               \
        while( current != NULL ){                                                                                                   \
            if( ELEMENT_TYPE__EQUALS_FUNCTION( &current->value, &value ) ){                                                         \
                *out_index = index;                                                                                                 \
                return true;                                                                                                        \
            }                                                                                                                       \
            current = current->next;                                                                                                \
            index++;                                                                                                                \
        }                                                                                                                           \
                                                                                                                                    \
        return false;                                                                                                               \
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
    unsigned long long METHOD_PREFIX ## __position_of( TYPENAME *link ){                                                            \
        TYPENAME *current = METHOD_PREFIX ## __head( link );                                                                        \
                                                                                                                                    \
        unsigned long long position = 0;                                                                                            \
        while( current != link ){                                                                                                   \
            current = current->next;                                                                                                \
            position++;                                                                                                             \
        }                                                                                                                           \
                                                                                                                                    \
        return position;                                                                                                            \
    }                                                                                                                               \
                                                                                                                                    \
    void METHOD_PREFIX ## __for_each( TYPENAME *list, void( *function )( ELEMENT_TYPE *value, void *user_data ), void *user_data ){ \
        TYPENAME *current = METHOD_PREFIX ## __head( list );                                                                        \
                                                                                                                                    \
        while( current != NULL ){                                                                                                   \
            function( &current->value, user_data );                                                                                 \
            current = current->next;                                                                                                \
        }                                                                                                                           \
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
    void METHOD_PREFIX ## __concatenate( TYPENAME *first, TYPENAME *second ){                                                       \
        TYPENAME *first_tail = METHOD_PREFIX ## __tail( first );                                                                    \
        TYPENAME *second_head = METHOD_PREFIX ## __head( second );                                                                  \
                                                                                                                                    \
        first_tail->next = second_head;                                                                                             \
        second_head->previous = first_tail;                                                                                         \
    }                                                                                                                               \
                                                                                                                                    \
    TYPENAME *METHOD_PREFIX ## __delete_link( TYPENAME *link, Allocator *allocator ){                                               \
        TYPENAME *head = METHOD_PREFIX ## __head( link );                                                                           \
        if( head == link ){                                                                                                         \
            link->next->previous = NULL;                                                                                            \
            head = link->next;                                                                                                      \
        }                                                                                                                           \
        else{                                                                                                                       \
            link->previous->next = link->next;                                                                                      \
        }                                                                                                                           \
                                                                                                                                    \
        if( link->next != NULL ){                                                                                                   \
            link->next->previous = link->previous;                                                                                  \
        }                                                                                                                           \
                                                                                                                                    \
        allocator__free( allocator, link );                                                                                         \
                                                                                                                                    \
        return head;                                                                                                                \
    }                                                                                                                               \
                                                                                                                                    \
    TYPENAME *METHOD_PREFIX ## __delete_first( TYPENAME *link, ELEMENT_TYPE value, Allocator *allocator ){                          \
        TYPENAME *head = METHOD_PREFIX ## __head( link );                                                                           \
                                                                                                                                    \
        TYPENAME *current = head;                                                                                                   \
        while( current != NULL ){                                                                                                   \
            if( ELEMENT_TYPE__EQUALS_FUNCTION( &current->value, &value ) ){                                                         \
                return METHOD_PREFIX ## __delete_link( current, allocator );                                                        \
            }                                                                                                                       \
            current = current->next;                                                                                                \
        }                                                                                                                           \
                                                                                                                                    \
        return NULL;                                                                                                                \
    }                                                                                                                               \
                                                                                                                                    \
    TYPENAME *METHOD_PREFIX ## __delete_all( TYPENAME *link, ELEMENT_TYPE value, Allocator *allocator ){                            \
        TYPENAME *head = METHOD_PREFIX ## __head( link );                                                                           \
                                                                                                                                    \
        TYPENAME *current = head;                                                                                                   \
        while( current != NULL ){                                                                                                   \
            if( ELEMENT_TYPE__EQUALS_FUNCTION( &current->value, &value ) ){                                                         \
                current = current->next;                                                                                            \
                head = METHOD_PREFIX ## __delete_link( current->previous, allocator );                                              \
            }                                                                                                                       \
            else{                                                                                                                   \
                current = current->next;                                                                                            \
            }                                                                                                                       \
        }                                                                                                                           \
                                                                                                                                    \
        return head;                                                                                                                \
    }

END_DECLARATIONS

#endif // KIRKE__LIST__H
