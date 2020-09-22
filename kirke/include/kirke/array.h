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
#define ARRAY__DECLARE( TYPENAME, TYPENAME_LOWERCASE, ELEMENT_TYPE )                                                                                                \
    /*                                                                                                                                                              \
     *  A structure which wraps an array of like types, tracking allocated capacity and length.                                                                     \
     */                                                                                                                                                             \
    typedef struct TYPENAME {                                                                                                                                       \
        /**                                                                                                                                                         \
         * A pointer to the memory region containing elements contained by the array.                                                                               \
         */                                                                                                                                                         \
        ELEMENT_TYPE *data;                                                                                                                                         \
        /**                                                                                                                                                         \
         * The actual length of the array, in elements                                                                                                              \
         */                                                                                                                                                         \
        unsigned long long length;                                                                                                                                  \
        /**                                                                                                                                                         \
         * The allocated capacity of the array, in elements.                                                                                                        \
         */                                                                                                                                                         \
        unsigned long long capacity;                                                                                                                                \
        /**                                                                                                                                                         \
         *  The size a single element stored in the array.                                                                                                          \
         */                                                                                                                                                         \
        unsigned long long element_size;                                                                                                                            \
    } TYPENAME;                                                                                                                                                     \
                                                                                                                                                                    \
    /**                                                                                                                                                             \
     *  \brief Fully initialize an array with allocated memory.                                                                                                     \
     *  \param array A pointer to the array which will be initialized.                                                                                              \
     *  \param allocator A pointer to the Allocator which will be used to initialize memory owned by                                                                \
     *  the array.                                                                                                                                                  \
     *  \param capacity The desired capacity of the array, in elements.                                                                                             \
     */                                                                                                                                                             \
    void TYPENAME_LOWERCASE ## __initialize(                                                                                                                        \
        TYPENAME *TYPENAME_LOWERCASE,                                                                                                                               \
        Allocator *allocator,                                                                                                                                       \
        unsigned long long capacity                                                                                                                                 \
    );                                                                                                                                                              \
                                                                                                                                                                    \
    /**                                                                                                                                                             \
     *  \brief This method fully initializes an array with the given data                                                                                           \
     *  \param array A pointer to the array which will be initialized.                                                                                              \
     *  \param allocator A pointer to the Allocator which will be used to initialize memory owned by                                                                \
     *  the array.                                                                                                                                                  \
     *  \param data A pointer to the memory region containing the elements which will be contained by                                                               \
     *  the array. Elements to be copied and \p data will not be modified. Managing the memory                                                                      \
     *  allocated for \p data is the caller's responsibility.                                                                                                       \
     *  \param length The length, in elements of \p data.                                                                                                           \
     */                                                                                                                                                             \
    void TYPENAME_LOWERCASE ## __initialize__full(                                                                                                                  \
        TYPENAME *TYPENAME_LOWERCASE,                                                                                                                               \
        Allocator* allocator,                                                                                                                                       \
        ELEMENT_TYPE const *data,                                                                                                                                   \
        unsigned long long length,                                                                                                                                  \
        unsigned long long capacity                                                                                                                                 \
    );                                                                                                                                                              \
                                                                                                                                                                    \
    /**                                                                                                                                                             \
     *  \brief This method searches for the first occurrence of the specified sequence, and returns the element                                                     \
     *  index of the start of that occurrence.                                                                                                                      \
     *  \param array A pointer to an array in which to search for the specified sequence                                                                            \
     *  \param sequence A pointer to an array containing the sequence for which to search.                                                                          \
     *  \param index An out parameter. Upon successful completion, this will store the index at which the                                                           \
     *  specified sequence was found.  If the specified sequence was not found, then this will store the number of                                                  \
     *  elements contained in the TYPENAME.                                                                                                                         \
     *  \returns Returns true if the specified sequence was found.                                                                                                  \
     *  \returns Returns false if the specified sequance was not found.                                                                                             \
     */                                                                                                                                                             \
    bool TYPENAME_LOWERCASE ## __index_of(                                                                                                                          \
        const TYPENAME* TYPENAME_LOWERCASE,                                                                                                                         \
        const TYPENAME* sequence,                                                                                                                                   \
        unsigned long long *out_index                                                                                                                               \
    );                                                                                                                                                              \
                                                                                                                                                                    \
    /**                                                                                                                                                             \
     *  \brief Frees the memory allocated for the array, without freeing the array structure itself.                                                                \
     *  \param array The array whose memory is to be cleared                                                                                                        \
     *  \param allocator The allocator which was used to allocate the array's data. This must also be used                                                          \
     *  to free the array's data.                                                                                                                                   \
     *  \note This method will free the array's 'data' field. However, if the array contains pointers to                                                            \
     *  dynamically-allocated structures, then those must be freed prior to calling this method, or you                                                             \
     *  may lose your reference to those pointers and leak memory.                                                                                                  \
     */                                                                                                                                                             \
    void TYPENAME_LOWERCASE ## __clear(                                                                                                                             \
        TYPENAME *TYPENAME_LOWERCASE,                                                                                                                               \
        Allocator *allocator                                                                                                                                        \
    );                                                                                                                                                              \
                                                                                                                                                                    \
    /**                                                                                                                                                             \
     *  \brief Clears the specified elements of the given array by setting them equal to 0.                                                                         \
     *  \param array A pointer to the array whose elements will be cleared.                                                                                         \
     *  \param start_index The index of the first element to be cleared.                                                                                            \
     *  \param element_count The number of elements to be cleared.                                                                                                  \
     */                                                                                                                                                             \
    void TYPENAME_LOWERCASE ## __clear_elements(                                                                                                                    \
        TYPENAME *TYPENAME_LOWERCASE,                                                                                                                               \
        unsigned long long start_index,                                                                                                                             \
        unsigned long long element_count                                                                                                                            \
    );                                                                                                                                                              \
                                                                                                                                                                    \
    /**                                                                                                                                                             \
     *  \brief This method creates, initializes and returns an array with the same length, capacity                                                                 \
     *  and elements as the passed-in array. Elements are copied, so modifying the returned array will                                                              \
     *  not affect the underlying data of the passed-in array.                                                                                                      \
     *  \param array A pointer to the array which will be cloned.                                                                                                   \
     *  \param allocator A pointer to the allocator which will be used to allocate new memory for the clone.                                                        \
     *  \returns A pointer to the newly-created array.                                                                                                              \
     */                                                                                                                                                             \
    TYPENAME *TYPENAME_LOWERCASE ## __clone(                                                                                                                        \
        TYPENAME const *TYPENAME_LOWERCASE,                                                                                                                         \
        Allocator *allocator                                                                                                                                        \
    );                                                                                                                                                              \
                                                                                                                                                                    \
    /**                                                                                                                                                             \
     *  \brief Compares two array structures for equality.                                                                                                          \
     *  \param first The first array to be compared.                                                                                                                \
     *  \param second The second array to be compared.                                                                                                              \
     *  \returns Returns true if both array structures are equal - that is, they have the same element size, length,                                                \
     *  and if they contain the same elements. Capacity is not compared.                                                                                            \
     *  \returns Returns false if both TYPENAME structures are not equal.                                                                                           \
     */                                                                                                                                                             \
    bool TYPENAME_LOWERCASE ## __equals(                                                                                                                            \
        TYPENAME const *first,                                                                                                                                      \
        TYPENAME const *second                                                                                                                                      \
    );                                                                                                                                                              \
                                                                                                                                                                    \
    /*                                                                                                                                                              \
     *  A wrapper around an array type, which provides automatic growth and memory management.                                                                      \
     */                                                                                                                                                             \
    typedef struct Auto ## TYPENAME {                                                                                                                               \
        /**                                                                                                                                                         \
         *  A pointer to the underlying array.                                                                                                                      \
         */                                                                                                                                                         \
        TYPENAME *TYPENAME_LOWERCASE;                                                                                                                               \
        /**                                                                                                                                                         \
         *  The allocator used for memory management.                                                                                                               \
         */                                                                                                                                                         \
        Allocator *allocator;                                                                                                                                       \
    } Auto ## TYPENAME;                                                                                                                                             \
                                                                                                                                                                    \
    /**                                                                                                                                                             \
     *  \brief This method intializes an AutoArray structure.                                                                                                       \
     *  \param auto_array A pointer to the AutoArray to be initialized.                                                                                             \
     *  \param allocator A pointer to the allocator which will be used to manage memory controlled by the                                                           \
     *  AutoArray.                                                                                                                                                  \
     *  \param capacity The desired initial capacity of the AutoArray, in elements.                                                                                 \
     */                                                                                                                                                             \
    void auto_ ## TYPENAME_LOWERCASE ## __initialize(                                                                                                               \
        Auto ## TYPENAME *auto_ ## TYPENAME_LOWERCASE,                                                                                                              \
        Allocator *allocator,                                                                                                                                       \
        unsigned long long capacity                                                                                                                                 \
    );                                                                                                                                                              \
                                                                                                                                                                    \
    /**                                                                                                                                                             \
     *  \brief This method will clear an AutoArray structure, and the underlying memory contained in                                                                \
     *  auto_array->array be freed. However, if the elements contained by this field are themselves                                                                 \
     *  dynamically-allocated, then they must be freed prior to calling this method, as you may lose                                                                \
     *  your reference to these elements when auto_array->array is freed. This method will also set                                                                 \
     *  the AutoArray's allocator to NULL. The allocator field is borrowed rather than owned, so it                                                                 \
     *  will not be deinitialized by calling this method.                                                                                                           \
     *  \param auto_array A pointer to the AutoArray. structure which will be cleared.                                                                              \
     */                                                                                                                                                             \
    void auto_ ## TYPENAME_LOWERCASE ## __clear(                                                                                                                    \
        Auto ## TYPENAME *auto_ ## TYPENAME_LOWERCASE                                                                                                               \
    );                                                                                                                                                              \
                                                                                                                                                                    \
    /**                                                                                                                                                             \
     *  \brief This method appends a single element to the end of an AutoArray, allocating additional memory as necessary.                                          \
     *  \param auto_array A pointer to the AutoArray to which the element will be appended.                                                                         \
     *  \param element The element which will be appended to the AutoArray.                                                                                         \
     */                                                                                                                                                             \
    inline void auto_ ## TYPENAME_LOWERCASE ## __append_element(                                                                                                    \
        Auto ## TYPENAME *auto_ ## TYPENAME_LOWERCASE,                                                                                                              \
        ELEMENT_TYPE element                                                                                                                                        \
    );                                                                                                                                                              \
                                                                                                                                                                    \
    /**                                                                                                                                                             \
     *  \brief This method appends elements to the end of an AutoArray, allocating additional memory as necessary.                                                  \
     *  \param auto_array A pointer to the AutoArray to which the elements will be appended.                                                                        \
     *  \param element_count The number of elements to be appended.                                                                                                 \
     *  \param data A pointer to the memory region containing the elements will be appended to the AutoArray.                                                       \
     */                                                                                                                                                             \
    void auto_ ## TYPENAME_LOWERCASE ## __append_elements(                                                                                                          \
        Auto ## TYPENAME *auto_ ## TYPENAME_LOWERCASE,                                                                                                              \
        unsigned long long element_count,                                                                                                                           \
        ELEMENT_TYPE const *data                                                                                                                                    \
    );                                                                                                                                                              \
                                                                                                                                                                    \
    /**                                                                                                                                                             \
     *  \brief This method prepends an element to the beginning of an AutoArray, allocating additional memory as necessary.                                         \
     *  \param auto_array A pointer to the AutoArray to which the element will be prepended.                                                                        \
     *  \param element The element which will be prepended to the AutoArray.                                                                                        \
     */                                                                                                                                                             \
    inline void auto_ ## TYPENAME_LOWERCASE ## __prepend_element(                                                                                                   \
        Auto ## TYPENAME *auto_ ## TYPENAME_LOWERCASE,                                                                                                              \
        ELEMENT_TYPE element                                                                                                                                        \
    );                                                                                                                                                              \
                                                                                                                                                                    \
    /**                                                                                                                                                             \
     *  \brief This method prepends elements to the beginning of an AutoArray, allocating additional memory as necessary.                                           \
     *  \param auto_array A pointer to the AutoArray to which the elements will be prepended.                                                                       \
     *  \param element_count The number of elements to be prepended.                                                                                                \
     *  \param data A pointer to the memory region containing the elements will be prepended to the AutoArray.                                                      \
     */                                                                                                                                                             \
    void auto_ ## TYPENAME_LOWERCASE ## __prepend_elements(                                                                                                         \
        Auto ## TYPENAME *auto_ ## TYPENAME_LOWERCASE,                                                                                                              \
        unsigned long long element_count,                                                                                                                           \
        ELEMENT_TYPE const *data                                                                                                                                    \
    );                                                                                                                                                              \
                                                                                                                                                                    \
    /**                                                                                                                                                             \
     *  \brief This method inserts an element into the specified location of an AutoArray, allocating additional memory as necessary.                               \
     *  \param auto_array A pointer to the AutoArray into which the element will be inserted.                                                                       \
     *  \param index The index at which the element will be inserted.                                                                                               \
     *  \param element The element which will be inserted.                                                                                                          \
     */                                                                                                                                                             \
    inline void auto_ ## TYPENAME_LOWERCASE ## __insert_element(                                                                                                    \
        Auto ## TYPENAME *auto_ ## TYPENAME_LOWERCASE,                                                                                                              \
        unsigned long long index,                                                                                                                                   \
        ELEMENT_TYPE element                                                                                                                                        \
    );                                                                                                                                                              \
                                                                                                                                                                    \
    /**                                                                                                                                                             \
     *  \brief This method inserts elements to the specified location of an AutoArray, allocating additional memory as necessary.                                   \
     *  \param auto_array A pointer to the AutoArray into which elements will be inserted.                                                                          \
     *  \param start_index The index at which the first element will be inserted.                                                                                   \
     *  \param element_count The number of elements which will be inserted.                                                                                         \
     *  \param data A pointer to the memory region containing the elements to be inserted.                                                                          \
     */                                                                                                                                                             \
    void auto_ ## TYPENAME_LOWERCASE ## __insert_elements(                                                                                                          \
        Auto ## TYPENAME *auto_ ## TYPENAME_LOWERCASE,                                                                                                              \
        unsigned long long start_index,                                                                                                                             \
        unsigned long long element_count,                                                                                                                           \
        ELEMENT_TYPE const *data                                                                                                                                    \
    );                                                                                                                                                              \
                                                                                                                                                                    \
    /**                                                                                                                                                             \
     *  \brief Removes the element at the given index.                                                                                                              \
     *  \param auto_array The AutoArray from which the element will be removed.                                                                                     \
     *  \param index The index of the element which will be removed.                                                                                                \
     *  \note This method preserves ordering of the remaining elements within the AutoArray. If ordering is not important,                                          \
     *  a faster alternative is the method auto_array__remove_element_fast.                                                                                         \
     */                                                                                                                                                             \
    void auto_ ## TYPENAME_LOWERCASE ## __remove_element(                                                                                                           \
        Auto ## TYPENAME *auto_ ## TYPENAME_LOWERCASE,                                                                                                              \
        unsigned long long element_index                                                                                                                            \
    );                                                                                                                                                              \
                                                                                                                                                                    \
    /**                                                                                                                                                             \
     *  \brief Removes the element at the given index. Ordering is not preserved. Instead, the last element is copied to                                            \
     *  the specified index.                                                                                                                                        \
     *  \param auto_array The AutoArray from which the element will be removed.                                                                                     \
     *  \param index The index of the element which will be removed.                                                                                                \
     */                                                                                                                                                             \
    void auto_ ## TYPENAME_LOWERCASE ## __remove_element__fast(                                                                                                     \
        Auto ## TYPENAME* auto_ ## TYPENAME_LOWERCASE,                                                                                                              \
        unsigned long long element_index                                                                                                                            \
    );                                                                                                                                                              \
                                                                                                                                                                    \
    /**                                                                                                                                                             \
     *  \brief This method removes a sequence of elements from an AutoArray.                                                                                        \
     *  \param auto_array A pointer to the AutoArray from which elements will be removed.                                                                           \
     *  \param start_index The index of the first element which will be removed.                                                                                    \
     *  \param element_count The number of elements to remove.                                                                                                      \
     */                                                                                                                                                             \
    void auto_ ## TYPENAME_LOWERCASE ## __remove_range(                                                                                                             \
        Auto ## TYPENAME* auto_ ## TYPENAME_LOWERCASE,                                                                                                              \
        unsigned long long start_index,                                                                                                                             \
        unsigned long long element_count                                                                                                                            \
    );

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
#define ARRAY__DEFINE( TYPENAME, TYPENAME_LOWERCASE, ELEMENT_TYPE, ELEMENT_TYPE__EQUALS_FUNCTION )                                                                  \
                                                                                                                                                                    \
    void TYPENAME_LOWERCASE ## __initialize(                                                                                                                        \
        TYPENAME *TYPENAME_LOWERCASE,                                                                                                                               \
        Allocator* allocator,                                                                                                                                       \
        unsigned long long capacity                                                                                                                                 \
    ){                                                                                                                                                              \
        *TYPENAME_LOWERCASE = (TYPENAME){                                                                                                                           \
            /* Cast for C++ compatibility */                                                                                                                        \
            .data = (ELEMENT_TYPE*) allocator__alloc( allocator, capacity * sizeof( ELEMENT_TYPE ) ),                                                               \
            .length = 0,                                                                                                                                            \
            .capacity = capacity,                                                                                                                                   \
            .element_size = sizeof( ELEMENT_TYPE )                                                                                                                  \
        };                                                                                                                                                          \
    }                                                                                                                                                               \
                                                                                                                                                                    \
    void TYPENAME_LOWERCASE ## __initialize__full(                                                                                                                  \
        TYPENAME *TYPENAME_LOWERCASE,                                                                                                                               \
        Allocator* allocator,                                                                                                                                       \
        ELEMENT_TYPE const *data,                                                                                                                                   \
        unsigned long long length,                                                                                                                                  \
        unsigned long long capacity                                                                                                                                 \
    ){                                                                                                                                                              \
        *TYPENAME_LOWERCASE = (TYPENAME) {                                                                                                                          \
            /* Cast for C++ compatibility */                                                                                                                        \
            .data = (ELEMENT_TYPE*) allocator__alloc( allocator, length * sizeof( ELEMENT_TYPE ) ),                                                                 \
            .length = length,                                                                                                                                       \
            .capacity = capacity,                                                                                                                                   \
            .element_size = sizeof( ELEMENT_TYPE )                                                                                                                  \
        };                                                                                                                                                          \
                                                                                                                                                                    \
        memcpy( TYPENAME_LOWERCASE->data, data, length * sizeof( ELEMENT_TYPE ) );                                                                                  \
    }                                                                                                                                                               \
                                                                                                                                                                    \
    void TYPENAME_LOWERCASE ## __clear(                                                                                                                             \
        TYPENAME *TYPENAME_LOWERCASE,                                                                                                                               \
        Allocator *allocator                                                                                                                                        \
    ){                                                                                                                                                              \
        if( TYPENAME_LOWERCASE != NULL ){                                                                                                                           \
            allocator__free( allocator, TYPENAME_LOWERCASE->data );                                                                                                 \
            TYPENAME_LOWERCASE->data = NULL;                                                                                                                        \
            TYPENAME_LOWERCASE->length = 0;                                                                                                                         \
            TYPENAME_LOWERCASE->capacity = 0;                                                                                                                       \
        }                                                                                                                                                           \
    }                                                                                                                                                               \
                                                                                                                                                                    \
    void TYPENAME_LOWERCASE ## __clear_elements(                                                                                                                    \
        TYPENAME *TYPENAME_LOWERCASE,                                                                                                                               \
        unsigned long long start_index,                                                                                                                             \
        unsigned long long element_count                                                                                                                            \
    ){                                                                                                                                                              \
        if( TYPENAME_LOWERCASE->capacity < element_count ){                                                                                                         \
            log__warning(                                                                                                                                           \
                "%s__clear_elements: Parameter element_count is greater than Array capacity.  elemen_count: %d. capacity: %d.",                                     \
                #TYPENAME_LOWERCASE,                                                                                                                                \
                element_count,                                                                                                                                      \
                TYPENAME_LOWERCASE->capacity                                                                                                                        \
            );                                                                                                                                                      \
        }                                                                                                                                                           \
                                                                                                                                                                    \
        memset(                                                                                                                                                     \
            TYPENAME_LOWERCASE->data + start_index,                                                                                                                 \
            0,                                                                                                                                                      \
            math__min__ullong( TYPENAME_LOWERCASE->length, element_count ) * TYPENAME_LOWERCASE->element_size                                                       \
        );                                                                                                                                                          \
    }                                                                                                                                                               \
                                                                                                                                                                    \
    TYPENAME *TYPENAME_LOWERCASE ## __clone(                                                                                                                        \
        TYPENAME const *TYPENAME_LOWERCASE,                                                                                                                         \
        Allocator *allocator                                                                                                                                        \
    ){                                                                                                                                                              \
        TYPENAME *new_ ## TYPENAME_LOWERCASE = (TYPENAME*) allocator__alloc( allocator, sizeof( TYPENAME ) );                                                       \
        *new_ ## TYPENAME_LOWERCASE = (TYPENAME) {                                                                                                                  \
            /* Cast for C++ compatibility */                                                                                                                        \
            .data = (ELEMENT_TYPE*) allocator__alloc( allocator, TYPENAME_LOWERCASE->length * sizeof( ELEMENT_TYPE ) ),                                             \
            .length = TYPENAME_LOWERCASE->length,                                                                                                                   \
            .capacity = TYPENAME_LOWERCASE->capacity,                                                                                                               \
            .element_size = sizeof( ELEMENT_TYPE )                                                                                                                  \
        };                                                                                                                                                          \
                                                                                                                                                                    \
        memcpy( new_ ## TYPENAME_LOWERCASE->data, TYPENAME_LOWERCASE->data, TYPENAME_LOWERCASE->length * sizeof( ELEMENT_TYPE ) );                                  \
                                                                                                                                                                    \
        return new_ ## TYPENAME_LOWERCASE;                                                                                                                          \
    }                                                                                                                                                               \
                                                                                                                                                                    \
    bool TYPENAME_LOWERCASE ## __equals(                                                                                                                            \
        TYPENAME const *first,                                                                                                                                      \
        TYPENAME const *second                                                                                                                                      \
    ){                                                                                                                                                              \
        if( first == NULL || second == NULL ){                                                                                                                      \
            log__warning(                                                                                                                                           \
                "%s__equals: NULL passed as parameter. Parameter \'first\': %p. Parameter \'second\': %p.",                                                         \
                #TYPENAME_LOWERCASE,                                                                                                                                \
                first,                                                                                                                                              \
                second                                                                                                                                              \
            );                                                                                                                                                      \
                                                                                                                                                                    \
            if( first == second ){                                                                                                                                  \
                return true;                                                                                                                                        \
            }                                                                                                                                                       \
            return false;                                                                                                                                           \
        }                                                                                                                                                           \
                                                                                                                                                                    \
        if( first->length != second->length ){                                                                                                                      \
            return false;                                                                                                                                           \
        }                                                                                                                                                           \
                                                                                                                                                                    \
        for( unsigned long long element_index = 0; element_index < first->length; element_index++ ){                                                                \
            if( ELEMENT_TYPE__EQUALS_FUNCTION( &first->data[ element_index ], &second->data[ element_index ] ) == 0 ){                                              \
                return false;                                                                                                                                       \
            }                                                                                                                                                       \
        }                                                                                                                                                           \
                                                                                                                                                                    \
        return true;                                                                                                                                                \
    }                                                                                                                                                               \
                                                                                                                                                                    \
    bool TYPENAME_LOWERCASE ## __index_of(                                                                                                                          \
        const TYPENAME* TYPENAME_LOWERCASE,                                                                                                                         \
        const TYPENAME* sequence,                                                                                                                                   \
        unsigned long long *out_index                                                                                                                               \
    ){                                                                                                                                                              \
        for( unsigned long long element_index = 0; element_index < TYPENAME_LOWERCASE->length; element_index++ ){                                                   \
            TYPENAME subsequence = {                                                                                                                                \
                .data = TYPENAME_LOWERCASE->data + element_index,                                                                                                   \
                .length = sequence->length,                                                                                                                         \
                .capacity = sequence->length,                                                                                                                       \
                .element_size = sizeof( ELEMENT_TYPE )                                                                                                              \
            };                                                                                                                                                      \
                                                                                                                                                                    \
            if( TYPENAME_LOWERCASE ## __equals( &subsequence, sequence ) ){                                                                                         \
                *out_index = element_index;                                                                                                                         \
                return true;                                                                                                                                        \
            }                                                                                                                                                       \
        }                                                                                                                                                           \
                                                                                                                                                                    \
        return false;                                                                                                                                               \
    }                                                                                                                                                               \
                                                                                                                                                                    \
    void auto_ ## TYPENAME_LOWERCASE ## __initialize(                                                                                                               \
        Auto ## TYPENAME *auto_ ## TYPENAME_LOWERCASE,                                                                                                              \
        Allocator *allocator,                                                                                                                                       \
        unsigned long long capacity                                                                                                                                 \
    ){                                                                                                                                                              \
        /* Cast for C++ compatibility */                                                                                                                            \
        auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE = (TYPENAME*) allocator__alloc( allocator, sizeof( TYPENAME ) );                                            \
        TYPENAME_LOWERCASE ## __initialize( auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE, allocator, capacity );                                                 \
        auto_ ## TYPENAME_LOWERCASE->allocator = allocator;                                                                                                         \
    }                                                                                                                                                               \
                                                                                                                                                                    \
    void auto_ ## TYPENAME_LOWERCASE ## __clear( Auto ## TYPENAME *auto_ ## TYPENAME_LOWERCASE ){                                                                   \
        if( auto_ ## TYPENAME_LOWERCASE != NULL ){                                                                                                                  \
            TYPENAME_LOWERCASE ## __clear( auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE, auto_ ## TYPENAME_LOWERCASE->allocator );                               \
            allocator__free( auto_ ## TYPENAME_LOWERCASE->allocator, auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE );                                             \
            auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE = NULL;                                                                                                 \
            auto_ ## TYPENAME_LOWERCASE->allocator = NULL;                                                                                                          \
        }                                                                                                                                                           \
    }                                                                                                                                                               \
                                                                                                                                                                    \
    /**                                                                                                                                                             \
     *  \brief Possibly expands the memory allocated for auto_array->array->data.                                                                                   \
     *  If auto_array->capacity < new_capacity, then the memory allocated for auto_array->array->data                                                               \
     *  will be expanded to new_capacity. Otherwise, no action is taken.                                                                                            \
     *  \param auto_ ## TYPENAME_LOWERCASE A pointer to the AutoSlice whose memory may be expanded.                                                                 \
     *  \param new_capacity The desired capacity, in elements.                                                                                                      \
     */                                                                                                                                                             \
    static void auto_ ## TYPENAME_LOWERCASE ## __maybe_expand(                                                                                                      \
        Auto ## TYPENAME *auto_ ## TYPENAME_LOWERCASE,                                                                                                              \
        unsigned long long new_capacity                                                                                                                             \
    ){                                                                                                                                                              \
        if(                                                                                                                                                         \
            auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->data == NULL ||                                                                                        \
            new_capacity > auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->capacity                                                                                \
        ){                                                                                                                                                          \
            unsigned long bytes_required = math__nearest_greater_power_of_2__ulong( auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->element_size * new_capacity ); \
                                                                                                                                                                    \
            /* Cast for C++ compatibility */                                                                                                                        \
            auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->data = (ELEMENT_TYPE*) allocator__realloc(                                                             \
                auto_ ## TYPENAME_LOWERCASE->allocator,                                                                                                             \
                auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->data,                                                                                              \
                bytes_required                                                                                                                                      \
            );                                                                                                                                                      \
                                                                                                                                                                    \
            auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->capacity = ( bytes_required / auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->element_size ) - 1;     \
                                                                                                                                                                    \
            TYPENAME_LOWERCASE ## __clear_elements(                                                                                                                 \
                auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE,                                                                                                    \
                auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->length,                                                                                            \
                auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->capacity - auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->length                                 \
            );                                                                                                                                                      \
        }                                                                                                                                                           \
    }                                                                                                                                                               \
                                                                                                                                                                    \
    inline void auto_ ## TYPENAME_LOWERCASE ## __append_element(                                                                                                    \
        Auto ## TYPENAME *auto_ ## TYPENAME_LOWERCASE,                                                                                                              \
        ELEMENT_TYPE element                                                                                                                                        \
    ){                                                                                                                                                              \
        auto_ ## TYPENAME_LOWERCASE ## __append_elements( auto_ ## TYPENAME_LOWERCASE, 1, &element );                                                               \
    }                                                                                                                                                               \
                                                                                                                                                                    \
    void auto_ ## TYPENAME_LOWERCASE ## __append_elements(                                                                                                          \
        Auto ## TYPENAME *auto_ ## TYPENAME_LOWERCASE,                                                                                                              \
        unsigned long long element_count,                                                                                                                           \
        ELEMENT_TYPE const *data                                                                                                                                    \
    ){                                                                                                                                                              \
        RETURN_IF_FAIL( auto_ ## TYPENAME_LOWERCASE != NULL );                                                                                                      \
        RETURN_IF_FAIL( element_count > 0 );                                                                                                                        \
                                                                                                                                                                    \
        auto_ ## TYPENAME_LOWERCASE ## __maybe_expand( auto_ ## TYPENAME_LOWERCASE, auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->length + element_count );      \
                                                                                                                                                                    \
        memcpy(                                                                                                                                                     \
            auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->data + auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->length,                                        \
            data,                                                                                                                                                   \
            element_count * auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->element_size                                                                           \
        );                                                                                                                                                          \
                                                                                                                                                                    \
        auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->length += element_count;                                                                                   \
    }                                                                                                                                                               \
                                                                                                                                                                    \
                                                                                                                                                                    \
    inline void auto_ ## TYPENAME_LOWERCASE ## __prepend_element( Auto ## TYPENAME* auto_ ## TYPENAME_LOWERCASE, ELEMENT_TYPE element ){                            \
        auto_ ## TYPENAME_LOWERCASE ## __prepend_elements( auto_ ## TYPENAME_LOWERCASE, 1, &element );                                                              \
    }                                                                                                                                                               \
                                                                                                                                                                    \
    void auto_ ## TYPENAME_LOWERCASE ## __prepend_elements(                                                                                                         \
        Auto ## TYPENAME* auto_ ## TYPENAME_LOWERCASE,                                                                                                              \
        unsigned long long element_count,                                                                                                                           \
        ELEMENT_TYPE const *data                                                                                                                                    \
    ){                                                                                                                                                              \
        RETURN_IF_FAIL( auto_ ## TYPENAME_LOWERCASE != NULL );                                                                                                      \
        RETURN_IF_FAIL( element_count > 0 );                                                                                                                        \
                                                                                                                                                                    \
        auto_ ## TYPENAME_LOWERCASE ## __maybe_expand( auto_ ## TYPENAME_LOWERCASE, auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->length + element_count );      \
                                                                                                                                                                    \
        /* We use mem__move here because whenever element_count < length, the memory regions will overlap. */                                                       \
        memmove(                                                                                                                                                    \
            auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->data + element_count,                                                                                  \
            auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->data,                                                                                                  \
            auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->length * auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->element_size                                 \
        );                                                                                                                                                          \
                                                                                                                                                                    \
        memcpy(                                                                                                                                                     \
            auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->data,                                                                                                  \
            data,                                                                                                                                                   \
            element_count * auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->element_size                                                                           \
        );                                                                                                                                                          \
                                                                                                                                                                    \
        auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->length += element_count;                                                                                   \
    }                                                                                                                                                               \
                                                                                                                                                                    \
    inline void auto_ ## TYPENAME_LOWERCASE ## __insert_element(                                                                                                    \
        Auto ## TYPENAME *auto_ ## TYPENAME_LOWERCASE,                                                                                                              \
        unsigned long long index,                                                                                                                                   \
        ELEMENT_TYPE element                                                                                                                                        \
    ){                                                                                                                                                              \
        auto_ ## TYPENAME_LOWERCASE ## __insert_elements( auto_ ## TYPENAME_LOWERCASE, index, 1, &element );                                                        \
    }                                                                                                                                                               \
                                                                                                                                                                    \
    void auto_ ## TYPENAME_LOWERCASE ## __insert_elements(                                                                                                          \
        Auto ## TYPENAME *auto_ ## TYPENAME_LOWERCASE,                                                                                                              \
        unsigned long long start_index,                                                                                                                             \
        unsigned long long element_count,                                                                                                                           \
        ELEMENT_TYPE const *data                                                                                                                                    \
    ){                                                                                                                                                              \
        RETURN_IF_FAIL( auto_ ## TYPENAME_LOWERCASE != NULL );                                                                                                      \
        RETURN_IF_FAIL( element_count > 0 );                                                                                                                        \
                                                                                                                                                                    \
        /* This calculation allows for inserting elements at an index greater than the auto_ ## TYPENAME_LOWERCASE's length. */                                     \
        unsigned long long length_after_insertion = math__max__ullong( auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->length, start_index ) + element_count;      \
                                                                                                                                                                    \
        auto_ ## TYPENAME_LOWERCASE ## __maybe_expand( auto_ ## TYPENAME_LOWERCASE, length_after_insertion );                                                       \
                                                                                                                                                                    \
        /* We only have to make room for the inserted elements if they are inserted between existing elements.  */                                                  \
        if( start_index < auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->length ){                                                                                \
            memmove(                                                                                                                                                \
                auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->data + start_index + element_count,                                                                \
                auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->data + start_index,                                                                                \
                ( auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->length - start_index ) * sizeof( ELEMENT_TYPE )                                                  \
            );                                                                                                                                                      \
        }                                                                                                                                                           \
                                                                                                                                                                    \
        memcpy(                                                                                                                                                     \
            auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->data + start_index,                                                                                    \
            data,                                                                                                                                                   \
            element_count * auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->element_size                                                                           \
        );                                                                                                                                                          \
                                                                                                                                                                    \
        auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->length = length_after_insertion;                                                                           \
    }                                                                                                                                                               \
                                                                                                                                                                    \
    void auto_ ## TYPENAME_LOWERCASE ## __remove_element(                                                                                                           \
        Auto ## TYPENAME *auto_ ## TYPENAME_LOWERCASE,                                                                                                              \
        unsigned long long element_index                                                                                                                            \
    ){                                                                                                                                                              \
        RETURN_IF_FAIL( auto_ ## TYPENAME_LOWERCASE != NULL );                                                                                                      \
        RETURN_IF_FAIL( element_index < auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->length );                                                                  \
                                                                                                                                                                    \
        if( element_index != auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->length - 1 ){                                                                         \
            memmove(                                                                                                                                                \
                auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->data + element_index,                                                                              \
                auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->data + element_index + 1,                                                                          \
                ( auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->length - element_index - 1 ) * sizeof( ELEMENT_TYPE )                                            \
            );                                                                                                                                                      \
        }                                                                                                                                                           \
                                                                                                                                                                    \
        auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->length -= 1;                                                                                               \
    }                                                                                                                                                               \
                                                                                                                                                                    \
    void auto_ ## TYPENAME_LOWERCASE ## __remove_element__fast(                                                                                                     \
        Auto ## TYPENAME* auto_ ## TYPENAME_LOWERCASE,                                                                                                              \
        unsigned long long element_index                                                                                                                            \
    ){                                                                                                                                                              \
        RETURN_IF_FAIL( auto_ ## TYPENAME_LOWERCASE != NULL );                                                                                                      \
        RETURN_IF_FAIL( element_index < auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->length );                                                                  \
                                                                                                                                                                    \
        if( element_index != auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->length - 1 ){                                                                         \
            memcpy(                                                                                                                                                 \
                auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->data + element_index,                                                                              \
                auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->data + auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->length - 1,                                \
                auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->element_size                                                                                       \
            );                                                                                                                                                      \
        }                                                                                                                                                           \
        auto_ ## TYPENAME_LOWERCASE->TYPENAME_LOWERCASE->length -= 1;                                                                                               \
    }                                                                                                                                                               \
                                                                                                                                                                    \
    void auto_ ## TYPENAME_LOWERCASE ## __remove_range(                                                                                                             \
        Auto ## TYPENAME* auto_ ## TYPENAME_LOWERCASE,                                                                                                              \
        unsigned long long start_index,                                                                                                                             \
        unsigned long long element_count                                                                                                                            \
    ){                                                                                                                                                              \
        (void)( auto_ ## TYPENAME_LOWERCASE );                                                                                                                      \
        (void)( start_index );                                                                                                                                      \
        (void)( element_count );                                                                                                                                    \
    }

/**
 *  @} group array
 */

#endif // KIRKE__ARRAY__H
