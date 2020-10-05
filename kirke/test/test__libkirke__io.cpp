// 3rdParty Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "kirke/error.h"
#include "kirke/io.h"
#include "kirke/system_allocator.h"
#include "kirke/string.h"

class IOTestFixture {
    protected:
        IOTestFixture(){
            system_allocator__initialize( &system_allocator, NULL );

            // Create an input file of known size
            FILE* output_file = fopen( file_path.data, "w" );
            unsigned long long bytes_written = fwrite( file_contents.data, 1, file_contents.length, output_file );
            REQUIRE( bytes_written == file_contents.length );
            fclose( output_file );
        }

        ~IOTestFixture(){
            system_allocator__deinitialize( &system_allocator );

            // Remove our input file
            remove( file_path.data );
        }

        SystemAllocator system_allocator;

        String file_path = string__literal( "test_file.txt" );
        String file_contents = string__literal( "Test File Contents:  012345\n" );
};

TEST_CASE_METHOD( IOTestFixture, "io__read_text_file", "[io]" ){
    Error error = {0};

    String input;
    REQUIRE( io__read_text_file( system_allocator.allocator, file_path, &input, &error ) );
    REQUIRE( error.code == Error__None );
    REQUIRE( input.length == file_contents.length );
    REQUIRE( string__equals( input, file_contents ) );

    string__clear( &input, system_allocator.allocator );
}

TEST_CASE_METHOD( IOTestFixture, "io__read_file__error", "[io]" ){
    String does_not_exist = string__literal( "does_not_exist" );

    Error error = {0};
    String input;
    REQUIRE_FALSE( io__read_text_file( system_allocator.allocator, does_not_exist, &input, &error ) );

    REQUIRE( error.code == IO__Error__UnableToOpenFile );
}
