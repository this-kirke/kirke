// 3rdParty Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "kirke/hash_map.h"
#include "kirke/string.h"
#include "kirke/system_allocator.h"

HASH_MAP__DECLARE( HashMap__StringToInt, hash_map__string_to_int, String, int )
HASH_MAP__DEFINE( HashMap__StringToInt, hash_map__string_to_int, String, int, string__equals )

TEST_CASE( "hash_map__initialize_and_clear", "[hash_map]" ){
    const unsigned long long BUCKET_COUNT = 10;

    SystemAllocator system_allocator;
    system_allocator__initialize( &system_allocator, NULL );

    HashMap__StringToInt hash_map;
    hash_map__string_to_int__initialize( &hash_map, system_allocator.allocator, BUCKET_COUNT );


    REQUIRE( hash_map.allocator == system_allocator.allocator );
    REQUIRE( hash_map.entry_buckets.capacity == BUCKET_COUNT );

    hash_map__string_to_int__clear( &hash_map );
    system_allocator__deinitialize( &system_allocator );
}

class HashMap__TestFixture {
    protected:

        HashMap__TestFixture(){
            system_allocator__initialize( &system_allocator, NULL );
            hash_map__string_to_int__initialize( &hash_map, system_allocator.allocator, BUCKET_COUNT );
        }

        ~HashMap__TestFixture(){
            hash_map__string_to_int__clear( &hash_map );
            system_allocator__deinitialize( &system_allocator );
        }

        const unsigned long long BUCKET_COUNT = 10;
        HashMap hash_map;
        SystemAllocator system_allocator;
};

TEST_CASE_METHOD( HashMap__TestFixture, "hash_map__insert_and_retrieve", "[hash_map]" ){
    String key = string__literal( "key" );
    int value = 42;
    hash_map__string_to_int__insert( &hash_map, key, value );

    int retrieved_value;
    REQUIRE( hash_map__string_to_int__retrieve( &hash_map, key, &retrieved_value ) );
    REQUIRE( retrieved_value == value );

    String does_not_exit = string__literal( "Does not exist." );
    REQUIRE_FALSE( hash_map__string_to_int__retrieve( &hash_map, does_not_exit, &retrieved_value ) );
}

TEST_CASE_METHOD( HashMap__TestFixture, "hash_map__delete", "[hash_map]" ){
    String strings[ 10 ] = {
        string__literal( "zero" ),
        string__literal( "one" ),
        string__literal( "two" ),
        string__literal( "three" ),
        string__literal( "four" ),
        string__literal( "five" ),
        string__literal( "six" ),
        string__literal( "seven" ),
        string__literal( "eight" ),
        string__literal( "nine" )
    };

    for( unsigned long entry_index = 0; entry_index < 10; entry_index++ ){
        hash_map__string_to_int__insert( &hash_map, strings[ entry_index ], entry_index );
    }

    for( unsigned long entry_index = 0; entry_index < 10; entry_index++ ){
        hash_map__string_to_int__delete( &hash_map, strings[ 9 - entry_index ] );

        int value;
        REQUIRE_FALSE( hash_map__string_to_int__retrieve( &hash_map, strings[ 9 - entry_index ], &value ) );
    }
}
