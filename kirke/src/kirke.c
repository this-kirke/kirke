// System Includes
#include <stdio.h>

// Internal Includes
#include "kirke/kirke.h"


int add( int a, int b ){
    return a + b;
}

int multiply( int a, int b ){
    return a * b;
}

void say_hello( char *buffer, int buffer_size ){
    snprintf( buffer, buffer_size, "Hello!" );
}
