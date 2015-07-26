/****
	Linked lists

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "list.h"

typedef struct {
	NODE;
	node    *car;
	node    *cdr;
} list;

