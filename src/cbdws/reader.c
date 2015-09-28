/****
	General reader to create objects

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"
#include "free_internal.h"

/*
	Unalloc reader
*/
Node *reader_free(Node *node)
{
	free(node);
	return NULL;
}
