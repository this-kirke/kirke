// System Includes
#include <limits.h>

// Internal Includes
#include "kirke/math.h"

long math__min__long( long first, long second ){
    if( first < second ){
        return first;
    }

    return second;
}

long math__max__long( long first, long second ){
    if( first > second ){
        return first;
    }

    return second;
}

unsigned long math__min__ulong( unsigned long first, unsigned long second ){
    if( first < second ){
        return first;
    }

    return second;
}

unsigned long math__max__ulong( unsigned long first, unsigned long second ){
    (void)( first );
    (void)( second );

    return 0;
}
