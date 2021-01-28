#ifndef Sum_Included
#define Sum_Included

#include "console.h"
#include "Set.h"

struct digit {
	int d;
	digit * next;
}; 

digit * sum(digit * first, digit* second);

#endif;