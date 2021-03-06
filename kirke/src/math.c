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
    if( first > second ){
        return first;
    }

    return second;
}

unsigned long long math__min__ullong( unsigned long long first, unsigned long long second ){
    if( first < second ){
        return first;
    }

    return second;
}

unsigned long long math__max__ullong( unsigned long long first, unsigned long long second ){
    if( first > second ){
        return first;
    }

    return second;
}

unsigned long math__nearest_greater_power_of_2__ulong( unsigned long value ){
    if( value == 0 ){
        return 1;
    }

	while( value & ( value - 1 ) ){
		value = value & ( value - 1 );
    }

	return value << 1;
}
