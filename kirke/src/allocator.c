// System Includes
#include "string.h" // memset

// Internal Includes
#include "kirke/allocator.h"

/**
 *  \brief Allocator is a simple vtable for functions which manage memory.
 */
typedef struct Allocator {
    /**
     *  This is a pointer to a function which will allocate new memory.
     */
	void* ( *alloc )( unsigned long long size, void* allocator_data );
    /**
     *  This is a pointer to a function which will reallocate an existing region of memory.
     */
    void* ( *realloc )( void* pointer, unsigned long long size, void* allocator_data );
    /**
     *  This is a pointer to a function which will free a region of memory which was allocated by this 
     *  Allocator.
     */
	void ( *free )( void* pointer, void* allocator_data );
	/**
     *  This is user-specified callback method, which will be called in case one of the allocation methods fails.
     *  This field may be NULL at the user's discretion
     */
    void ( *out_of_memory )( void* allocator_data );
    /**
     *  This is a pointer to user-supplied memory, which will be1 passed to all of the above methods
     */
	void* allocator_data;
} Allocator;


Allocator* allocator__create(
	void* ( *alloc_function )( unsigned long long size, void* allocator_data ),
    void* ( *realloc_function )( void* pointer, unsigned long long size, void* allocator_data ),
	void ( *free_function )( void* pointer, void* allocator_data ),
	void ( *out_of_memory_function )( void* allocator_data ),
    void* allocator_data
){
    (void)( alloc_function );
    (void)( realloc_function );
    (void)( free_function );
    (void)( out_of_memory_function );
    (void)( allocator_data );
    
    return NULL;
}

void allocator__destroy( Allocator* allocator ){
    (void)( allocator );
}
