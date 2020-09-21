// 3rdParty Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "kirke/system_allocator.h"

TEST_CASE( "system_allocator__initialize_and_deinitialize", "[system_allocator]" ){
    SystemAllocator system_allocator;
    system_allocator__initialize( &system_allocator, NULL );

    const unsigned long ELEMENT_COUNT = 25;
    long* memory = (long*) allocator__alloc( system_allocator.allocator, ELEMENT_COUNT * sizeof( long ) );

    for( unsigned long element_index = 0; element_index < ELEMENT_COUNT; element_index++ ){
        memory[ element_index ] = 42;
    }

    allocator__free( system_allocator.allocator, memory );

    system_allocator__deinitialize( &system_allocator );
}
