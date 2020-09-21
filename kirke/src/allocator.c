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
    Allocator* allocator = alloc_function( sizeof( Allocator ), allocator_data );

	if( allocator == NULL ){
		if( out_of_memory_function != NULL ){
			out_of_memory_function( allocator_data );
		}
	}
	else{
		allocator->alloc = alloc_function;
		allocator->realloc = realloc_function;
		allocator->free = free_function;
		allocator->out_of_memory = out_of_memory_function;
		allocator->allocator_data = allocator_data;
	}
    
    return allocator;
}

void allocator__destroy( Allocator* allocator ){
    if( allocator != NULL ){
        allocator->free( allocator, allocator->allocator_data );
    }
}


void* allocator__alloc( Allocator* allocator, unsigned long long size ){
    void* new_memory = allocator->alloc( size, allocator->allocator_data );

    if( new_memory == NULL ){
        if( allocator->out_of_memory != NULL ){
            allocator->out_of_memory( allocator->allocator_data );
        }
    }
    
    return new_memory;
}

void allocator__free( Allocator* allocator, void* pointer ){
    allocator->free( pointer, allocator->allocator_data );
}
