// 3rdParty Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "kirke/allocator.h"


class Allocator__TestFixture{
    protected:
        Allocator__TestFixture(){
            allocator = allocator__create(
                system_alloc, 
                system_realloc,
                system_free,
                NULL,
                NULL
            );
        }

        ~Allocator__TestFixture(){
            allocator__destroy( allocator );
        }

        static void* system_alloc( unsigned long long size, void* allocator_data ){
            return malloc( size );
        }

        static void* system_realloc( void* pointer, unsigned long long size, void* allocator_data ){
            return realloc( pointer, size );
        }

        static void system_free( void* pointer, void* allocator_data ){
            free( pointer );
        }

        Allocator* allocator;
};

TEST_CASE_METHOD( Allocator__TestFixture, "allocator__create_and_destroy", "[allocator]" ){
    REQUIRE( allocator != NULL );
}

TEST_CASE_METHOD( Allocator__TestFixture, "allocator__alloc_and_free", "[allocator]" ){    
    const int ELEMENT_SIZE = sizeof( long );
    const int ELEMENT_COUNT = 10;

    long* array = (long*) allocator__alloc( allocator, ELEMENT_COUNT * ELEMENT_SIZE );

    REQUIRE( array != NULL );

    for( size_t element_index = 0; element_index < ELEMENT_COUNT; element_index++ ){
        array[ element_index ] = 0;
    }

    allocator__free( allocator, array );
}


TEST_CASE_METHOD( Allocator__TestFixture, "allocator__realloc", "[allocator]" ){
    const int ELEMENT_SIZE = sizeof( long );
    const int ELEMENT_COUNT = 10;

    long* array = (long*) allocator__alloc( allocator, ELEMENT_COUNT * ELEMENT_SIZE );

    REQUIRE( array != NULL );

    array = (long*) allocator__realloc( allocator, array, 2 * ELEMENT_COUNT * ELEMENT_SIZE );
    
    REQUIRE( array != NULL );

    // Not a great way to check if realloc was successful.  Element access without a segfault or some reported corruption 
    // is about all we can hope for. 
    for( size_t element_index = 0; element_index < 2 * ELEMENT_COUNT; element_index++ ){
        array[ element_index ] = 0;
    }

    allocator__free( allocator, array );
}
