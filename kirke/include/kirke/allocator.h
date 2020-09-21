/** 
 *  \file kirke/allocator.h
 */

#ifndef KIRKE__ALLOCATOR__H
#define KIRKE__ALLOCATOR__H

// Internal Includes
#include "kirke/macros.h"

/**
 *  \defgroup allocator Allocator
 *  @{
 */

BEGIN_DECLARATIONS

/**
 *	\brief Allocator is a structure which handles dynamic memory allocation and release.
 *	Allocator itself is opaque, and defined in kirke/src/allocator.c. Allocator is just a virtual
 *	function table with references to methods for alloc, realloc, free, and out_of_memory. 
 *	Allocator can be used direcly by defining these methods and calling allocator__create. Or, 
 *	Allocator can be specialized by defining a structure containing an Allocator* member, see
 *	\ref SystemAllocator for an example.
 */
typedef struct Allocator Allocator;

/**
 *	\brief Creates an allocator structure with the specified methods.  The Allocator structure itself is
 *	dynamically-allocated using the specified alloc_function.
 *	\param alloc_function The function which will be called to allocate new memory.
 *	\param realloc_function The function which will be called to reallocate a block of memory.
 *	\param free_function The function which will be called to free a dynamically-allocated block of memory.
 *	\param out_of_memory_function The function which will be called when an out-of-memory condition occurs.
 *	\param allocator_data A pointer to user-defined data, which will be passed to each of the above methods.
 *	This can be used to track state for a specialized allocator.
 */
Allocator* allocator__create(
	void* ( *alloc_function )( unsigned long long size, void* allocator_data ),
    void* ( *realloc_function )( void* pointer, unsigned long long size, void* allocator_data ),
	void ( *free_function )( void* pointer, void* allocator_data ),
	void ( *out_of_memory_function )( void* allocator_data ),
    void* allocator_data
);

/**
 * 	\brief This method destroys an allocator, freeing the memory allocated for the Allocator structure
 *  itself by calling allocator->free_function.
 *  \param allocator The allocator to be destroyed.
 */
void allocator__destroy( Allocator* allocator );

/**
 * 	\brief This method allocates a new block of memory using the specified Allocator.
 *  \param allocator The allocator to be used for allocation.
 *  \param size The size in bytes of the memory region to be allocated. 
 */
void *allocator__alloc( Allocator* allocator, unsigned long long size );

/**
 *	\brief This method will reallocate a given block of memory. 
 *	If the new region of memory is larger than the old region, then this method will attempt to expand 
 *	the current region. If the current region cannot be expanded, then a new block will be allocated, 
 *	and the old memory will be copied to the start of the new region.
 */
void *allocator__realloc( Allocator* allocator, void* pointer, unsigned long long size );

/**
 * 	\brief This method will free a region of memory allocated with allocator__alloc,  allocator__calloc, or
 *	allocator__realloc.
 *	\param allocator The allocator which will be used to free memory.
 *	\param pointer A pointer to the start of the region of memory to be freed.
 */
void allocator__free( Allocator* allocator, void* pointer );

/**
 *  @} group allocator
 */

END_DECLARATIONS

#endif // KIRKE__ALLOCATOR__H
