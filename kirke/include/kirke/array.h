/**
 *  \file kirke/array.h
 */

#ifndef KIRKE__ARRAY__H
#define KIRKE__ARRAY__H

// System Includes
#include <string.h> // memcmp, memcpy, memset
#include <stdbool.h>

// Internal Includes
#include "kirke/allocator.h"
#include "kirke/log.h"
#include "kirke/math.h"

/**
 *  \defgroup array Array
 *  @{
 */

/**
 *  Array is a container class, representing a collection of objects of the same type. Array itself is not a
 *  a type; it is only defined as a pair of macros, ARRAY__DECLARE and ARRAY__DEFINE, which actually define
 *  the desired type. Arrays are only intended to store mutable data types. Declaring an array of 'const char'
 *  will not compile, because many of the methods defined here modify the underlying elements.
 */

/**
 *  \def ARRAY__DECLARE( TYPENAME, TYPENAME_LOWERCASE, ELEMENT_TYPE )
 *  \brief Declares a structure and interface methods for a Array type. This macro should be paired
 *  with a call to the macro ARRAY__DEFINE( TYPENAME, TYPENAME_LOWERCASE, ELEMENT_TYPE ), which defines the
 *  implementations of interface methods declared herein.
 *  \param TYPENAME The name which will be assigned to the structure type.
 *  \param TYPENAME_LOWERCASE Same as TYPENAME, only lowercase. This will be used to prefix interface methods,
 *  as well as to name local variables and parameters for the interface methods.
 *  \param ELEMENT_TYPE The type which will be stored in the array.
 */
#define ARRAY__DECLARE( TYPENAME, TYPENAME_LOWERCASE, ELEMENT_TYPE )                                                                                                        \
    /*                                                                                                                                                                      \
     *  A structure which wraps an array of like types, tracking allocated capacity and length.                                                                             \
     */                                                                                                                                                                     \
    typedef struct TYPENAME {                                                                                                                                               \
        /**                                                                                                                                                                 \
         * A pointer to the memory region containing elements contained by the array.                                                                                       \
         */                                                                                                                                                                 \
        ELEMENT_TYPE *data;                                                                                                                                                 \
        /**                                                                                                                                                                 \
         * The actual length of the array, in elements                                                                                                                      \
         */                                                                                                                                                                 \
        unsigned long long length;                                                                                                                                          \
        /**                                                                                                                                                                 \
         * The allocated capacity of the array, in elements.                                                                                                                \
         */                                                                                                                                                                 \
        unsigned long long capacity;                                                                                                                                        \
        /**                                                                                                                                                                 \
         *  The size a single element stored in the array.                                                                                                                  \
         */                                                                                                                                                                 \
        unsigned long long element_size;                                                                                                                                    \
    } TYPENAME;                                                                                                                                                             \
                                                                                                                                                                            \
    /**                                                                                                                                                                     \
     *  \brief Fully initialize a TYPENAME with allocated memory.                                                                                                           \
     *  \param TYPENAME_LOWERCASE A pointer to the TYPENAME which will be initialized.                                                                                      \
     *  \param allocator A pointer to the Allocator which will be used to initialize memory owned by                                                                        \
     *  \p TYPENAME_LOWERCASE.                                                                                                                                              \
     *  \param capacity The desired capacity of the array, in elements.                                                                                                     \
     */                                                                                                                                                                     \
    void TYPENAME_LOWERCASE ## __initialize(                                                                                                                                \
        TYPENAME *TYPENAME_LOWERCASE,                                                                                                                                       \
        Allocator *allocator,                                                                                                                                               \
        unsigned long long capacity                                                                                                                                         \
    );                                                                                                                                                                      \
                                                                                                                                                                            \
    /**                                                                                                                                                                     \
     *  \brief This method fully initializes a TYPENAME with the given data                                                                                                 \
     *  \param TYPENAME_LOWERCASE A pointer to the TYPENAME which will be initialized.                                                                                      \
     *  \param allocator A pointer to the Allocator which will be used to initialize memory owned by                                                                        \
     *  \p TYPENAME_LOWERCASE.                                                                                                                                              \
     *  \param data A pointer to the memory region containing the elements which will be contained by                                                                       \
     *  \p TYPENAME_LOWERCASE. Elements to be copied and \p data will not be modified. Managing the memory                                                                  \
     *  allocated for \p data is the caller's responsibility.                                                                                                               \
     *  \param length The length, in elements of \p data.                                                                                                                   \
     */                                                                                                                                                                     \
    void TYPENAME_LOWERCASE ## __initialize__full(                                                                                                                          \
        TYPENAME *TYPENAME_LOWERCASE,                                                                                                                                       \
        Allocator* allocator,                                                                                                                                               \
        ELEMENT_TYPE const *data,                                                                                                                                           \
        unsigned long long length,                                                                                                                                          \
        unsigned long long capacity                                                                                                                                         \
    );                                                                                                                                                                      \
                                                                                                                                                                            \
    /**                                                                                                                                                                     \
     *  \brief Frees the memory allocated for the array, without freeing the array structure itself.                                                                        \
     *  \param TYPENAME_LOWERCASE The array whose memory is to be cleared                                                                                                   \
     *  \param allocator The allocator which was used to allocate the array's data. This must also be used                                                                  \
     *  to free the array's data.                                                                                                                                           \
     *  \note This method will free the array's 'data' field. However, if the array contains pointers to                                                                    \
     *  dynamically-allocated structures, then those must be freed prior to calling this method, or you                                                                     \
     *  may lose your reference to those pointers and leak memory.                                                                                                          \
     */                                                                                                                                                                     \
    void TYPENAME_LOWERCASE ## __clear(                                                                                                                                     \
        TYPENAME *TYPENAME_LOWERCASE,                                                                                                                                       \
        Allocator *allocator                                                                                                                                                \
    );                                                                                                                                                                      \
                                                                                                                                                                            \
    /**                                                                                                                                                                     \
     *  \brief Compares two array structures for equality.                                                                                                                  \
     *  \param first The first array to be compared.                                                                                                                        \
     *  \param second The second array to be compared.                                                                                                                      \
     *  \returns Returns true if both array structures are equal - that is, they have the same element size, length,                                                        \
     *  and if they contain the same elements. Capacity is not compared.                                                                                                    \
     *  \returns Returns false if both TYPENAME structures are not equal.                                                                                                   \
     */                                                                                                                                                                     \
    bool TYPENAME_LOWERCASE ## __equals(                                                                                                                                    \
        TYPENAME const *first,                                                                                                                                              \
        TYPENAME const *second                                                                                                                                              \
    );                                                                                                                                                                      \

/**
 *  \def ARRAY__DEFINE( TYPENAME, TYPENAME_LOWERCASE, ELEMENT_TYPE )
 *  \brief Defines interface methods for a Array type. This macro must be paired with a call to the macro
 *  ARRAY__DECLARE( TYPENAME, TYPENAME_LOWERCASE, ELEMENT_TYPE ).
 *  \param TYPENAME The name which will was assigned to the structure type.
 *  \param TYPENAME_LOWERCASE Same as TYPENAME, only lowercase. This will be used to prefix interface methods,
 *  as well as to name local variables and parameters for the interface methods.
 *  \param ELEMENT_TYPE The type which will be stored in the array.
 *  \param ELEMENT_TYPE__EQUALS_FUNCTION A function which will compare two ELEMENT_TYPEs, returning 1 if they
 *  are equal, and 0 otherwise. The signature should be bool METHOD_NAME( const *ELEMENT_TYPE, const *ELEMENT_TYPE ).
 *  This is used to implement the method bool TYPENAME_LOWERCASE ## __equals. The Array metaclass has no means of
 *  knowing what type of elements are contained within - they could be integral types, user-defined structures,
 *  or pointers to either. Users may also have different ideas about how these types should be compared for
 *  equality, as in address vs. field by field comparison. Allowing the user to supply an arbitrary equality
 *  comparison function yields the most utility and flexibility.
 */
#define ARRAY__DEFINE( TYPENAME, TYPENAME_LOWERCASE, ELEMENT_TYPE, ELEMENT_TYPE__EQUALS_FUNCTION )                                                                          \
                                                                                                                                                                            \
    void TYPENAME_LOWERCASE ## __initialize(                                                                                                                                \
        TYPENAME *TYPENAME_LOWERCASE,                                                                                                                                       \
        Allocator* allocator,                                                                                                                                               \
        unsigned long long capacity                                                                                                                                         \
    ){                                                                                                                                                                      \
        *TYPENAME_LOWERCASE = (TYPENAME){                                                                                                                                   \
            /* Cast for C++ compatibility */                                                                                                                                \
            .data = (ELEMENT_TYPE*) allocator__alloc( allocator, capacity * sizeof( ELEMENT_TYPE ) ),                                                                       \
            .length = 0,                                                                                                                                                    \
            .capacity = capacity,                                                                                                                                           \
            .element_size = sizeof( ELEMENT_TYPE )                                                                                                                          \
        };                                                                                                                                                                  \
    }                                                                                                                                                                       \
                                                                                                                                                                            \
    void TYPENAME_LOWERCASE ## __initialize__full(                                                                                                                          \
        TYPENAME *TYPENAME_LOWERCASE,                                                                                                                                       \
        Allocator* allocator,                                                                                                                                               \
        ELEMENT_TYPE const *data,                                                                                                                                           \
        unsigned long long length,                                                                                                                                          \
        unsigned long long capacity                                                                                                                                         \
    ){                                                                                                                                                                      \
        *TYPENAME_LOWERCASE = (TYPENAME) {                                                                                                                                  \
            /* Cast for C++ compatibility */                                                                                                                                \
            .data = (ELEMENT_TYPE*) allocator__alloc( allocator, length * sizeof( ELEMENT_TYPE ) ),                                                                         \
            .length = length,                                                                                                                                               \
            .capacity = capacity,                                                                                                                                           \
            .element_size = sizeof( ELEMENT_TYPE )                                                                                                                          \
        };                                                                                                                                                                  \
                                                                                                                                                                            \
        memcpy( TYPENAME_LOWERCASE->data, data, length * sizeof( ELEMENT_TYPE ) );                                                                                          \
    }                                                                                                                                                                       \
                                                                                                                                                                            \
    void TYPENAME_LOWERCASE ## __clear(                                                                                                                                     \
        TYPENAME *TYPENAME_LOWERCASE,                                                                                                                                       \
        Allocator *allocator                                                                                                                                                \
    ){                                                                                                                                                                      \
        if( TYPENAME_LOWERCASE != NULL ){                                                                                                                                   \
            allocator__free( allocator, TYPENAME_LOWERCASE->data );                                                                                                         \
            TYPENAME_LOWERCASE->data = NULL;                                                                                                                                \
            TYPENAME_LOWERCASE->length = 0;                                                                                                                                 \
            TYPENAME_LOWERCASE->capacity = 0;                                                                                                                               \
        }                                                                                                                                                                   \
    }                                                                                                                                                                       \
                                                                                                                                                                            \
    bool TYPENAME_LOWERCASE ## __equals(                                                                                                                                    \
        TYPENAME const *first,                                                                                                                                              \
        TYPENAME const *second                                                                                                                                              \
    ){                                                                                                                                                                      \
        if( first->length != second->length ){                                                                                                                              \
            return false;                                                                                                                                                   \
        }                                                                                                                                                                   \
                                                                                                                                                                            \
        for( unsigned long long element_index = 0; element_index < first->length; element_index++ ){                                                                        \
            if( ELEMENT_TYPE__EQUALS_FUNCTION( &first->data[ element_index ], &second->data[ element_index ] ) == 0 ){                                                      \
                return false;                                                                                                                                               \
            }                                                                                                                                                               \
        }                                                                                                                                                                   \
                                                                                                                                                                            \
        return true;                                                                                                                                                        \
    }                                                                                                                                                                       \
                                                                                                                                                                            \


/**
 *  @} group array
 */

#endif // KIRKE__ARRAY__H
