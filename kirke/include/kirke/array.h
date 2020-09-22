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
 *  with a call to the macro
 *      ARRAY__DEFINE( TYPENAME, TYPENAME_LOWERCASE, ELEMENT_TYPE, ELEMENT_TYPE__EQUALS_FUNCTION ),
 *  which defines the implementations of interface methods declared herein.
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
     *  \brief Fully initialize an array with allocated memory.                                                                                                             \
     *  \param TYPENAME_LOWERCASE A pointer to the array which will be initialized.                                                                                         \
     *  \param allocator A pointer to the Allocator which will be used to initialize memory owned by                                                                        \
     *  the array.                                                                                                                                                          \
     *  \param capacity The desired capacity of the array, in elements.                                                                                                     \
     */                                                                                                                                                                     \
    void TYPENAME_LOWERCASE ## __initialize(                                                                                                                                \
        TYPENAME *TYPENAME_LOWERCASE,                                                                                                                                       \
        Allocator *allocator,                                                                                                                                               \
        unsigned long long capacity                                                                                                                                         \
    );                                                                                                                                                                      \
                                                                                                                                                                            \
    /**                                                                                                                                                                     \
     *  \brief This method fully initializes an array with the given data                                                                                                   \
     *  \param TYPENAME_LOWERCASE A pointer to the array which will be initialized.                                                                                         \
     *  \param allocator A pointer to the Allocator which will be used to initialize memory owned by                                                                        \
     *  the array.                                                                                                                                                          \
     *  \param data A pointer to the memory region containing the elements which will be contained by                                                                       \
     *  the array. Elements to be copied and \p data will not be modified. Managing the memory                                                                              \
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
     *  \brief This method searches for the first occurrence of the specified sequence, and returns the element                                                             \
     *  index of the start of that occurrence.                                                                                                                              \
     *  \param TYPENAME_LOWERCASE A pointer to an array in which to search for the specified sequence                                                                       \
     *  \param sequence A pointer to an array containing the sequence for which to search.                                                                                  \
     *  \param index An out parameter. Upon successful completion, this will store the index at which the                                                                   \
     *  specified sequence was found.  If the specified sequence was not found, then this will store the number of                                                          \
     *  elements contained in the TYPENAME.                                                                                                                                 \
     *  \returns Returns true if the specified sequence was found.                                                                                                          \
     *  \returns Returns false if the specified sequance was not found.                                                                                                     \
     */                                                                                                                                                                     \
    bool TYPENAME_LOWERCASE ## __index_of(                                                                                                                                  \
        const TYPENAME* TYPENAME_LOWERCASE,                                                                                                                                 \
        const TYPENAME* sequence,                                                                                                                                           \
        unsigned long long *out_index                                                                                                                                       \
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
     *  \brief Clears the specified elements of the given array by setting them equal to 0.                                                                                 \
     *  \param TYPENAME_LOWERCASE A pointer to the array whose elements will be cleared.                                                                                    \
     *  \param start_index The index of the first element to be cleared.                                                                                                    \
     *  \param element_count The number of elements to be cleared.                                                                                                          \
     */                                                                                                                                                                     \
    void TYPENAME_LOWERCASE ## __clear_elements(                                                                                                                            \
        TYPENAME *TYPENAME_LOWERCASE,                                                                                                                                       \
        unsigned long long start_index,                                                                                                                                     \
        unsigned long long element_count                                                                                                                                    \
    );                                                                                                                                                                      \
                                                                                                                                                                            \
    /**                                                                                                                                                                     \
     *  \brief This method creates, initializes and returns an array with the same length, capacity                                                                         \
     *  and elements as the passed-in array. Elements are copied, so modifying the returned array will                                                                      \
     *  not affect the underlying data of the passed-in array.                                                                                                              \
     *  \param TYPENAME_LOWERCASE A pointer to the array which will be cloned.                                                                                              \
     *  \param allocator A pointer to the allocator which will be used to allocate new memory for the clone.                                                                \
     *  \returns A pointer to the newly-created array.                                                                                                                      \
     */                                                                                                                                                                     \
    TYPENAME *TYPENAME_LOWERCASE ## __clone(                                                                                                                                \
        TYPENAME const *TYPENAME_LOWERCASE,                                                                                                                                 \
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
 *  \param ELEMENT_TYPE__EQUALS_FUNCTION A function which will compare two pointers to const array elements, returning
 *  true if they are equal, and false otherwise. The signature should be:
 *      bool (*equals_function)( const *ELEMENT_TYPE, const *ELEMENT_TYPE ).
 *  This is used, for example, to implement the method array__equals.
 *
 *  The array metaclass has no means of knowing what type of elements are contained within - they could be integral types,
 *  user-defined structures, or pointers to either. Users may also have different ideas about how these types should be
 *  compared for equality, as in by address or a field by field comparison. Allowing the user to supply an arbitrary equality
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
    void TYPENAME_LOWERCASE ## __clear_elements(                                                                                                                            \
        TYPENAME *TYPENAME_LOWERCASE,                                                                                                                                       \
        unsigned long long start_index,                                                                                                                                     \
        unsigned long long element_count                                                                                                                                    \
    ){                                                                                                                                                                      \
        if( TYPENAME_LOWERCASE->capacity < element_count ){                                                                                                                 \
            log__warning(                                                                                                                                                   \
                "%s__clear_elements: Parameter element_count is greater than Array capacity.  elemen_count: %d. capacity: %d.",                                             \
                #TYPENAME_LOWERCASE,                                                                                                                                        \
                element_count,                                                                                                                                              \
                TYPENAME_LOWERCASE->capacity                                                                                                                                \
            );                                                                                                                                                              \
        }                                                                                                                                                                   \
                                                                                                                                                                            \
        memset(                                                                                                                                                             \
            TYPENAME_LOWERCASE->data + start_index,                                                                                                                         \
            0,                                                                                                                                                              \
            math__min__ullong( TYPENAME_LOWERCASE->length, element_count ) * TYPENAME_LOWERCASE->element_size                                                               \
        );                                                                                                                                                                  \
    }                                                                                                                                                                       \
                                                                                                                                                                            \
    TYPENAME *TYPENAME_LOWERCASE ## __clone(                                                                                                                                \
        TYPENAME const *TYPENAME_LOWERCASE,                                                                                                                                 \
        Allocator *allocator                                                                                                                                                \
    ){                                                                                                                                                                      \
        TYPENAME *new_ ## TYPENAME_LOWERCASE = (TYPENAME*) allocator__alloc( allocator, sizeof( TYPENAME ) );                                                               \
        *new_ ## TYPENAME_LOWERCASE = (TYPENAME) {                                                                                                                          \
            /* Cast for C++ compatibility */                                                                                                                                \
            .data = (ELEMENT_TYPE*) allocator__alloc( allocator, TYPENAME_LOWERCASE->length * sizeof( ELEMENT_TYPE ) ),                                                     \
            .length = TYPENAME_LOWERCASE->length,                                                                                                                           \
            .capacity = TYPENAME_LOWERCASE->capacity,                                                                                                                       \
            .element_size = sizeof( ELEMENT_TYPE )                                                                                                                          \
        };                                                                                                                                                                  \
                                                                                                                                                                            \
        memcpy( new_ ## TYPENAME_LOWERCASE->data, TYPENAME_LOWERCASE->data, TYPENAME_LOWERCASE->length * sizeof( ELEMENT_TYPE ) );                                          \
                                                                                                                                                                            \
        return new_ ## TYPENAME_LOWERCASE;                                                                                                                                  \
    }                                                                                                                                                                       \
                                                                                                                                                                            \
    bool TYPENAME_LOWERCASE ## __equals(                                                                                                                                    \
        TYPENAME const *first,                                                                                                                                              \
        TYPENAME const *second                                                                                                                                              \
    ){                                                                                                                                                                      \
        if( first == NULL || second == NULL ){                                                                                                                              \
            log__warning(                                                                                                                                                   \
                "%s__equals: NULL passed as parameter. Parameter \'first\': %p. Parameter \'second\': %p.",                                                                 \
                #TYPENAME_LOWERCASE,                                                                                                                                        \
                first,                                                                                                                                                      \
                second                                                                                                                                                      \
            );                                                                                                                                                              \
                                                                                                                                                                            \
            if( first == second ){                                                                                                                                          \
                return true;                                                                                                                                                \
            }                                                                                                                                                               \
            return false;                                                                                                                                                   \
        }                                                                                                                                                                   \
                                                                                                                                                                            \
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
    bool TYPENAME_LOWERCASE ## __index_of(                                                                                                                                  \
        const TYPENAME* TYPENAME_LOWERCASE,                                                                                                                                 \
        const TYPENAME* sequence,                                                                                                                                           \
        unsigned long long *out_index                                                                                                                                       \
    ){                                                                                                                                                                      \
        (void)( TYPENAME_LOWERCASE );                                                                                                                                       \
        (void)( sequence );                                                                                                                                                 \
        (void)( out_index );                                                                                                                                                \
        return false;                                                                                                                                                       \
    }                                                                                                                                                                       \
                                                                                                                                                                            \

/**
 *  @} group array
 */

#endif // KIRKE__ARRAY__H
