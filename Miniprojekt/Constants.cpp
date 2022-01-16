#include "Constants.h"

Integer fastAbs(Integer value)
{
	UInteger temp = value >> (sizeof(UInteger)*8-1);
	value ^= temp;
	value += temp & 1;
	return value;
}

