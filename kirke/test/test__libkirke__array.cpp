// 3rdParty Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "kirke/array.h"
#include "kirke/system_allocator.h"

ARRAY__DECLARE( Array__char, array__char, char )
ARRAY__DEFINE( Array__char, array__char, char )


class Array__TestFixture{
    protected:
        Array__TestFixture(){
            system_allocator__initialize( &system_allocator, NULL );
        }

        ~Array__TestFixture(){
            system_allocator__deinitialize( &system_allocator );
        }

        SystemAllocator system_allocator;
};

TEST_CASE_METHOD( Array__TestFixture, "array__char__initialize_and_clear", "[array]" ){
    Array__char array;
    array__char__initialize( &array, system_allocator.allocator, 10 );

    REQUIRE( array.data != NULL );
    REQUIRE( array.capacity == 10 );

    array__char__clear( &array, system_allocator.allocator );

    REQUIRE( array.data == NULL );
    REQUIRE( array.length == 0 );
    REQUIRE( array.capacity == 0 );
    REQUIRE( array.element_size == 1 );
}
