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

        const int ELEMENT_SIZE = sizeof( long );
        const int ELEMENT_COUNT = 10;
};

TEST_CASE_METHOD( Allocator__TestFixture, "allocator__create_and_destroy", "[allocator]" ){
    REQUIRE( allocator != NULL );
}
