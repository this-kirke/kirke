// 3rdParty Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "kirke/list.h"
#include "kirke/system_allocator.h"

bool ints_are_equal( int const *first, int const *second ){
    if( *first == *second ){
        return true;
    }
    return false;
}

LIST__DECLARE( List__int, list__int, int )
LIST__DEFINE( List__int, list__int, int )

class List__TestFixture{
    protected:
        List__TestFixture(){
            system_allocator__initialize( &system_allocator, NULL );
        }

        ~List__TestFixture(){
            system_allocator__deinitialize( &system_allocator );
        }

        SystemAllocator system_allocator;
        List__int *list = NULL;
};

TEST_CASE_METHOD( List__TestFixture, "list__int__head", "[list]" ){
    list = (List__int*) allocator__alloc( system_allocator.allocator, sizeof( List__int ) );
    *list = (List__int){
        .value = 0,
        .next = NULL,
        .previous = NULL
    };

    List__int *current_head = list;
    for( int link_index = 1; link_index < 10; link_index++ ){
        List__int *link= (List__int*) allocator__alloc( system_allocator.allocator, sizeof( List__int ) );
        *link = (List__int){
            .value = link_index,
            .next = NULL,
            .previous = NULL
        };

        current_head->previous = link;
        link->next = current_head;
        link->previous = NULL;

        current_head = link;
    }

    REQUIRE( list__int__head( list ) == current_head );

    while( current_head != NULL ){
        List__int *head = current_head;
        current_head = current_head->next;
        allocator__free( system_allocator.allocator, head );
    }
}
