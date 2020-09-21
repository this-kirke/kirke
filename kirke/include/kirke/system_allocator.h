/**
 *  \file kirke/system_allocator.h
 */

#ifndef KIRKE__SYSTEM_ALLOCATOR__H
#define KIRKE__SYSTEM_ALLOCATOR__H

// Internal Includes
#include "kirke/macros.h"
#include "kirke/allocator.h"

BEGIN_DECLARATIONS

/**
 *  \defgroup system_allocator SystemAllocator
 *  @{
 */

/**
 *  \brief An allocator which uses the system's malloc, realloc and free methods.
 *  This allocator checks for out of memory errors (when malloc or realloc returns NULL),
 *  and calls an optional callback if this occurs.
 */
typedef struct SystemAllocator{
    /**
     *  The initialzed allocator, which can be passed to any method requiring an allocator parameter.
     */
    Allocator* allocator;
    /**
     *  An optional callback, specified in system_allocator__initialize, which will be called in case of
     *  out of memory errors.
     */
    void ( *out_of_memory_callback )( void );
} SystemAllocator;

/**
 *  Initializes a SystemAllocator structure.
 *  The SystemAllocator structure contains an \ref allocator field which can be passed to any method taking
 *  an Allocator* parameter. This allocator is a vtable which points to the system's malloc, realloc and free
 *  methods.
 *  \param system_allocator A pointer to the SystemAllocator to be initialized.
 *  \param out_of_memory_callback An optional method which will be called if alloc or realloc return NULL,
 *  i.e. an out of memory condition occurred.
 */
void system_allocator__initialize( SystemAllocator* system_allocator, void( *out_of_memory_callback )( void ) );

/**
 *  De-initializes a SystemAllocator structure.
 *  This must be called when finished with a SystemAllocator initialized with system_allocator__initialize.
 *  \param system_allocator A pointer to the SystemAllocator structure to be de-initialized.
 *  \note Internally this calls allocator__destroy on \ref allocator, so failing to call this method will leak memory.
 */
void system_allocator__deinitialize( SystemAllocator* system_allocator );

/**
 *  @} group system_allocator
 */

END_DECLARATIONS

#endif // KIRKE__SYSTEM_ALLOCATOR__H
