/** 
 *  \file kirke/macros.h
 */

#ifndef KIRKE__MACROS__H
#define KIRKE__MACROS__H

/**
 *  \defgroup macros Macros
 *  @{
 */

/** 
 *  \def BEGIN_DECLARATIONS
 *  \brief If calling from C++ code (__cplusplus is defined), opens an extern "C" {} block to 
 *  prevent C++ compiler export name mangling. 
 */

/** 
 *  \def END_DECLARATIONS
 *  \brief If calling from C++ code (__cplusplus is defined), closes an extern "C" {} block to 
 *  prevent C++ compiler export name mangling. 
 */
#ifdef __cplusplus
    #define BEGIN_DECLARATIONS extern "C" {
    #define END_DECLARATIONS }
#else
    #define BEGIN_DECLARATIONS
    #define END_DECLARATIONS
#endif // __cplusplus

/**
 *  \def RETURN_IF_FAIL
 *  \brief Convenience macro to exit a function if a given condition does not hold.
 */
#define RETURN_IF_FAIL( predicate ) \
    if( !( predicate ) ){           \
        return;                     \
    }

/**
 *  \def RETURN_VALUE_IF_FAIL
 *  \brief Convenience macro to exit a function and return a value if a given condition does not hold.
 */
#define RETURN_VALUE_IF_FAIL( predicate, value )    \
    if( !( predicate ) ){                           \
        return value;                               \
    }

/** 
 *  \def ELEMENT_COUNT
 *  \brief Calculates the number of elements in a stack-allocated array.
 *  \note Only works for stack-allocated arrays, *not* for pointers.
 */
#define ELEMENT_COUNT( array ) ( sizeof( array ) / sizeof( ( array )[ 0 ] ) )

/** 
 *  \def NULL
 *  \brief Indicates a null/invalid pointer.
 */
#ifndef NULL
    #define NULL (void*) 0
#endif

/**
 *  @} group macros
 */

#endif // KIRKE__MACROS__H
