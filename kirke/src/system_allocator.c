// Internal Includes
#include "kirke/system_allocator.h"

// System Includes
#include <stdlib.h>

// Internal Includes
#include "kirke/system_allocator.h"

static void* system_allocator__alloc( unsigned long long size, void* allocator_data ){
    (void)( allocator_data );
    return malloc( size );
}

static void* system_allocator__realloc( void* pointer, unsigned long long size, void* allocator_data ){
    (void)( allocator_data );
    return realloc( pointer, size );
}

static void system_allocator__free( void* pointer, void* allocator_data ){
    (void)( allocator_data );
    free( pointer );
}

static void system_allocator__out_of_memory( void* allocator_data ){
    SystemAllocator* system_allocator = (SystemAllocator*) allocator_data;

    if( system_allocator->out_of_memory_callback != NULL ){
        system_allocator->out_of_memory_callback();
    }
}

void system_allocator__initialize( SystemAllocator* system_allocator, void( *out_of_memory_callback )( void ) ){
    system_allocator->allocator = allocator__create(
        system_allocator__alloc,
        system_allocator__realloc,
        system_allocator__free,
        system_allocator__out_of_memory,
        system_allocator
    );

    system_allocator->out_of_memory_callback = out_of_memory_callback;
}

void system_allocator__deinitialize( SystemAllocator* system_allocator ){
    if( system_allocator != NULL ){
        allocator__destroy( system_allocator->allocator );
        system_allocator->out_of_memory_callback = NULL;
    }
}
