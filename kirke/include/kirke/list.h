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
    TYPENAME* METHOD_PREFIX ## __head( TYPENAME *list );                                                                            \
                                                                                                                                    \
    TYPENAME* METHOD_PREFIX ## __tail( TYPENAME *list );

#define LIST__DEFINE( TYPENAME, METHOD_PREFIX, ELEMENT_TYPE )                                                                       \
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
    }

END_DECLARATIONS

#endif // KIRKE__LIST__H
