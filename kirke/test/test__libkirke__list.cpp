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
LIST__DEFINE( List__int, list__int, int, ints_are_equal )

TEST_CASE( "list__int__head", "[list]" ){
    SystemAllocator system_allocator;
    system_allocator__initialize( &system_allocator, NULL );

    List__int *list = (List__int*) allocator__alloc( system_allocator.allocator, sizeof( List__int ) );
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

    system_allocator__deinitialize( &system_allocator );
}

TEST_CASE( "list__int__tail", "[list]" ){
    SystemAllocator system_allocator;
    system_allocator__initialize( &system_allocator, NULL );

    List__int *list = (List__int*) allocator__alloc( system_allocator.allocator, sizeof( List__int ) );
    *list = (List__int){
        .value = 0,
        .next = NULL,
        .previous = NULL
    };

    List__int *current_tail = list;
    for( int link_index = 1; link_index < 10; link_index++ ){
        List__int *link= (List__int*) allocator__alloc( system_allocator.allocator, sizeof( List__int ) );
        *link = (List__int){
            .value = link_index,
            .next = NULL,
            .previous = NULL
        };

        current_tail->next = link;
        link->previous = current_tail;
        link->next = NULL;

        current_tail = link;
    }

    REQUIRE( list__int__tail( list ) == current_tail );

    while( list != NULL ){
        List__int *head = list;
        list = list->next;
        allocator__free( system_allocator.allocator, head );
    }

    system_allocator__deinitialize( &system_allocator );
}

class List__TestFixture{
    protected:
        List__TestFixture(){
            system_allocator__initialize( &system_allocator, NULL );
            list__int__initialize( &list, system_allocator.allocator, 0 );
        }

        ~List__TestFixture(){
            list__int__clear( list, system_allocator.allocator );
            system_allocator__deinitialize( &system_allocator );
        }

        SystemAllocator system_allocator;
        List__int *list = NULL;
};

TEST_CASE_METHOD( List__TestFixture, "list__int__initialize_and_clear", "[list]" ){
    REQUIRE( list != NULL );
}

TEST_CASE_METHOD( List__TestFixture, "list__int__length", "[list]" ){
    for( int link_index = 1; link_index < 10; link_index++ ){
        list__int__append( list, system_allocator.allocator, link_index );
    }

    REQUIRE( list__int__length( list ) == 10 );
}

TEST_CASE_METHOD( List__TestFixture, "list__int__where", "[list]" ){
    for( int link_index = 1; link_index < 10; link_index++ ){
        list__int__append( list, system_allocator.allocator, link_index );
    }

    List__int * link;
    REQUIRE( list__int__where( list, 3, &link ) );
    REQUIRE( link->value == 3 );

    REQUIRE_FALSE( list__int__where( list, 11, &link ) );
    REQUIRE( link->value == 3 );
}

TEST_CASE_METHOD( List__TestFixture, "list__int__index_of", "[list]" ){
    for( int link_index = 1; link_index < 10; link_index++ ){
        list__int__append( list, system_allocator.allocator, link_index );
    }

    unsigned long long index;
    REQUIRE( list__int__index_of( list, 3, &index ) );
    REQUIRE( index == 3 );

    REQUIRE_FALSE( list__int__index_of( list, 11, &index ) );
    REQUIRE( index == 3 );
}

TEST_CASE_METHOD( List__TestFixture, "list__int__at", "[list]" ){
    for( int link_index = 1; link_index < 10; link_index++ ){
        list__int__append( list, system_allocator.allocator, link_index );
    }

    List__int *link;
    REQUIRE( list__int__at( list, 3, &link ) );
    REQUIRE( link->value == 3 );

    REQUIRE_FALSE( list__int__at( list, 11, &link ) );
    REQUIRE( link->value == 3 );
}

TEST_CASE_METHOD( List__TestFixture, "list__int__position_of", "[list]" ){
    for( int link_index = 1; link_index < 10; link_index++ ){
        list__int__append( list, system_allocator.allocator, link_index );
    }

    List__int *link;
    list__int__at( list, 3, &link );

    REQUIRE( list__int__position_of( link ) == 3 );
}

void list__int__for_each__helper( int *value, void* user_data ){
    bool *called = (bool*) user_data;
    called[ *value ] = 1;
}

TEST_CASE_METHOD( List__TestFixture, "list__int__for_each", "[list]" ){
    for( int link_index = 1; link_index < 10; link_index++ ){
        list__int__append( list, system_allocator.allocator, link_index );
    }

    bool called[ 10 ] = { true };
    list__int__for_each( list, list__int__for_each__helper, called );

    for( int called_index = 0; called_index < sizeof( called ); called_index++ ){
        REQUIRE( called[ called_index ] == true );
    }
}

TEST_CASE_METHOD( List__TestFixture, "list__int__append", "[list]" ){
    for( int list_index = 1; list_index < 10; list_index++ ){
        list__int__append( list, system_allocator.allocator, list_index );
    }

    List__int *current = list;
    for( int list_index = 0; list_index < 10; list_index++ ){
        REQUIRE( current != NULL );
        REQUIRE( current->value == list_index );
        current = current->next;
    }
}

TEST_CASE_METHOD( List__TestFixture, "list__int__prepend", "[list]" ){
    for( int list_index = 1; list_index < 10; list_index++ ){
        list__int__prepend( list, system_allocator.allocator, list_index );
    }

    List__int *current = list;
    for( int list_index = 0; list_index < 10; list_index++ ){
        REQUIRE( current != NULL );
        REQUIRE( current->value == list_index );
        current = current->previous;
    }
}

TEST_CASE_METHOD( List__TestFixture, "list__int__insert_before", "[list]" ){
    for( int list_index = 1; list_index < 10; list_index++ ){
        list__int__append( list, system_allocator.allocator, list_index );
    }

    List__int *third;
    REQUIRE( list__int__at( list, 3, &third ) );

    list__int__insert_before( third, system_allocator.allocator, 11 );

    REQUIRE( list__int__at( list, 3, &third ) );

    REQUIRE( third->value == 11 );
    REQUIRE( third->previous->value == 2 );
    REQUIRE( third->next->value == 3 );
    REQUIRE( third->next->previous == third );
    REQUIRE( third->previous->next == third );
}

TEST_CASE_METHOD( List__TestFixture, "list__int__insert_after", "[list]" ){
    for( int list_index = 1; list_index < 10; list_index++ ){
        list__int__append( list, system_allocator.allocator, list_index );
    }

    List__int *third;
    REQUIRE( list__int__at( list, 3, &third ) );

    list__int__insert_after( third->previous, system_allocator.allocator, 11 );

    REQUIRE( list__int__at( list, 3, &third ) );

    REQUIRE( third->value == 11 );
    REQUIRE( third->previous->value == 2 );
    REQUIRE( third->next->value == 3 );
    REQUIRE( third->next->previous == third );
    REQUIRE( third->previous->next == third );
}

TEST_CASE_METHOD( List__TestFixture, "list__int__concatenate", "[list]" ){
    List__int *second;
    list__int__initialize( &second, system_allocator.allocator, 10 );

    for( int list_index = 1; list_index < 10; list_index++ ){
        list__int__append( list, system_allocator.allocator, list_index );
        list__int__append( second, system_allocator.allocator, 10 + list_index );
    }

    list__int__concatenate( list, second );

    REQUIRE( list__int__length( list ) == 20 );
    for( int list_index = 0; list_index < 20; list_index++ ){
        List__int *link;
        REQUIRE( list__int__at( list, list_index, &link ) );
        REQUIRE( link->value == list_index );
    }
}

TEST_CASE_METHOD( List__TestFixture, "list__int__delete_link", "[list]" ){
    for( int list_index = 1; list_index < 10; list_index++ ){
        list__int__append( list, system_allocator.allocator, list_index );
    }

    List__int *fifth;
    REQUIRE( list__int__at( list, 5, &fifth ) );

    list__int__delete_link( fifth, system_allocator.allocator );
    REQUIRE( list__int__at( list, 5, &fifth ) );

    REQUIRE( fifth->value == 6 );
    REQUIRE( fifth->previous->value == 4 );
    REQUIRE( fifth->previous->next == fifth );
    REQUIRE( fifth->next->value == 7 );
    REQUIRE( fifth->next->previous == fifth );


    List__int *second = list->next;
    list = list__int__delete_link( list, system_allocator.allocator );

    REQUIRE( list == second );
}

TEST_CASE_METHOD( List__TestFixture, "list__int__delete_first", "[list]" ){
    for( int list_index = 1; list_index < 10; list_index++ ){
        list__int__append( list, system_allocator.allocator, list_index );
    }

    List__int *fifth;
    REQUIRE( list__int__at( list, 5, &fifth ) );
    list__int__insert_after( fifth, system_allocator.allocator, 9 );

    list__int__delete_first( list, 9, system_allocator.allocator );

    List__int *link = list;
    int list_index = 0;
    while( link != NULL ){
        REQUIRE( link->value == list_index++ );
        link = link->next;
    }
}
