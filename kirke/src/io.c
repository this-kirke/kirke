// System Includes
#include <stdio.h> // fopen, fclose, fseek, ftell, fread

// Internal Includes
#include "kirke/allocator.h"
#include "kirke/error.h"
#include "kirke/io.h"
#include "kirke/string.h"

bool io__read_text_file( Allocator* allocator, String file_path, String *out__string, Error* error ){
    FILE* input_file = fopen( file_path.data, "r" );

    if( input_file == NULL ){
        error__set(
            error,
            "IO",
            IO__Error__UnableToOpenFile,
            "Unable to open input file \"%*s.\"", file_path.length, file_path.data
        );

        return false;
    }

    unsigned long long input_file_size;
    fseek( input_file, 0, SEEK_END );
    input_file_size = ftell( input_file );

    string__initialize( out__string, allocator, input_file_size );

    fseek( input_file, 0, SEEK_SET );
    out__string->length = fread( out__string->data, 1, input_file_size, input_file );

    fclose( input_file );

    return true;
}

String* io__read_stdin( Allocator* allocator ){
    String* output = allocator__alloc( allocator, sizeof( String ) );
    string__initialize( output, allocator, 0 );

    AutoString auto_string = {
        .string = output,
        .allocator = allocator
    };

    char buffer[ 1024 ];
    long bytes_read;
    while( ( bytes_read = fread( buffer, sizeof( char ), sizeof( buffer ), stdin ) ) > 0 ){
        auto_string__append_elements( &auto_string, bytes_read, buffer );
    }

    return output;
}
