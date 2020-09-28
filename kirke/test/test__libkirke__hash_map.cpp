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
