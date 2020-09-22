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

/**
 *  \def ARRAY__DEFINE( TYPENAME, TYPENAME_LOWERCASE, ELEMENT_TYPE )
 *  \brief Defines interface methods for a Array type. This macro must be paired with a call to the macro
 *  ARRAY__DECLARE( TYPENAME, TYPENAME_LOWERCASE, ELEMENT_TYPE ).
 *  \param TYPENAME The name which will was assigned to the structure type.
 *  \param TYPENAME_LOWERCASE Same as TYPENAME, only lowercase. This will be used to prefix interface methods,
 *  as well as to name local variables and parameters for the interface methods.
 *  \param ELEMENT_TYPE The type which will be stored in the array.
 */
#define ARRAY__DEFINE( TYPENAME, TYPENAME_LOWERCASE, ELEMENT_TYPE )                                                                                                         \
                                                                                                                                                                            \
    void TYPENAME_LOWERCASE ## __initialize(                                                                                                                                \
        TYPENAME *TYPENAME_LOWERCASE,                                                                                                                                       \
        Allocator* allocator,                                                                                                                                               \
        unsigned long long capacity                                                                                                                                         \
    ){                                                                                                                                                                      \
        (void)( TYPENAME_LOWERCASE );                                                                                                                                       \
        (void)( allocator );                                                                                                                                                \
        (void)( capacity );                                                                                                                                                 \
    }                                                                                                                                                                       \
                                                                                                                                                                            \
    void TYPENAME_LOWERCASE ## __clear(                                                                                                                                     \
        TYPENAME *TYPENAME_LOWERCASE,                                                                                                                                       \
        Allocator *allocator                                                                                                                                                \
    ){                                                                                                                                                                      \
        (void)( TYPENAME_LOWERCASE );                                                                                                                                       \
        (void)( allocator );                                                                                                                                                \
    }                                                                                                                                                                       \

/**
 *  @} group array
 */

#endif // KIRKE__ARRAY__H
