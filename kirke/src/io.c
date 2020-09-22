// Internal Includes
#include "kirke/allocator.h"
#include "kirke/error.h"
#include "kirke/io.h"
#include "kirke/string.h"

String* io__read_text_file( Allocator* allocator, String* file_path, Error* error ){
    FILE* input_file = fopen( file_path->data, "r" );

    if( input_file == NULL ){
        error__set(
            error,
            "IO",
            IO__Error__UnableToOpenFile,
            "Unable to open input file \"%s.\"", file_path->data
        );

        return NULL;
    }

    unsigned long long input_file_size;
    fseek( input_file, 0, SEEK_END );
    input_file_size = ftell( input_file );

    String* output = allocator__alloc( allocator, sizeof( String ) );
    string__initialize( output, allocator, input_file_size );

    fseek( input_file, 0, SEEK_SET );
    output->length = fread( output->data, 1, input_file_size, input_file );

    fclose( input_file );

    return output;
}
