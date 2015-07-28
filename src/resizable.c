/****
	Resizable array, will be used for all collections storage

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <string.h>
#include "resizable.h"

typedef struct
{
	NODE;
	long        size;
	Node        *mutable;
	Node        *array;
} resizable;
